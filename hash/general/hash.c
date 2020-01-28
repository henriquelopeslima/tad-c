#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash.h"

int main(){
    srand(time(NULL));
    Hash *hash;
    // Division
    hash = InicializarHash(7);
    // Multiplication
    //hash = InicializarHash(10);
    // Fold
    //hash = InicializarHash(1000);
    // Analysis 
    // hash = InicializarHash(32);

    printf("====== Chaves Inseridas ======\n");
    for(int i = 0; i < 3; i++){
        int a = rand();
        // printf("- %d -", a);
        insertHashTratamentExt(hash, a);  
    }
    insertHashTratamentExt(hash, 14);
    insertHashTratamentExt(hash, 7);
    insertHashTratamentExt(hash, 21);
    insertHashTratamentExt(hash, 49);
    
    removeHashTratamentExt(hash, 14);
    
    insertHashTratamentExt(hash, 3);  
    insertHashTratamentExt(hash, 0);
    insertHashTratamentExt(hash, 33);  
    insertHashTratamentExt(hash, 20);  
    imprimirHash(hash);
     return 1;
}