#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "impr.h"

/**
 * Estructura para indicar la orden de imprimir un documento.
 */
struct orden {
    Doc *doc;
    int listo;
};

/**
 * Definimos las variables globales
 */

ColaFifo *colaFifo;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_t t[3];
int n;

/**
 * Funcion que se ocupa en el thread y representa a una impresora
 */
void *t_imprimir(void *ptr){
    Impr *impr = ptr;
    for(;;) {
        pthread_mutex_lock(&m);
        while (vacia(colaFifo)) {
            pthread_cond_wait(&cond, &m);
        }
        Orden *ord = extraer(colaFifo);
        pthread_mutex_unlock(&m);
        pthread_cond_broadcast(&cond);
        imprimir(ord->doc, impr);
        pthread_mutex_lock(&m);
        ord->listo = 1;
        pthread_mutex_unlock(&m);
        pthread_cond_broadcast(&cond);
        if(vacia(colaFifo)){
            break;
        }
    }
    return NULL;
}

/**
 * Inicializa las impresoras
 */
void init_impr(Impr **imprs, int n_impr) {
    colaFifo = nuevaColaFifo();
    n = n_impr;
    for(int i=0;i<n_impr;i++){
        pthread_create(&t[i],NULL,t_imprimir,imprs[i]);
    }
}

/**
 * Entierra los threads que ocupaba cada impresora
 */
void terminar_impr() {
    for(int i=0;i<n;i++){
        if(pthread_join(t[i],NULL)!=0){
            break;
        }
    }
}

/**
 * Crea una orden de impresion para el documento
 */
Orden *imprimir_asinc(Doc *doc) {
    Orden *ord = malloc(sizeof(Orden));
    ord->doc=doc;
    ord->listo=0;
    agregar(colaFifo,ord);
    pthread_cond_broadcast(&cond);
    return ord;
}
/**
 * Confirma que una orden este terminada
 */
void confirmar(Orden *ord) {
    while(!ord->listo){
        pthread_cond_wait(&cond,&m);
    }
    free(ord);
}