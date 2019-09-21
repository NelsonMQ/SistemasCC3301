#include <stdio.h>
#include <stdlib.h>

/*
 * Entrega la cantidad de elementos que hay en la cola, dado el archivo.
 */
int cantidad_cola(FILE *in){
    char buf[4];
    fread(buf,1,4,in);
    return atoi(buf);
}

/*
 * Entrega la posicion del elemento con mejor prioridad, dado el archivo y la cantidad de elementos.
 */
int buscar_prioritario(int n,FILE *in){
    int j=10000;
    int h;
    for(int i=0;i<n;i++){
        char buf2[6];
        fseek(in,15+i*17,SEEK_SET);
        fread(buf2,1,6,in);
        if(j>atoi(buf2)){
            h=i;
            j=atoi(buf2);
        }
    }
    return h;
}

/*
 * Muestra en pantalla el nombre del elemento que se indica, dado el archivo y su posicion en este.
 */
void mostrar_nombre(int h,FILE *in){
    char buf3[11];
    fseek(in,5+h*17,SEEK_SET);
    fread(buf3,1,10,in);
    buf3[10]='\0';
    printf("%s \n",buf3);
}

/*
 * Copia la linea "i" a la linea "j"
 */
void cambiar_linea(int i, int j, FILE *in){
    char buf[17];
    fseek(in,5+i*17,SEEK_SET);
    fread(buf,1,17,in);
    fseek(in,5+j*17,SEEK_SET);
    fwrite(buf,1,17,in);
}

/*
 * Cambia en el archivo la cantidad de elementos a una nueva cantidad "j".
 */
void cambiar_cantidad(FILE *in, int j){
    char buf[6];
    sprintf(buf,"%-4d\n",j);
    fseek(in,0,SEEK_SET);
    fwrite(buf,1,5,in);
}

/*
 * Saca los elementos en orden de prioridad, mostrando sus nombres y actualizando el archivo.
 */
int main(int argc, char **argv){
    FILE *in = fopen(argv[1],"r+");
    int n = cantidad_cola(in);
    if(n==0){
        printf("%s \n","error: cola.txt esta vacia");
        return 0;
    }
    int h = buscar_prioritario(n,in);
    mostrar_nombre(h,in);
    cambiar_linea(n-1,h,in);
    cambiar_cantidad(in,n-1);
    fclose(in);
    return 0;
}