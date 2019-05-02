#include "../../include/head.h"

char* pathSr = "files/strings";
int readS;
int writeS;

void string_to_file (char* str) {
    writeS = open(pathSr, O_APPEND | O_WRONLY);
    write(writeS, str, sizeof(char));
    close(writeS);
}

int get_num_str () {
    int cod = 1, n; char* s = NULL;
    readS = open(pathSr, O_RDONLY);
    lseek(readS, 0, SEEK_SET); 
    while ((n = read(readS, s, sizeof(char)))) {
        lseek(readS, cod++ * sizeof(char), SEEK_SET);
    }
    free(s);
    close(readS);
    return cod;
}

char* search_string (int cod) {
    char* a = NULL;
    readS = open(pathSr, O_RDONLY);
    lseek(readS, (cod-1) * sizeof(char), SEEK_SET);
    read(readS, a, sizeof(char));
    close(readS);
    return a;
}

char* get_string (int id) {
    char* s = NULL;
    readS = open(pathSr, O_RDONLY);
    int n; char* r = "String not found";
    lseek(readS, (id-1) * sizeof(char), SEEK_SET);
    if ((n = read(readS, s, sizeof(char))))
        r = strdup(s);
    close(readS);
    return r;
}

void print_string() {
    int n, i = 1; char* a = NULL;
    readS = open(pathSr, O_RDONLY);
    lseek(readS, 0, SEEK_SET); 
    printf("========Strings\n");
    while ((n = read(readS, a, sizeof(char)))) {
        printf("String: %s\n", a);
        lseek(readS, i++ * sizeof(char), SEEK_SET);
    }
    close(readS);
}

