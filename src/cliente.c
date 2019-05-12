#include "../include/head.h"

int main (int argc, char* argv[]) {

    char sread[85], swrite[85];
    int n = 1, m, input_size, input[2];
	char buf[85]; int r = 0;
    // get pid
    int pid_cl = getpid();
    Command c = init_command();
    c->pid = pid_cl;
    // send pid to server
    int write_to_server = open("wserver", O_WRONLY, 0644);
    write(write_to_server, c, sizeof(struct cmd));

    int read_from_server = open("rserver", O_RDONLY, 0644);
    while(read(read_from_server, &r, sizeof(int)) == -1) sleep(1);
    // Create read/write pipes
        // write
        sprintf(swrite, "w%d", c->pid);
        mkfifo(swrite, 0666);
        int s_write = open(swrite, O_RDWR, 0644);
        // read
        sprintf(sread, "r%d", c->pid);
        mkfifo(sread, 0666);
        int s_read = open(sread, O_RDONLY, 0644);

    // write to server
    write(1, PROMPT, PSIZE);
    while((n = readln(0, buf, 85))) {
        if( buf[0] != '\n' ) {
            input_size = read_client(input, buf);
            if (input_size == 1) {
                c->type = 1;
                c->art = input[0];
                write(s_write, c, sizeof(struct cmd));
            } else if (input_size == 2) {
                c->type = 2;
                c->art = input[0];
                c->pr = input[1];
                while(write(write_to_server, c, sizeof(struct cmd)) == -1) sleep(1);
            }
        }
        buf[0] = 0;
        // read from server
        m = read(s_read, buf, 85);
        if (m > 0)
            write(1, buf, m);
        buf[0] = 0;

        write(1, PROMPT, PSIZE);
	}

    c->type = -1;
    write(s_write, c, sizeof(struct cmd));

    free(c);
    close(write_to_server); close(read_from_server); close(s_write); close(s_read);
    unlink(swrite); unlink(sread);

    return 0;
}