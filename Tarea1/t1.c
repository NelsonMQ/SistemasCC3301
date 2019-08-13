#include <string.h>
#include "t1.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Dado un arreglo con unsigned int,
 * los trunca a los "nbits" menos significativos
 * y los concatena en un solo unsigned int
 */
uint comprimir(uint *a, int nbits){
    int mask = ~(-1<<nbits); //Mascara con 1's en los "nbits" bits menos significativos
    uint *p = a;
    uint u = 0;
    int n = sizeof(uint)<<3; //Cantidad de bits que ocupa un uint
    while(n>(nbits-1)){ //Mientras nos quede espacio en el uint "u"
        u = u|(mask & *p); //concatenamos el uint truncado
        p++;
        if(n-nbits>nbits-1)//la ultima vez no movemos a "u"
            u = u << nbits;
        n = n - nbits;
    }
    return u;
}

/*
 * Dado dos strings "d" y "s", entrega un nuevo string
 * donde "s" es concatenado con "d"
 */
char *insercion(char *d, char *s){
    char *newstr = malloc(strlen(d)+strlen(s)+1);
    strcpy(newstr,s);
    strcat(newstr,d);
    return newstr;
}

/*
 * Dado dos strings "d" y "s", en donde
 * "d" posee bits no utilizados, inserta a "s"
 * en el principio del string "d".
 */
void insertar(char *d, char *s){
    char *p = d + strlen(d) + strlen(s); //apunta a donde termina el String resultante
    char *p2 = d + strlen(d); // apunta al "0" del string "d"
    char *p3 = s + strlen(s) - 1; // apunta al ultimo caracter de "s"
    while(p2!=d-1) { // corremos descendentemente el strin "d"
        *p = *p2;
        p--;
        p2--;
    }
    while(p3!=s-1) { // copiamos el string "s" al principio del string "d"
        *p = *p3;
        p--;
        p3--;
    }
}