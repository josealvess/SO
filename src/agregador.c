#include "../include/head.h"
#include <time.h>

char* pathAg = "files/vendas";
int readAg;
int agreg;

void agrega(Venda v) {
    Venda vd = init_venda(); int n, found = 0;
    int f = open("files/agregador", O_CREAT | O_RDWR | O_APPEND, 0644);
    while ((n = read(f, vd, sizeof(struct venda))) && !found) {
        printf("N -> %d\n", n);
        if (vd->art == v->art) {
            printf("Artigo -> %d\n", vd->art);
            vd->qtd += v->qtd;
            vd->preco += v->preco;
            lseek(f, (vd->art-1) * sizeof(struct venda), SEEK_SET);
            write(f, vd, sizeof(struct venda));
            found = 1;
        } 
    }
    printf("n -> %d\n", n);
    if (n == 0) {
        lseek(f, (vd->art-1) * sizeof(struct venda), SEEK_SET);
        write(f, v, sizeof(struct venda));
    }
    v->agreg = 1;
    //update_venda(v);
}

void vendas () {
    int n; Venda v = init_venda();
    readAg = open(pathAg, O_RDONLY, 0644);
    lseek(readAg, 0, SEEK_SET); 
    while ((n = read(readAg, v, sizeof(struct venda)))) {
        if (v->agreg == 0)
            agrega(v);
        lseek(readAg, 0, SEEK_CUR);
    }
    close(readAg);
    free(v);
}

void file_agreg() {
    char filename[128]; Venda v = init_venda();
    time_t t = time(NULL); char str[128];
    struct tm tm = *localtime(&t); int n;
    sprintf(filename, "files/%d-%d-%dT%d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("%s\n", filename);
    agreg = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
    readAg = open(pathAg, O_RDONLY, 0644);
    while ((n = read(readAg, v, sizeof(struct venda)))) {
        sprintf(str, "Artigo: %d - Qtd: %d - Preço: %f\n", v->art, v->qtd, v->preco);
        write(agreg, str, strlen(str));
        lseek(readAg, 0, SEEK_CUR);
    }
    close(agreg);
}

void agregador () {

    vendas();
    file_agreg();
    system("rm files/agregador");

}