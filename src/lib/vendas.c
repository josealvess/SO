#include "../../include/head.h"

char* pathVd = "files/vendas";
int readVd;

Venda init_venda() {
    Venda v = (Venda) malloc (sizeof(struct venda));
    v->cod = 0;
    v->art = 0;
    v->qtd = 0;
    v->preco = 0;
    v->agreg = 0;
    return v;
}

int get_num_venda () {
    int cod = 1, n; Venda v = init_venda();
    readVd = open(pathVd, O_CREAT | O_RDONLY, 0644);
    lseek(readVd, 0, SEEK_SET); 
    while ((n = read(readVd, v, sizeof(struct venda)))) {
        cod++;
        lseek(readVd, 0, SEEK_CUR);
    }
    free(v);
    close(readVd);
    return cod;
}

void add_venda (Venda v) {
    readVd = open(pathVd, O_CREAT | O_APPEND | O_WRONLY, 0644);
    write(readVd, v, sizeof(struct venda));
    close(readVd);
}

void update_venda (Venda v) {
    readVd = open(pathVd, O_RDWR, 0644);
    lseek(readVd, (v->cod-1) * sizeof(struct venda), SEEK_SET);
    write(readVd, v, sizeof(struct venda));
    close(readVd);
}

Venda get_venda (int cod) {
    Venda v = init_venda();
    readVd = open(pathVd, O_RDONLY, 0644);
    lseek(readVd, (v->cod-1) * sizeof(struct venda), SEEK_SET);
    read(readVd, v, sizeof(struct venda));
    close(readVd);
    return v;
}

void print_vendas() {
    int n; Venda v = init_venda();
    readVd = open(pathVd, O_RDONLY, 0644);
    lseek(readVd, 0, SEEK_SET); 
    printf("========Vendas\n");
    while ((n = read(readVd, v, sizeof(struct venda)))) {
        printf("Cod: %d - Artigo: %d - Qtd: %d - Preço: %f - Agreg: %d\n", v->cod, v->art, v->qtd, v->preco, v->agreg);
        lseek(readVd, 0, SEEK_CUR);
    }
    close(readVd);
    free(v);
}
