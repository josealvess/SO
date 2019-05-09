#include "../../include/head.h"

char* pathSr = "files/strings.txt";
int readS;
int writeS;

void string_to_file (char* nome) {
    writeS = open(pathSr, O_APPEND | O_WRONLY, 0644);
    char* str = malloc ((strlen(nome) * sizeof(char)));
    sprintf(str, "%s\n", nome);
    write(writeS, str, strlen(str));
    free(str);
    close(writeS);
}

int get_num_str () {
    int cod = 1, n; char s[85];
    readS = open(pathSr, O_RDONLY, 0644);
    lseek(readS, 0, SEEK_SET); 
    while ((n = readln(readS, s, 85))) {
        cod++;
        lseek(readS, 0, SEEK_CUR);
    }
    close(readS);
    return cod;
}
/*
char* search_string (int cod) {
    char a[1024];
    readS = open(pathSr, O_RDONLY);
    lseek(readS, 0, SEEK_SET); 
    while ((n = readln(readS, s, 1024))) {
        if (i == id) {
            r = strdup(s);
            break;
        }
        i++;
        lseek(readS, 0, SEEK_CUR);
    }
    close(readS);
    return a;
}*/

char* get_string (int id) {
    char s[85]; int i = 1;
    readS = open(pathSr, O_RDONLY, 0644);
    int n; char* r = "String not found";
    lseek(readS, 0, SEEK_SET); 
    while ((n = readln(readS, s, 85))) {
        if (i == id) {
            r = strdup(s);
            break;
        }
        i++;
        lseek(readS, 0, SEEK_CUR);
    }
    close(readS);
    return r;
}

void print_string() {
    int n; char a[85];
    readS = open(pathSr, O_RDONLY, 0644);
    lseek(readS, 0, SEEK_SET); 
    printf("========Strings\n");
    while ((n = readln(readS, a, 85))) {
        printf("String: %s\n", a);
        lseek(readS, 0, SEEK_CUR);
    }
    close(readS);
}

