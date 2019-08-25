#include <stdio.h>
#include <stdlib.h>
#include "t2.h"

int calzar(Nodo *a, Nodo **ppat){
    Nodo *b = *ppat;
    if(b==NULL){
        *ppat = a;
        return 1;
    }
    if(a==NULL){
        return 0;
    }
    if(b->x!=a->x){
        return 0;
    }
    int i = calzar((*a).izq,&(**ppat).izq);
    int j = calzar((*a).der,&(**ppat).der);
    if(i==1 && j==1){
        return 1;
    }
    else{
        return 0;
    }
}