#include "../include/head.h"

char* pathA = "files/artigos";
char* pathS = "files/strings.txt";
int artigos;
int strings;

void help() {
	printf("i <nome> <preço>        -> Insere artigo\n");
	printf("n <código> <novo nome>  -> Altera nome\n");
	printf("p <código> <novo preço> -> Altera preço\n");
    printf("f <código>              -> Procura artigo\n");
	printf("a                       -> Agregador\n");
	printf("v                       -> Apresenta vendas\n");
	printf("s                       -> Apresenta artigos\n\n");
}

void add_artigo (char* buf) {
    int id; char *nome, str[45]; 
    nome = strtok(NULL, DELIM);
    // strings 
    id = get_num_str();
    string_to_file(nome);
    // artigo
    Artg a = init_artigo();
    a->cod = get_num_art();
    a->nome = id; 
    a->preco = atof(strtok(NULL, DELIM));
    artigo_to_file(a); 
    free(a);
    sprintf(str, "Artigo -> %d\n", a->cod);
    write(1, str, strlen(str));
}

void alt_nome (char* buf) {
    int cod, id; char *nome; char* out = "Não existem artigos com esse código\n";
    cod = atoi(strtok(NULL, DELIM));
    Artg a = search_artigo (cod);  
    if (a->cod != 0 ) {
        nome = strtok(NULL, DELIM);
        // strings 
        id = get_num_str();
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
    Artg a = search_artigo (cod);  
    if (a->cod != 0 ) {
        a->preco = atof(strtok(NULL, DELIM));
        mod_art(a);
    } else
        write(1, out, strlen(out));
    free(a);
}

void show_artigo(char* buf) {
    char* out = "Não existem artigos com esse código\n";
    int cod = atoi(strtok(NULL, DELIM));
    Artg a = search_artigo (cod);  
    if (a->cod != 0 )
        art_info(a);
    else
        write(1, out, strlen(out));
    free(a);
}

void call_agreg() {
    char s[7];
    sprintf(s, "agreg\n");
    // send agreg to server
    int server = open("server", O_WRONLY, 0644);
    write(server, s, strlen(s));
    close(server);
}

int main (int argc, char* argv[]) {
    int n = 1; char *token, opt; 
    char buf[85];

    artigos = open(pathA, O_CREAT, 0644);
    close(artigos);
    strings = open(pathS, O_CREAT, 0644);
    close(strings);

    while (n > 0) {
        
        write(1, PROMPT, PSIZE);
        while((n = readln(0, buf, 85)) == -1);
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
            case 's': print_artigos();
                    break;
            case 'v': print_vendas();
                    break;
            case 'f': show_artigo(buf);
                    break;
            case 'a': call_agreg();
                    break;
            case '?': help();
                    break;
            default: 
                    break;
        }
    }

    return 0;
}