#include "../include/head.h"

int cl_read;
int cl_write;

pid_t pub = 0;
pid_t cli = 0;

void sig_term_handler(int signum) {
    kill(cli, SIGUSR1);
    kill(pub, SIGUSR1);
}

void catch_sigterm() {
    static struct sigaction sigact;

    memset(&sigact, 0, sizeof(struct sigaction));
    sigact.sa_handler = sig_term_handler;

    sigaction(SIGTERM, &sigact, NULL);
}


void adiciona_venda (int art, int qtd_stock, int qtd_venda) {
    Artg a = search_artigo (art); 
    Venda v = init_venda();
    v->cod = get_num_venda();
    v->art = art;
    int total = qtd_stock + qtd_venda;
    (total < 0) ? (v->qtd = qtd_stock) : (v->qtd = abs(qtd_venda));
    v->preco = v->qtd * a->preco;
    add_venda(v);
    free(v);
    free(a); 
}

void adicionar_stock (int cod, int qtd) {
    Stock s = search_stock(cod);
    if (s->art == 0) {
        Artg a = search_artigo (cod);  
        if (a->cod != 0 ) {
            s->art = cod;
            if (qtd < 0) s->qtd = 0;
            else s->qtd = qtd;
            add_stock(s);
        } 
        free(a);
    } else {
        if (qtd < 0)
            adiciona_venda(s->art, s->qtd, qtd);
        ((s->qtd + qtd) < 0) ? (s->qtd = 0) : (s->qtd += qtd);
        update_stock(s);
    }
    Reply r = init_reply();
    r->type = 1; r->qtd = s->qtd;
    write(cl_write, r, sizeof(struct reply));
    free(s);
    free(r);
}

void show_stock(int cod) {
    Artg a = search_artigo (cod); Reply r = init_reply();
    if (a->cod != 0 ){ 
        Stock s = search_stock (a->cod); 
        r->type = 2; r->qtd = s->qtd; r->pr = a->preco;
        free(s);
    }
    write(cl_write, r, sizeof(struct reply));
    free(a); free(r);
}

void agrega () {
    char filename[85];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(filename, "files/%d-%d-%dT%d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    // replace standard input with input file
    int vendas = open("files/vendas", O_RDONLY, 0644);
    dup2(vendas, 0);
    // replace standard output with output file
    int agr = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
    dup2(agr, 1);
    // close unused file descriptors
    close(vendas);
    close(agr);
    // execute
    execlp("./ag", "./ag", NULL);
    _exit(-1);
}

void handler(int sig) {
    wait(NULL);
}

int main (int argc, char* argv[]) {
    
    catch_sigterm(); // mata servidor
    signal(SIGCHLD, handler); // previne zombies

    mkfifo("wserver", 0666); 
    int read_from_client = open("wserver", O_RDONLY, 0644);
    mkfifo("rserver", 0666); 
    int write_to_client = open("rserver", O_RDWR, 0644);
    char sread[85]; char swrite[85];
	Command c = init_command();  Reply r = init_reply();
    int n;

    while ( 1 ) {
        while((n = read(read_from_client, c, sizeof(struct cmd))) == -1);
        if (n > 0) {
            pub = getpid();
            write(write_to_client, r, sizeof(struct reply));
            if (c->type == 5) { 
                if (fork() == 0) {
                    printf("Agregador\n");
                    agrega();
                    _exit(-1);
                }
            } else if (c->type == 2) {
                sprintf(swrite, "r%d", c->pid);
                cl_write = open(swrite, O_RDWR, 0644);
                adicionar_stock(c->art, c->pr);
                close(cl_write);
            } else {
                int pid_cl = c->pid;
                sprintf(sread, "w%d", pid_cl);
                sprintf(swrite, "r%d", pid_cl);
                pid_cl = fork();
                if (pid_cl == 0) {
                    cli = pid_cl;
                    cl_read = open(sread, O_RDONLY, 0644);
                    cl_write = open(swrite, O_RDWR, 0644);
                    while((n = read(cl_read, c, sizeof(struct cmd))) && (c->type != -1)) {
                        if (c->type == 1) 
                            show_stock(c->art);
                    }
                    close(cl_write);
                    close(cl_read);
                    _exit(-1);
                }
            }
        }
    }

    free(c);
    unlink("wserver");
    unlink("rserver");
    close(read_from_client); close(write_to_client);

    return 0;
}