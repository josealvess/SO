#ifndef __HEAD__
#define __HEAD__

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

ssize_t readln (int fildes, void *buf, size_t nbyte);

//Artigos
Artg init_artigo();
void artigo_to_file (Artg art);
void mod_art (Artg a);
void art_info (Artg a);
void print_artigos ();
Artg search_artigo (int cod);
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
void rm_stock (Stock s, int qtd);
Stock search_stock (int cod);
void print_stock();

#endif