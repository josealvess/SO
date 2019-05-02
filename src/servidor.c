#include "../include/head.h"

char* pathS = "files/stocks";
char* pathV = "files/vendas";
int stocks;
int vendas;

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
}

void adicionar_stock () {
    int cod, st; Stock s = init_stock();
    printf("========Adicionar Stock\n");
    printf("Codigo do  artigo: ");
    scanf("%d", &cod);  
    Artg a = search_artigo (cod);  
    if (a->cod !=0 ) {
        printf("Stock: ");
        scanf("%d", &st);
        s->art = a->cod;
        s->qtd = st;
        add_stock(s);
    } else
        printf("Não existem artigos com esse código\n");
    free(s);
    free(a);
}

void show_artigo() {
    int cod;
    printf("Codigo do Artigo: ");
    scanf("%d", &cod);  
    Artg a = search_artigo (cod);  
    if (a->cod !=0 )
        art_info(a);
    else
        printf("Não existem artigos com esse código\n");
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
    int opt = 99;

    stocks = open(pathS, O_CREAT);
    close(stocks);
    vendas = open(pathV, O_CREAT);
    close(vendas);

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
    }

    return 0;
}