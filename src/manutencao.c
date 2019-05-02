#include "../include/head.h"

char* pathA = "files/artigos";
char* pathS = "files/strings";
int artigos;
int strings;

void help() {
	printf("i <nome> <preço>        -> Insere artigo\n");
	printf("n <código> <novo nome>  -> Altera nome\n");
	printf("p <código> <novo preço> -> Altera preço\n");
	printf("s                       -> Apresenta artigos\n\n");
}

void add_artigo (char* buf) {
    int id; char *token; char* str;
    token = strtok(NULL, DELIM);
    // strings 
    str = malloc (strlen(token) * sizeof(char));
    strcpy(str, token);
    printf("str -> %s\n", str);
    id = get_num_str(str);
    string_to_file(str);
    free(str);
    // artigo
    Artg a = init_artigo();
    a->cod = get_num_art();
    a->nome = id; 
    a->preco = atof(strtok(NULL, DELIM));
    artigo_to_file(a); 
    free(a);
    sprintf(str, "Artigo -> %d\n", id);
    write(1, str, strlen(str));
}

void alt_nome (char* buf) {
    int cod, id; char *nome; char* out = "Não existem artigos com esse código\n";
    cod = atoi(strtok(NULL, DELIM));
    Artg a = search_artigo (cod);  
    if (a->cod != 0 ) {
        nome = strtok(NULL, DELIM);
        // strings 
        id = get_num_str(nome);
        string_to_file(nome);
        a->nome = id;
        mod_art(a);
    } else
        write(1, out, strlen(out));
    free(a);
}

void alt_preco (char* buf) {
    int cod; char* out = "Não existem artigos com esse código\n";
    cod = atoi(strtok(NULL, DELIM));
    printf("Cod -> %d\n", cod);
    Artg a = search_artigo (cod);  
    if (a->cod != 0 ) {
        a->preco = atof(strtok(NULL, DELIM));
        mod_art(a);
    } else
        write(1, out, strlen(out));
    free(a);
}
/*
void show_artigo() {
    int cod;
    printf("Codigo do Artigo: ");
    scanf("%d", &cod);  
    Artg a = search_artigo (cod);  
    if (a->cod != 0 )
        art_info(a);
    else
        printf("Não existem artigos com esse código\n");
    free(a);
}*/

int main (int argc, char* argv[]) {
    int n = 1; char *token, opt; 
    char buf[1024];

    artigos = open(pathA, O_CREAT);
    close(artigos);
    strings = open(pathS, O_CREAT);
    close(strings);

    while (n > 0) {
        
        write(1, PROMPT, PSIZE);
        n = readln(0, buf, 1024);
        if (n > 0) {
            token = strtok(buf, DELIM);
            opt = *token;
        }
        switch (opt) {
            case 'i': add_artigo(buf);
                    break;
            case 'n': alt_nome(buf);
                    break;
            case 'p': alt_preco(buf);
                    break;
            case 's': print_string();
                    break;
            case '?': help();
                    break;
            default: 
                    break;
        }
    }

    return 0;
}