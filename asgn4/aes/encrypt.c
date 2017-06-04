/*
 * This code encrypts input data using the Rijndael (AES) cipher.  The
 * key length is hard-coded to 128 key bits; this number may be changed
 * by redefining a constant near the start of the file.
 *
 * This program uses CTR mode encryption.
 *
 * Usage: encrypt <key1> <key2> <file name>
 *
 * Author: Ethan L. Miller (elm@cs.ucsc.edu)
 * Based on code from Philip J. Erdelsky (pje@acm.org)
 *
 */

#include <stdio.h>
#include <fcntl.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "rijndael.h"

static char rcsid[] = "$Id: encrypt.c,v 1.2 2003/04/15 01:05:36 elm Exp elm $";

#define KEYBITS 128
#define STICKY  01000


/* Used to grab the second half of the key if needed */
int second_half (int keylen)
{
  if (keylen < 8)
    return keylen;
  else
    return 8;
}

int main(int argc, char **argv)
{
  unsigned long rk[RKLENGTH(KEYBITS)];	/* round key */
  unsigned char key[KEYLENGTH(KEYBITS)];/* cipher key */
  char	buf[100];
  int i, nbytes, nwritten , ctr;
  int totalbytes;
  int	k0, k1;
  int fileId = 0x1234;			/* fake (in this example) */
  int nrounds;				/* # of Rijndael rounds */
  char *password;			/* supplied (ASCII) password */
  int	fd;
  char *filename;
  unsigned char filedata[16];
  unsigned char ciphertext[16];
  unsigned char ctrvalue[16];

  char* usage = "Usage: ./protectfile <-e || --encrypt> || <-d || --decrypt> <key1> <key2> <file>\n";
  //char* args;
  int encrypt_set = 0;
  int decrypt_set = 0;
  struct stat file_stat;

  if (argc < 5)
  {
    printf ("%s", usage);
    return 1;
  }

  // Checking args passed by user.
  if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encrypt"))
  {
    encrypt_set = 1;
  }
  else if (strcmp(argv[1], "-d") || strcmp(argv[1], "--decrypt"))
  {
    decrypt_set = 1;
  }
  else
  {
    printf ("Invalid arguments!\n");
    printf ("%s", usage);
    return 1;
  }

  // Need to strip off leading 0x if user provides key in hex form.
  if (argv[2][0] == '0' && (argv[2][1] == 'x' || argv[2][2] == 'X'))
  {
    printf("it\'s hex.\n");
    argv[2] += 2;
  }
  if (argv[3][0] == '0' && (argv[3][1] == 'x' || argv[3][2] == 'X'))
  {
    printf("it\'s hex.\n");
    argv[2] += 2;
  }

  int key_length = strlen(argv[2]);

  bzero (key, sizeof (key));
  bzero (ctrvalue, sizeof (ctrvalue));
  // Need to get key into a hex value and strip off leading 0's.

  // Removing a bunch of shit to make this accept 2 keys instead of 1.
  #if 0
    // Creating "0xdeadbeef" or whatever.
    bcopy (argv[2], &buf[2], second_half(key_length));
    printf ("%s\n", buf);
    /*
     * long num = strol ( str_with_nums_and_letters, char* ptr_string_portion, base)
     * - So basically num gets set to the number thats in str_... and ptr_...
     *   gets the string that's in str_...
     * - If base == 0, then the string should have a 0x prefix, which will then
     *   cause the number to be read in base-16.
     */
    k0 = strtol (buf, NULL, 0);
    printf ("k0: %d\n", k0);
    // Clearing buf.
    bzero (buf, sizeof(buf));
    // If need be, grab the remaining ints from the key, and make a new hex value.
    if (key_length > 8)
    {
      strcpy (buf, "0x");
      bcopy ((argv[2] + 8), &buf[2], key_length - 8);
    }
    k1 = strtol (buf, NULL, 0);
    printf ("k1: %d\n", k1);

    // Might want to delete this.  Check with Jake.
    if (k0 == 0 && k1 == 0)
    {
      fprintf(stderr, "Encryption / Decryption disabled for this user.\n");
      exit (-1);
    }
    
    bzero (buf, sizeof(buf));
  #else
    k0 = strtol (argv[2], NULL, 0);
    k1 = strtol (argv[3], NULL, 0);
  #endif
  // Replacing the leading 0's in key with our newly formatted k0.
  bcopy (&k0, &(key[0]), sizeof (k0));
  bcopy (&k1, &(key[sizeof(k0)]), sizeof (k1));
  filename = argv[argc - 1];

  /* Print the key, just in case */
  for (i = 0; i < sizeof (key); i++) {
    sprintf (buf+2*i, "%02x", key[sizeof(key)-i-1]);
  }
  fprintf (stderr, "KEY: %s\n", buf);
  
  /*
   * Initialize the Rijndael algorithm.  The round key is initialized by this
   * call from the values passed in key and KEYBITS.
   */
  nrounds = rijndaelSetupEncrypt(rk, key, KEYBITS);

  /*
   * Open the file.
   */
  fd = open(filename, O_RDWR);
  if (fd < 0)
  {
    fprintf(stderr, "Error opening file %s\n", argv[argc - 1]);
    return 1;
  }

  // Opening the inode of fd.
  if (fstat(fd, &file_stat) < 0)
  {
    fprintf (stderr, "Unable to get stats from file %s\n", argv[argc - 1]);
    return 1;
  }

  // inode "number" of fd.
  fileId = file_stat.st_ino;
  // Testing
  printf("%s inode num: %d\n", argv[argc - 1], fileId);

  // fd permissions = protection_mode AND NOT(sticky)
  // Unsetting sticky-bit.
  if (fchmod(fd, file_stat.st_mode & ~(STICKY)))
  {
    printf("Cannot unset sticky bit!\n");
    return 1;
  }
  
  
  /* fileID goes into bytes 8-11 of the ctrvalue */
  bcopy (&fileId, &(ctrvalue[8]), sizeof (fileId));

  /* This loop reads 16 bytes from the file, XORs it with the encrypted
     CTR value, and then writes it back to the file at the same position.
     Note that CTR encryption is nice because the same algorithm does
     encryption and decryption.  In other words, if you run this program
     twice, it will first encrypt and then decrypt the file.
  */
  for (ctr = 0, totalbytes = 0; /* loop forever */; ctr++)
  {
    /* Read 16 bytes (128 bits, the blocksize) from the file */
    nbytes = read (fd, filedata, sizeof (filedata));
    if (nbytes <= 0) {
      break;
    }
    if (lseek (fd, totalbytes, SEEK_SET) < 0)
    {
      perror ("Unable to seek back over buffer");
      exit (-1);
    }

    // Padding with zeros so userspace matches kernelspace.
    if (nbytes < 16)
    {
      for (int i = nbytes; i < 16; i++)
      {
        filedata[i] = 0;
      }
    }

    /* Set up the CTR value to be encrypted */
    bcopy (&ctr, &(ctrvalue[0]), sizeof (ctr));

    /* Call the encryption routine to encrypt the CTR value */
    rijndaelEncrypt(rk, nrounds, ctrvalue, ciphertext);

    /* XOR the result into the file data */
    for (i = 0; i < nbytes; i++) {
      filedata[i] ^= ciphertext[i];
    }

    /* Write the result back to the file */
    nwritten = write(fd, filedata, nbytes);
    if (nwritten != nbytes)
    {
      fprintf (stderr,
	       "%s: error writing the file (expected %d, got %d at ctr %d\n)",
	       argv[0], nbytes, nwritten, ctr);
      break;
    }

    /* Increment the total bytes written */
    totalbytes += nbytes;
  }

  if (fstat(fd, &file_stat) < 0)
  {
    fprintf (stderr, "Unable to get stats from file %s\n", argv[argc - 1]);
    return 1;
  }

  if (encrypt_set)
  {
    if (fchmod(fd, file_stat.st_mode | STICKY)){
      // For some reason it works without sudo lol
      //printf("chmod:  Error encrypting.  Are you using sudo?\n");
    }
  }
  else if (decrypt_set)
  {
    if (fchmod(fd, file_stat.st_mode & ~(STICKY))){
      // For some reason it works without sudo lol
      //printf("chmod:  Error decrypting.  Are you using sudo?\n");
    }
  }
  close (fd);
}
