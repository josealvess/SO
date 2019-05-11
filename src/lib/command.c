#include "../../include/head.h"

int read_client (int *input, char *buf) {
    char *token; int i = 0;
    token = strtok(buf, DELIM);
    do {
        input[i++] = atoi(token);
        token = strtok(NULL, DELIM);
    } while (token != NULL);
    return i;
}

Command init_command() {
    Command c = (Command) malloc (sizeof(struct cmd));
    c->type = 0;
    c->art = 0;
    c->pr = 0;
    c->pid = 0;
    return c;
}

