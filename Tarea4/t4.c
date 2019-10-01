#include <stdio.h>
#include <pthread.h>

#include "integral.h"

/*
 * Estructura para almacenar los datos y respuesta.
 */
typedef struct {
    Funcion f;
    void *ptr;
    double xi;
    double xf;
    int n;
    double resp;
}Args;

/*
 * Adaptacion de la funcion "integral" para que pueda ser llamada por pthread_create.
 */
void *integral_t(void *ptr){
    Args *args = ptr;
    double resp = integral(args->f,args->ptr,args->xi,args->xf,args->n);
    args->resp=resp;
    return NULL;
}

/*
 * Calcula una integral en "p" threads.
 */
double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p) {
    pthread_t t[p];
    Args args[p];
    double sub_intervalo = (xf-xi)/p;
    for(int i=0;i<p;i++){
        Args *arg = &args[i];
        arg->f = f;
        arg->ptr = ptr;
        arg->xi = xi + sub_intervalo*i;
        arg->xf = xi + sub_intervalo*(i+1);
        arg->n = n/p;
        pthread_create(&t[i],NULL,integral_t,&args[i]);
    }
    double suma = 0;
    for(int i=0;i<p;i++){
        pthread_join(t[i],NULL);
        suma += args[i].resp;
    }
    return suma;
}