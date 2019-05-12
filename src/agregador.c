#include "../include/head.h"

char* pathAg = "files/vendas";
int readAg;
int agreg;

void agrega(Venda v) {
    Venda vd = init_venda();
    int f = open("files/agregador", O_CREAT | O_RDWR, 0644);
    lseek(f, (v->art-1) * sizeof(struct venda), SEEK_SET);
    read(f, vd, sizeof(struct venda));
    if (vd->cod == 0) {
        lseek(f, (v->art-1) * sizeof(struct venda), SEEK_SET);
        write(f, v, sizeof(struct venda));
    } else {
        vd->qtd += v->qtd;
        vd->preco += v->preco;
        lseek(f, (vd->art-1) * sizeof(struct venda), SEEK_SET);
        write(f, vd, sizeof(struct venda));
    }
    v->agreg = 1;
    update_venda(v);
    free(vd);
}

void file_agreg() {
    Venda v = init_venda();
    char str[85]; int n;
    agreg = open("files/agregador", O_RDONLY, 0644);
    while ((n = read(agreg, v, sizeof(struct venda)))) {
        if (v->cod != 0) {
            sprintf(str, "Artigo: %d - Qtd: %d - Preço: %f\n", v->art, v->qtd, v->preco);
            write(1, str, strlen(str));
        }
        lseek(agreg, 0, SEEK_CUR);
    }
    close(agreg);
    free(v);
}

int main (int argc, char* argv[])  {

    int n = 1;
    Venda v = init_venda();
    while((n = read(0, v, sizeof(struct venda)))) {
        if (v->agreg == 0)
            agrega(v);
        lseek(agreg, 0, SEEK_CUR);
	}
    // processar agregação
    file_agreg();
    unlink("files/agregador");
    free(v);

    return 0;

}