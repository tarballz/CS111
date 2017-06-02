#include <stdio.h>
#include <fcntl.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/vnode.h>
#include "crypto_rijndael.h"

#define KEYBITS 128
#define STICKY  01000
#define KEYSIZE 16

int AESencrypt(unsigned char *user_key, int fileId, unsigned char *data, size_t va_size)
{
  unsigned long rk[RKLENGTH(KEYBITS)];  /* round key */
  unsigned char key[KEYLENGTH(KEYBITS)];/* cipher key */
  int i, ctr;
  int totalbytes;
  int nrounds;              /* # of Rijndael rounds */
  unsigned char ciphertext[KEYSIZE];
  unsigned char ctrvalue[KEYSIZE];

  // Clear all buffers.
  bzero(key, sizeof(key));
  bzero(ctrvalue, KEYSIZE);
  bzero(ciphertext, KEYSIZE);

  bcopy(&(user_key[0]), &(key[0]), 8);

  /*
   * Initialize the Rijndael algorithm.  The round key is initialized by this
   * call from the values passed in key and KEYBITS.
   */
  nrounds = rijndaelSetupEncrypt(rk, key, KEYBITS);

  // fileId -> bytes [8, 11] of ctrvalue
  bcopy(&fileId, &(ctrvalue[8]), sizeof(fileId));

  if ((va_size % KEYSIZE) != 0)
  {
    for (i = 0; i < (va_size % KEYSIZE); i++)
    {
      data[va_size + i] = 0;
    }
  }

  /* This loop reads 16 bytes from the file, XORs it with the encrypted
     CTR value, and then writes it back to the file at the same position.
     Note that CTR encryption is nice because the same algorithm does
     encryption and decryption.  In other words, if you run this program
     twice, it will first encrypt and then decrypt the file.
  */
  int index;
  for (ctr = 0, totalbytes = 0; totalbytes < va_size; ctr++)
  {
    /* Set up the CTR value to be encrypted */
    bcopy (&ctr, &(ctrvalue[0]), sizeof (ctr));

    /* Call the encryption routine to encrypt the CTR value */
    rijndaelEncrypt(rk, nrounds, ctrvalue, ciphertext);

    index = ctr * KEYSIZE;

    /* XOR the result into the file data */
    for (i = 0; i < KEYSIZE; i++) {
      filedata[index + i] ^= ciphertext[i];
    }

    /* Increment the total bytes written */
    totalbytes += KEYSIZE;
  }
  return 0;
}