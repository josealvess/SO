#include "../include/head.h"

int main (int argc, char* argv[]) {

    char sread[85], swrite[85];
    int n = 1, m, input_size, input[2];
	char buf1[85], buf2[85];
    char fifo[85], *in;
    // get pid
    int pid_cl = getpid();
    sprintf(fifo, "%d", pid_cl);
    // send pid to server
    int server = open("server", O_WRONLY, 0644);
    write(server, fifo, strlen(fifo));
    // Create read/write pipes
        // write
        sprintf(swrite, "w%s", fifo);
        mkfifo(swrite, 0666);
        int s_write = open(swrite, O_RDWR, 0644);
        // read
        sprintf(sread, "r%s", fifo);
        mkfifo(sread, 0666);
        int s_read = open(sread, O_RDONLY, 0644);

	while( n > 0 ) {
        // write to server
        write(1, PROMPT, PSIZE);
        n = read(0, buf1, 85);
        if( buf1[0] != '\n' ) {
            in = strdup(buf1);
            input_size = read_client(input, buf1);
            switch (input_size) {
                case 1: write(s_write, in, n);
                        break;
                default: write(server, in, n);
                        break;                
            } 
        }
        buf1[0] = 0;
        // read from server
        m = read(s_read, buf2, 85);
        write(1, buf2, m);
        buf2[0] = 0;
	}

    close(server); close(s_write); close(s_read);
    unlink(swrite); unlink(sread);

    return 0;
}