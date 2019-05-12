#include "../include/head.h"

char* pathAg = "files/vendas";
int readAg;
int agreg;

void agrega(Venda v) {
    Venda vd = init_venda(); int n, found = 0;
    int f = open("files/agregador", O_CREAT | O_RDWR | O_APPEND, 0644);
    while ((n = read(f, vd, sizeof(struct venda))) && !found) {
        if (vd->art == v->art) {
            //printf("Artigo -> %d\n", vd->art);
            vd->qtd += v->qtd;
            vd->preco += v->preco;
            lseek(f, (vd->art-1) * sizeof(struct venda), SEEK_SET);
            write(f, vd, sizeof(struct venda));
            found = 1;
        } 
    }
    if (n == 0) {
        lseek(f, (vd->art-1) * sizeof(struct venda), SEEK_SET);
        write(f, v, sizeof(struct venda));
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
        sprintf(str, "Artigo: %d - Qtd: %d - Preço: %f\n", v->art, v->qtd, v->preco);
        write(1, str, strlen(str));
        lseek(agreg, 0, SEEK_CUR);
    }
    close(agreg);
    free(v);
}

int main (int argc, char* argv[])  {

    int n = 1; Venda v = init_venda();

    int vendas = open("files/vendas", O_RDONLY, 0644);
    while((n = read(vendas, v, sizeof(struct venda))) == -1) {
            print_venda (v->cod);
            //agrega(v);
        // processar agregação
        //file_agreg();
	}
    system("rm files/agregador");
    free(v);

    return 0;

}