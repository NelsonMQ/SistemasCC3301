#include <stdio.h>
#include <stdlib.h>
#include "t2.h"

int calzar(Nodo *a, Nodo **ppat){
    Nodo *b = *ppat;
    //First case
    if(b==NULL){
        *ppat = a;
        return 1;
    }
    //Second case
    if(a==NULL){
        return 0;
    }
    //If the roots are different
    if(b->x!=a->x){
        return 0;
    }
    //We need to know if the left node "calza"
    int i = calzar((*a).izq,&(**ppat).izq);
    //We need to know if the right node "calza"
    int j = calzar((*a).der,&(**ppat).der);
    //If both "calzan"
    if(i==1 && j==1){
        return 1;
    }
    else{
        return 0;
    }
}