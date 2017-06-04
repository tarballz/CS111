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
// Universal check for sticky bit.
// Prints 0 if sticky is not set.
// Prints 512 (i.e., not zero) if sticky is set.
#define CHECK_STICKY(var) ((var) & (1<<(9)))

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
  unsigned long rk[RKLENGTH(KEYBITS)];  /* round key */
  unsigned char key[KEYLENGTH(KEYBITS)];/* cipher key */
  char  buf[100];
  int i, nbytes, nwritten , ctr;
  int totalbytes;
  int k0, k1;
  int fileId, file_mode;
  int nrounds;        /* # of Rijndael rounds */
  char *password;     /* supplied (ASCII) password */
  int fd;
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
  if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encrypt") == 0)
  {
    encrypt_set = 1;
  }
  else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decrypt") == 0)
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
    argv[3] += 2;
  }

  int key_length = strlen(argv[2]);

  bzero (key, sizeof (key));
  bzero (ctrvalue, sizeof (ctrvalue));
  // Need to get key into a hex value and strip off leading 0's.

  k0 = strtol (argv[2], NULL, 0);
  k1 = strtol (argv[3], NULL, 0);
  // Replacing the leading 0's in key with our newly formatted k0.
  bcopy (&k0, &(key[0]), sizeof (k0));
  bcopy (&k1, &(key[sizeof(k0)]), sizeof (k1));

  // sys_setkey()
  syscall(548, k0, k1);
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

  // inode "mode" of fd, using for the check for STICKY.
  file_mode = file_stat.st_mode;

  // Checks for if the user is trying to decrypt a decrypted file.
  //printf("Sticky value: %d\n", CHECK_STICKY(file_mode));
  if (CHECK_STICKY(file_mode) == 0 && (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decrypt") == 0))
  {
    printf("Trying to decrypt a decrypted file!\n");
    exit(-1);
  }
  // Checks for if the user is trying to encrypt a encrypted file.
  if (CHECK_STICKY(file_mode) > 0 && (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encrypt") == 0))
  {
    printf("Trying to encrypt an encrypted file!\n");
    exit(-1);
  }

  // fd permissions = protection_mode AND NOT(sticky)
  // Unsetting sticky-bit.
  if (fchmod(fd, file_stat.st_mode & ~(S_ISVTX)) == -1)
  {
    printf("Cannot unset sticky bit!\n");
    return 1;
  }

  //printf("Trying to decrypt: %d\n", (file_stat.st_mode & ~(S_ISVTX)));
  
  
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
    printf("Encrypt: %d\n", fchmod(fd, file_stat.st_mode | S_ISVTX));
    if (fchmod(fd, file_stat.st_mode | S_ISVTX)){
      // For some reason it works without sudo lol
      //printf("chmod:  Error encrypting.  Are you using sudo?\n");
    }
  }
  else if (decrypt_set)
  {
    printf("Decrypt: %d\n", fchmod(fd, file_stat.st_mode & ~(S_ISVTX)));
    if (fchmod(fd, file_stat.st_mode & ~(S_ISVTX))){
      // For some reason it works without sudo lol
      //printf("chmod:  Error decrypting.  Are you using sudo?\n");
    }
  }
  close (fd);
}