#include "../../include/head.h"

ssize_t readln(int fildes, void *buf, size_t nbyte) {
	ssize_t nbytes = 0;
	int n;
	char c;
	char *buffer = (char *)buf;

	while( nbytes < nbyte && (n = read(fildes,&c,1)) > 0 && c != '\n' )
		buffer[nbytes++] = c;

	(nbytes < nbyte) ? (buffer[nbytes] = '\0') : (buffer[nbytes - 1] = '\0');	

	return nbytes;
}

int read_client (int *input, char *buf) {
    char *token; int i = 0;
    token = strtok(buf, DELIM);
    do {
        input[i++] = atoi(token);
        token = strtok(NULL, DELIM);
    } while (token != NULL);
    return i;
}
