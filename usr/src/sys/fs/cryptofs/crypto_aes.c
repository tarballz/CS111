#include <stdio.h>
#include <fcntl.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "crypto_rijndael.h"

#define KEYBITS 128
#define STICKY  01000

int AESencrypt(unsigned char *ukey, int fileId, unsigned char *data, size_t va_size)
{
  unsigned long rk[RKLENGTH(KEYBITS)];  /* round key */
  unsigned char key[KEYLENGTH(KEYBITS)];/* cipher key */
  int i, nbytes, nwritten , ctr;
  int totalbytes;
  int nrounds;              /* # of Rijndael rounds */
  unsigned char ciphertext[16];
  unsigned char ctrvalue[16];
}