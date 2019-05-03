#include "../../include/head.h"

char* pathAr = "files/artigos";
int readA;
int writeA;

Artg init_artigo() {
    Artg a = (Artg) malloc (sizeof(struct artg));
    a->cod = 0;
    a->nome = 0;
    a->preco = 0;
    return a;
}
/*
Artg art_to_struct (char* s) {
    Artg a = (Artg) malloc (sizeof(struct artg));
    char *token;
	token = strtok(str, DELIM);
    token = strtok(NULL, DELIM);
    a->nome = 

}*/

int get_num_art () {
    int cod = 1, n;
    readA = open(pathAr, O_RDONLY);
    Artg a = init_artigo();
    lseek(readA, 0, SEEK_SET); 
    while ((n = read(readA, a, sizeof(struct artg)))) {
        lseek(readA, cod++ * sizeof(struct artg), SEEK_SET);
    }
    free(a);
    close(readA);
    return cod;
}

void artigo_to_file (Artg art) {
    writeA = open(pathAr, O_APPEND | O_WRONLY);
    write(writeA, art, sizeof(struct artg));
    close(writeA);
}

void mod_art (Artg a) {
    readA = open(pathAr, O_RDWR);
    lseek(readA, (a->cod-1) * sizeof(struct artg), SEEK_SET);
    write(readA, a, sizeof(struct artg));
    close(readA);
}

void art_info (Artg a) {
    char* nome = strdup(get_string(a->nome));
    printf("Codigo: %d ", a->cod);
    printf("Nome: %s ", nome);
    printf("Preço: %f\n", a->preco);
} 
  
void print_artigos () {
    int n, i = 1; Artg a = init_artigo();
    readA = open(pathAr, O_RDONLY);
    lseek(readA, 0, SEEK_SET); 
    while ((n = read(readA, a, sizeof(struct artg)))) {
        art_info(a);
        lseek(readA, i++ * sizeof(struct artg), SEEK_SET);
    }
    close(readA);
    free(a);
}

Artg search_artigo (int cod) {
    Artg a = init_artigo();
    readA = open(pathAr, O_RDONLY);
    lseek(readA, (cod-1) * sizeof(struct artg), SEEK_SET);
    read(readA, a, sizeof(struct artg));
    close(readA);
    return a;
}




