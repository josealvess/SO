#include "../include/head.h"
#include <time.h>

char* pathAg = "files/vendas";
int readAg;
int agreg;
char filename[128];

Agreg agregado;

Agreg init_agreg () {
    Agreg a = (Agreg) malloc (sizeof(struct agreg));
    a->art = 0;
    a->qtd = 0;
    a->preco = 0;
    a->prox = NULL;
    return a;
}

void agrega (Venda v, Agreg a) {
    if (v->agreg == 0) {
        Agreg aux = a;
        if (aux == NULL) {
            printf("entrei art %d\n", v->art);
            agregado = init_agreg();
            aux = agregado;
            aux->art = v->art;
            aux->qtd += v->qtd;
            aux->preco += v->preco;
            printf("asdfgaedfghjklkjhgfdsadfgh\n");
        } else if (aux->art == v->art) {
            aux->qtd += v->qtd;
            aux->preco += v->preco;
        } else {
            while ((aux != NULL) && (aux->art != v->art)) {
                printf("batata %d\n", v->art); 
                aux = aux->prox;
                agrega(v, aux);
            }
        }
        v->agreg = 1;
        //update_venda (v);    
    }
}

void vendas () {
    int n; Venda v = init_venda();
    readAg = open(pathAg, O_RDONLY, 0644);
    lseek(readAg, 0, SEEK_SET); 
    Agreg aux = agregado;
    while ((n = read(readAg, v, sizeof(struct venda)))) {
        agrega(v, aux);
        lseek(readAg, 0, SEEK_CUR);
    }
    close(readAg);
    free(v);
}

void agregador () {

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(filename, "files/%d-%d-%dT%d:%d:%d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("%s\n", filename);

    //agreg = open(filename, O_CREAT, 0777);
    //close(agreg);
  
    vendas();

    Agreg aux = agregado;
    while (aux)
        printf("Art: %d - Qtd: - %d Preco: %f\n", aux->art, aux->qtd, aux->preco);

}