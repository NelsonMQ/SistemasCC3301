#include <string.h>
#include "t1.h"
#include <stdlib.h>

uint comprimir(uint *a, int nbits){
    int mask = ~(-1<<nbits);
    uint *p = a;
    uint u = 0;
    int n = 32;
    while(n>(nbits-1)){
        u = u|(mask & *p);
        p++;
        u = u << nbits;
        n = n - nbits;
    }
    return u;
}

char *insercion(char *d, char *s){
    char *newstr = malloc(strlen(d)+strlen(s)+1);
    strcpy(newstr,s);
    newstr = strcat(newstr,d);
    return newstr;
}

void insertar(char *d, char *s){
    char *p = d + strlen(d) + strlen(s);
    char *p2 = d + strlen(d);
    char *p3 = s + strlen(s) - 1;
    for (int i = 0; i < strlen(d)+1; i++){
        *p = *p2;
        p--;
        p2--;
    }
    for (int i = 0; i < strlen(s); i++){
        *p = *p3;
        p--;
        p3--;
    }
}

int main(){
    return 0;
}
