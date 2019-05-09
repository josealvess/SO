#include "../include/head.h"

char* pathS = "files/stocks";
char* pathV = "files/vendas";
int stocks;
int vendas;

int read_client (int *input, char *buf) {
    char *token; int i = 0;
    token = strtok(buf, DELIM);
    do {
        input[i++] = atoi(token);
        token = strtok(NULL, DELIM);
    } while (token != NULL);
    return i;
}

void adiciona_venda (int art, int qtd_stock, int qtd_venda) {
    Artg a = search_artigo (art); 
    Venda v = init_venda();
    v->art = art;
    if ((qtd_stock + qtd_venda) < 0) v->qtd = qtd_stock; 
    else v->qtd = abs(qtd_venda);
    v->preco = v->qtd  * a->preco;
    add_venda(v);
    free(v);
    free(a); 
}

char* adicionar_stock (int cod, int qtd) {
    Stock s = search_stock(cod);
    if (s->art == 0) {
        Artg a = search_artigo (cod);  
        if (a->cod !=0 ) {
            s->art = cod;
            if (qtd < 0) s->qtd = 0;
            add_stock(s);
        } 
        free(a);
    } else {
        if ((s->qtd + qtd) < 0) s->qtd = 0; 
        else s->qtd += qtd;
        add_stock(s);
        if (qtd < 0)
            adiciona_venda(s->art, s->qtd, qtd);
    }
    char *out = NULL; 
    sprintf(out, "Novo Stock -> %d\n", s->qtd);
    write(1, out, strlen(out));
    free(s);
    return out;
}

char* show_stock(int cod) {
    char *out = NULL; 
    Artg a = search_artigo (cod);   
    if (a->cod != 0 ){ 
        Stock s = search_stock (a->cod); 
        sprintf(out, "Stock -> %d Preco -> %f\n", s->qtd, a->preco);
        write(1, out, strlen(out));
        free(s);
    }
    free(a);
    return out;
}

void files() {
    stocks = open(pathS, O_CREAT, 0644);
    close(stocks);
    vendas = open(pathV, O_CREAT, 0644);
    close(vendas);
}

int main (int argc, char* argv[]) {
    
    files();

    mkfifo("server", 0666);
    int get_client = open("server", O_RDONLY, 0644);
    int cl_read;
    int cl_write;
    char sread[128]; char swrite[128];
	char buf[1024], *out;
    int n, input_size, input[2];

    while (1) {
        while((n = read(get_client, buf, 1024)) == -1);
        if (n > 0) {
            int pid_cl = atoi(buf);
            sprintf(sread, "w%d", pid_cl);
            sprintf(swrite, "r%d", pid_cl);
            printf("cliente %d recebido\n", pid_cl);
            pid_cl = fork();
            if (pid_cl == 0) {
                cl_read = open(sread, O_RDONLY, 0644);
                cl_write = open(swrite, O_WRONLY, 0644);
                while((n = readln(cl_read, buf, 1024))) {
                    input_size = read_client(input, buf);
                    switch (input_size) {
                        case 1: out = strdup(show_stock(input[0]));
                                break;
                        case 2: out = strdup(adicionar_stock(input[0], input[1]));
                                break;
                        default: 
                                break;                
                    }
                    write(cl_write, out, strlen(out));
                }
                _exit(0);
                close(cl_read);
                close(cl_write);
            }
        }
    }

    close(get_client);
    unlink("server");

    return 0;
}