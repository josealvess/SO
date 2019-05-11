#include "../../include/head.h"

char* pathSt = "files/stocks";
int readSt;

Stock init_stock() {
    Stock s = (Stock) malloc (sizeof(struct stock));
    s->art = 0;
    s->qtd = 0;
    return s;
}

void add_stock (Stock s) {
    readSt = open(pathSt, O_CREAT | O_APPEND | O_WRONLY, 0644);
    write(readSt, s, sizeof(struct stock));
    close(readSt);
}

void update_stock (Stock s) {
    readSt = open(pathSt, O_CREAT | O_RDWR, 0644);
    lseek(readSt, (s->art-1) * sizeof(struct stock), SEEK_SET);
    write(readSt, s, sizeof(struct stock));
    close(readSt);
}

Stock search_stock (int cod) {
    Stock a = init_stock();
    readSt = open(pathSt, O_CREAT | O_RDONLY, 0644);
    lseek(readSt, (cod-1) * sizeof(struct stock), SEEK_SET);
    read(readSt, a, sizeof(struct stock));
    close(readSt);
    return a;
}

void print_stock() {
    int n; Stock a = init_stock();
    readSt = open(pathSt, O_RDONLY, 0644);
    lseek(readSt, 0, SEEK_SET); 
    printf("========Stock\n");
    while ((n = read(readSt, a, sizeof(struct stock)))) {
        if(a->art != 0)
            printf("Artigo: %d - Stock: %d\n", a->art, a->qtd);
        lseek(readSt, 0, SEEK_CUR);
    }
    close(readSt);
    free(a);
}
