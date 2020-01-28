struct node
{
    int key;
    struct node* next;
    int situacion;
};

typedef struct node Node;

struct hash
{
    int amount, sizeMax;
    Node **Node;
};

typedef struct hash Hash;

Hash* InicializarHash(int sizeMax);
Node* CriarNode(int key);
void freeHash(Hash* hash);
void imprimirHash(Hash* hash);

int keyDivision(int key, Hash *hash);
int keyMultiplication(int key, Hash *hash);
int keyFold(int key, Hash *hash);

int insertHash(Hash *hash, int key);
int searchHash(Hash* hash, int key);
void removeHash(Hash* hash, int key);

int insertHashTratamentInt(Hash *hash, int key);
Node *searchHashTratamentInt(Hash* hash, int key, int *a);
void removeHashTratamentInt(Hash* hash, int key);

int insertHashTratamentExt(Hash *hash, int key);
int searchHashTratamentExt(Hash* hash, int key);
int removeHashTratamentExt(Hash* hash, int key);

