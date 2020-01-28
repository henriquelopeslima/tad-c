#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap-max.h"

int main()
{
    Heap *new_heap = Inicializar(100);
    int i;
   
    for(i = 0; i < 9; i++){
        int a;
        scanf("%d", &a);
        Inserir(new_heap, a);
    }

    Imprimir(new_heap);
    HeapSort(new_heap);
    Imprimir(new_heap);
    Construir(new_heap);
    Imprimir(new_heap);
    remover(new_heap);
    Imprimir(new_heap);
    Inserir(new_heap, 8);
    Imprimir(new_heap);
    return 1;
}