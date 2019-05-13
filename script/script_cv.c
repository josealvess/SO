#include "../include/head.h"

int main(int argc, char *argv[]) {
    int pid;

    for(int i = 0; i < 1; i++) {
        pid = fork();
        if(pid == 0) {
            int fd = open("script/scr_cv", O_RDONLY);
            dup2(fd, 0);
            close(fd);
            execlp("./cv", "./cv", NULL);
            _exit(-1);
        }    
    }
    return 0;
}