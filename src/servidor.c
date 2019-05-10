#include "../include/head.h"

char* pathS = "files/stocks";
char* pathV = "files/vendas";
int stocks;
int vendas;
int cl_read;
int cl_write;

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

void adicionar_stock (int cod, int qtd) {
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
        if (qtd < 0)
            adiciona_venda(s->art, s->qtd, qtd);
        add_stock(s);
    }
    char out[128]; strcpy(out, ""); 
    sprintf(out, "Novo Stock -> %d\n", s->qtd);
    write(cl_write, out, strlen(out));
    free(s);
}

void show_stock(int cod) {
    char out[128]; strcpy(out, ""); 
    Artg a = search_artigo (cod);   
    if (a->cod != 0 ){ 
        Stock s = search_stock (a->cod); 
        sprintf(out, "Stock -> %d Preco -> %f\n", s->qtd, a->preco);
        write(cl_write, out, strlen(out));
        free(s);
    }
    free(a);
}

void files() {
    stocks = open(pathS, O_CREAT, 0644);
    close(stocks);
    vendas = open(pathV, O_CREAT, 0644);
    close(vendas);
}

int main (int argc, char* argv[]) {
    
    //files();
    mkfifo("server", 0666);
    int get_client = open("server", O_RDONLY, 0644);
    char sread[85]; char swrite[85];
	char buf1[85], buf2[85];
    int n, input_size, input[2];

    while (1) {
        while((n = read(get_client, buf1, 85)) == -1);
        if (n > 0) {
            //printf("%s\n", buf1);
            if (strcmp(buf1, "agreg\n") == 0) { 
                agregador();
            } else if ((input_size = read_client(input, buf1)) == 2) {
                cl_write = open(swrite, O_WRONLY, 0644);
                adicionar_stock(input[0], input[1]);
                close(cl_write);
            } else {
                pid_t pid_cl = atoi(buf1);
                sprintf(sread, "w%d", pid_cl);
                sprintf(swrite, "r%d", pid_cl);
                printf("cliente %d recebido\n", pid_cl);
                pid_cl = fork();
                if (pid_cl == 0) {
                    cl_read = open(sread, O_RDONLY, 0644);
                    printf("A ler-> %s, %d\n", sread, cl_read);
                    cl_write = open(swrite, O_WRONLY, 0644);
                    printf("A escrever-> %s, %d\n", swrite, cl_write);
                    while((n = read(cl_read, buf2, 85))) {
                        input_size = read_client(input, buf2);
                        switch (input_size) {
                            case 1: show_stock(input[0]);
                                    break;
                            default: 
                                    break;                
                        }
                    }
                    _exit(0);
                    close(cl_read);
                    close(cl_write);
                }
            }
        }
    }

    close(get_client);
    unlink("server");

    return 0;
}