#include "../include/head.h"

int main (int argc, char* argv[]) {

    if(mkfifo("cliente", 0666) == -1)  
        perror("Pipe failed");

    int n = 1;
	char buf[1024];
	int cliente = open("cliente", O_WRONLY);
    //int received = open("return", O_RDONLY);

	while( n > 0 ){
		write(1, PROMPT, PSIZE);
		n = read(0, buf, 1024);
		if( buf[0] != '\n' )
			write(cliente, buf, n);
	}
    close(cliente);
    //close(received);

    return 0;
}