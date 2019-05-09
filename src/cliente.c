#include "../include/head.h"

int main (int argc, char* argv[]) {

    char sread[128], swrite[128];
    int n = 1, m;
	char buf[1024];
    char fifo[128];
    // get pid
    int pid_cl = getpid();
    sprintf(fifo, "%d", pid_cl);
    
    // Create read/write pipes
        // write
    sprintf(swrite, "w%s", fifo);
    mkfifo(swrite, 0666);
        // read
    sprintf(sread, "r%s", fifo);
    mkfifo(sread, 0666);

    int s_write = open(swrite, O_WRONLY, 0644);
    int s_read = open(sread, O_RDONLY, 0644);

    // send pid to server
    int server = open("server", O_WRONLY, 0644);
    write(server, fifo, strlen(fifo));
    close(server);
    printf("%d\n", server);

	while( n > 0 ) {
        // write to server
        write(1, PROMPT, PSIZE);
        while((n = read(0, buf, 1024)) == -1);
        //n = read(0, buf, 1024);
        if( buf[0] != '\n' ) {
            write(s_write, buf, n);
        }
        // read from server
        m = read(s_read, buf, 1024);
        if (m > 0) {
            write(1, buf, m);
        }
	}

    close(s_write);
    close(s_read);
    unlink(swrite);
    unlink(sread);

    return 0;
}