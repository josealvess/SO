#include "../include/head.h"

char* pathS = "files/stocks";
char* pathV = "files/vendas";
int stocks;
int vendas;
/*
int menu () {
    int opt;
    printf("\n========Servidor de Vendas========\n");
    printf("1 - Ver artigos\n");
    printf("2 - Procurar artigo\n");
    printf("3 - Ver Stock\n");
    printf("4 - Adicionar Stock\n");
    printf("5 - Remover Stock\n");
    printf("0 - Sair\n");
    printf("Escolha opção: ");
    scanf("%d", &opt);
    return opt;
}*/

int read_client (int *input, char *buf) {
    char *token; int i = 0;
    token = strtok(buf, DELIM);
    do {
        input[i++] = atoi(token);
        token = strtok(NULL, DELIM);
    } while (token != NULL);
    return i;
}

void adicionar_stock (int cod, int qtd) {
    Stock s = search_stock(cod);
    if (s->art == 0) {
        Artg a = search_artigo (cod);  
        if (a->cod !=0 ) {
            s->art = cod;
            s->qtd = qtd;
            add_stock(s);
        } 
        free(a);
    } else {
        s->qtd += qtd;
        add_stock(s);
    }
    free(s);
}

void show_artigo(int cod) {
    Artg a = search_artigo (cod);  
    if (a->cod !=0 )
        art_info(a);
    free(a);
}

void show_stock(int cod) {
    Artg a = search_artigo (cod);   
    if (a->cod != 0 ){ 
        char out[128];
        Stock s = search_stock (a->cod); 
        sprintf(out, "Stock -> %d Preco -> %f\n", s->qtd, a->preco);
        write(1, out, strlen(out));
        free(s);
    }
    free(a);
}

void remove_stock() {
    int cod, q;
    printf("Codigo do Artigo: ");
    scanf("%d", &cod);  
    Stock a = search_stock (cod);  
    if (a->art !=0 ) {
        printf("Quantidade a remover: ");
        scanf("%d", &q);
        rm_stock(a, q);
    } else
        printf("Não existem artigos com esse código\n");
    free(a);
}

int main (int argc, char* argv[]) {
/*
    if(mkfifo("return", 0666) == -1)  
        perror("Pipe failed...");
*/
	char buf[1024], s[25];
    //int opt = 99;
    int n, input_size, input[2];
	int cliente = open("cliente", O_RDONLY);
    //int send = open("return", O_WRONLY);

    stocks = open(pathS, O_CREAT);
    close(stocks);
    vendas = open(pathV, O_CREAT);
    close(vendas);

    while ((n = read(cliente, buf, 1024))) {
        input_size = read_client(input, buf);
        sprintf(s, "Input size -> %d\n", input_size);
        switch (input_size) {
            case 1: show_stock(input[0]);
                    break;
            case 2: adicionar_stock(input[0], input[1]);
                    break;
            default: 
                    break;
        }
        write(1, s, strlen(s));
        write(1, buf, n);
        //sprintf(s, "Enviei -> %d", i++);
        //write(received, s, strlen(s));
    }

    close(cliente);
    //close(send);

    
 
    /*
    int fd = open("fifo",O_WRONLY);

    while (opt!=0) {
        opt = menu();
        switch (opt) {
            case 1: print_artigos();
                    break;
            case 2: show_artigo();
                    break;
            case 3: print_stock();
                    break;
            case 4: adicionar_stock();
                    break;
            case 5: remove_stock();
                    break;
            default: 
                    break;
        }
    }*/

    return 0;
}