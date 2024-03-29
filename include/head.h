#ifndef __HEAD__
#define __HEAD__

#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PROMPT "> "
#define PSIZE 3
#define DELIM " "

typedef struct artg {
    int cod;
    int nome;
    float preco;
} *Artg;

typedef struct stock {
    int art;
    int qtd;
} *Stock;

typedef struct venda {
    int cod;
    int art;
    int qtd;
    float preco;
    int agreg;
} *Venda;

typedef struct cmd {
    int type;
    int art;
    int pr;
    int pid;
} *Command;

typedef struct reply {
    int type;
    int qtd;
    float pr;
} *Reply;

typedef struct comp {
    int n_art;
    int n_nome;
} *Comp;

ssize_t readln (int fildes, void *buf, size_t nbyte);
int read_client (int *input, char *buf);

//Artigos
Artg init_artigo();
void artigo_to_file (Artg art);
void mod_art (Artg a);
void art_info (Artg a);
void print_artigos ();
Artg search_artigo (int cod);
void show_artigo(char* buf);
int get_num_art ();
//Strings
char* str_to_str (char* s);
char* get_string (int id);
void string_to_file (char* str);
int get_num_str ();
char* search_string (int cod);
void print_string();
//Stocks
Stock init_stock();
void add_stock (Stock s);
void update_stock (Stock s);
Stock search_stock (int cod);
void print_stock();
//Vendas
Venda init_venda();
Venda str_to_venda (char* str);
int get_num_venda();
void add_venda (Venda s);
void update_venda (Venda v);
Venda get_venda (int art);
void print_venda (int cod);
void print_vendas();
//agregador
void agregador ();
void file_agreg();
//command
Command init_command();
Reply init_reply();
//compacta
void test_log_size();
void add_art_comp();
void add_str_comp();

#endif