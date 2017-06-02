#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <fcntl.h>

#define KEYBITS 128
#define KEYLENGTH(keybits) ((keybits)/8)

int main(int argc, char *argv[])
{
	if (argc < 2) { 
		fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
		fprintf(stderr, "Usage: %s <hex>\n", argv[0]);
		return -1;
	}

  	unsigned int k0, k1;
	unsigned char key[KEYLENGTH(KEYBITS)];

	if (argc == 2) {
		if (argv[1][0] == '0' && (argv[1][1] == 'X' || argv[1][1] == 'x')) {
			argv[1] += 2;
		} else {
			fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
			fprintf(stderr, "Usage: %s <hex>\n", argv[0]);
			return -1;
		}
	}

	printf("argv[1]: %s\n", argv[1]);
	_exit(0);

	bzero (key, sizeof (key));
  	k0 = strtol (argv[1], NULL, 0);
  	k1 = strtol (argv[2], NULL, 0);
  	if ((k0 == 0) && (k1 == 0))
  		printf("setkey(0,0)\n");
  	bcopy (&k0, &(key[0]), sizeof (k0));
  	bcopy (&k1, &(key[sizeof (k0)]), sizeof (k1));

	for (int i = 0; i < sizeof (key); i++)
    	printf("%02x", key[sizeof (key)-i-1]);
  	printf("\n");

	return __syscall(548, k0, k1);
}