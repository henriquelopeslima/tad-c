#include <stdio.h>
#include <stdlib.h>
#include "heap-min-assing.h"

Heap* Inicializar(int sizeMax){
    Heap* heap = (Heap*) malloc(sizeof(Heap));
    if(heap != NULL){
        int i;
        heap->sizeMax = sizeMax;
        heap->Node = (Node**) malloc(sizeMax * sizeof(struct Node*));
        if(heap->Node == NULL){
            free(heap);
            return NULL;
        }
        heap->sizeofHeap = 0;
        for(i=0; i < heap->sizeMax; i++)
           heap->Node[i] = NULL;
    }
    return heap;
}

Node* CriarNode(int key){
    Node* node = (Node*) malloc(sizeof(Node));
    if(node != NULL){
        node->key = key;
        return node;
    }
}

void Imprimir(Heap *heap)
{   
    int i;
    printf("- ");
    for(i = 0; i < heap->sizeofHeap; i++)
        printf("%d  -  ",heap->Node[i]->key);
    printf("\n");
}

void Subir(int i, Heap* heap)
{
    int pai = (int) i/2;
    if(pai >= 1){
        if(heap->Node[pai-1]->key > heap->Node[i-1]->key){
            int aux = heap->Node[pai-1]->key;
            heap->Node[pai-1]->key = heap->Node[i-1]->key;
            heap->Node[i-1]->key = aux;
            Subir(pai, heap);
        }
    }
}

void Descer(int i, Heap *heap)
{
    int f = 2 * i;
    if(f <= heap->sizeofHeap){
        if(f<heap->sizeofHeap)
            if(heap->Node[f-1]->key > heap->Node[f]->key)
                f = f+1;
        if(heap->Node[i-1]->key > heap->Node[f-1]->key){
            int aux = heap->Node[i-1]->key;
            heap->Node[i-1]->key = heap->Node[f-1]->key;
            heap->Node[f-1]->key = aux;
            Descer(f, heap);    
        }
    }
}

void DescerSize(int i, Heap *heap, int size)
{
    int f = 2*i+1;
    if(f <= size){
        if(f<size)
            if(heap->Node[f]->key > heap->Node[1+f]->key)
                f = f+1;
        if(heap->Node[i]->key > heap->Node[f]->key){
            int aux = heap->Node[i]->key;
            heap->Node[i]->key = heap->Node[f]->key;
            heap->Node[f]->key = aux;
            DescerSize(f, heap, size);    
        }
    }
}

void Construir(Heap *heap)
{
    for(int i = (int) heap->sizeofHeap/2; i>=1; i--)
        Descer(i, heap);
}

void Inserir(Heap *heap, int key)
{
    if(heap->sizeofHeap < heap->sizeMax)
    {
        heap->Node[heap->sizeofHeap] = CriarNode(key);
        heap->Node[heap->sizeofHeap]->key = key;
        heap->sizeofHeap = (int) heap->sizeofHeap + 1;
        Subir(heap->sizeofHeap, heap);
    }
    else
    {
        printf("Overflow\n");
    }
}

void HeapSort(Heap* heap){    
    Construir(heap);
    int i = heap->sizeofHeap; 
    int aux = 0;
    for(i = heap->sizeofHeap-1; i>0; i--){
        aux = heap->Node[i]->key;
        heap->Node[i]->key = heap->Node[0]->key;
        heap->Node[0]->key = aux;
        DescerSize(0, heap, i-1);
    }
}

void remover(Heap *heap){
    int size = heap->sizeofHeap; 
    if(size!=0){
        int ele = heap->Node[0]->key;
        heap->Node[0]->key = heap->Node[size-1]->key;
        heap->sizeofHeap = size-1;
        Descer(1,heap); 
    }
}