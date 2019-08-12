
#include "t1.h"

typedef unsigned int uint;
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

