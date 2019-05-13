#include "../../include/head.h"

char *pathCmp = "files/log";

Comp init_comp() {
    Comp c = (Comp) malloc (sizeof(struct comp));
    c->n_art = 0;
    c->n_nome = 0;
    return c;
}

void add_art_comp ()  {
    Comp c =  init_comp();
    int comp = open(pathCmp,  O_CREAT | O_RDWR, 0644);
    read(comp, c, sizeof(struct comp));
    c->n_art = c->n_art + 1; c->n_nome = c->n_nome + 1;
    lseek(comp, 0, SEEK_SET);
    write(comp, c, sizeof(struct comp));
    close(comp);
    free(c);
}

void add_str_comp ()  {
    Comp c =  init_comp();
    int comp = open(pathCmp,  O_CREAT | O_RDWR, 0644);
    read(comp, c, sizeof(struct comp));
    c->n_nome = c->n_nome + 1;
    lseek(comp, 0, SEEK_SET);
    write(comp, c, sizeof(struct comp));
    close(comp);
    free(c);
}

void new_str_file (char* nome) {
    int w = open("files/new_strings", O_CREAT | O_APPEND | O_WRONLY, 0644);
    char* str = malloc ((strlen(nome) * sizeof(char)));
    sprintf(str, "%s\n", nome);
    write(w, str, strlen(str));
    free(str);
    close(w);
}

int new_num_str () {
    int cod = 1, n; char s[85];
    int r = open("files/new_strings", O_RDONLY, 0644);
    lseek(r, 0, SEEK_SET); 
    while ((n = readln(r, s, 85))) {
        cod++;
        lseek(r, 0, SEEK_CUR);
    }
    close(r);
    return cod;
}

void compacta() {
    int readA = open("files/artigos", O_RDONLY, 0644);
    Artg a = init_artigo(); char *new; int n, id;
    lseek(readA, 0, SEEK_SET); 
    while ((n = read(readA, a, sizeof(struct artg)))) {
        new = strdup(get_string(a->nome));
        id = new_num_str();
        new_str_file(new);
        a->nome = id;
        mod_art(a);
        lseek(readA, 0, SEEK_CUR);
    }
    free(a);
    close(readA);
    unlink("files/strings");
    rename("files/new_strings", "files/strings");
}

void new_log_size() {
    Comp c =  init_comp();
    int comp = open(pathCmp,  O_CREAT | O_RDWR, 0644);
    read(comp, c, sizeof(struct comp));
    c->n_art = get_num_art() - 1; c->n_nome = get_num_str() - 1;
    lseek(comp, 0, SEEK_SET);
    write(comp, c, sizeof(struct comp));
    close(comp);
    free(c);    
}

void test_log_size() {
    Comp c =  init_comp();
    int comp = open(pathCmp,  O_CREAT | O_RDWR, 0644);
    read(comp, c, sizeof(struct comp));
    if ((c->n_nome*0.8) > c->n_art) {
        compacta();
        new_log_size();
    }
    close(comp);
    free(c);
}

