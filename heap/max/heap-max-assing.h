struct node
{
    int key;
};

typedef struct node Node;

struct heap
{
    int sizeofHeap, sizeMax;
    Node **Node;
};

typedef struct heap Heap;

Heap* Inicializar(int sizeMax);
Node* CriarNode(int key);
void Subir(int i, Heap* heap);
void Descer(int i, Heap* heap);
void Imprimir(Heap* heap);
void Inserir(Heap* heap, int key);
void Construir(Heap* heap);
void HeapSort(Heap* heap);
void DescerSize(int i, Heap *heap, int size);
void remover(Heap *heap);

