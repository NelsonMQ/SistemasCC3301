#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "integral.h"
#include <stdlib.h>
#include <sys/wait.h>

/*
* Calcula una integral en "p" procesos.
*/
double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p) {
    double sub_intervalo = (xf-xi)/p;
    int pids[p];
    int infds[p];

    for(int i=0;i<p;i++){
        int fds[2];
        pipe(fds);
        if((pids[i]=fork())==0){
            close(fds[0]);
            double resp = integral(f,ptr,xi+sub_intervalo*i,xi+sub_intervalo*(i+1),n/p);
            write(fds[1],(char*)&resp, sizeof(resp));
            exit(0);
        }
        else{
            close(fds[1]);
            infds[i] = fds[0];
        }
    }
    double sum = 0;
    for(int k = 0;k<p;k++){
        double resp;
        read(infds[k],(char*)&resp, sizeof(resp));
        waitpid(pids[k],NULL,0);
        close(infds[k]);
        sum += resp;
    }
    return sum;
}