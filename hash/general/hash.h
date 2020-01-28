#include<stdio.h>
#include<stdlib.h>
#include "hash-assing.h"

// Methods for initialization and finalization
Hash* InicializarHash(int sizeMax){
    Hash* hash = (Hash*) malloc(sizeof(Hash));
    if(hash != NULL){
        int i;
        hash->sizeMax = sizeMax;
        hash->Node = (Node**) malloc(sizeMax * sizeof(Node*));
        if(hash->Node == NULL){
            free(hash);
            return NULL;
        }
        hash->amount = 0;
        for(i=0; i < hash->sizeMax; i++)
            hash->Node[i] = NULL;
    }
    return hash;
}

Node* CriarNode(int key){
    Node* node = (Node*) malloc(sizeof(Node));
    if(node != NULL){
        node->key = key;
        node->next = NULL;
        node->situacion = 0;
        return node;
    }
}

void freeHash(Hash* hash){
    if(hash != NULL){
        int i;
        for(i=0; i < hash->sizeMax; i++){
            if(hash->Node[i] != NULL)
                free(hash->Node[i]);
        }
        free(hash->Node);
        free(hash);
    }
}

// Methods for position search
int keyDivision(int key, Hash *hash){
    return abs(key) % hash->sizeMax;
}

int keyMultiplication(int key, Hash *hash){
    double cte = 0.6180339887; // Aurea cte
    double value = key * cte;
    value = value - (int) value;
    return (int) (hash->sizeMax * value);
}

// Methods for manipulation the hash
int insertHash(Hash *hash, int key){
    if(hash != NULL && hash->amount < hash->sizeMax){
        Node *node = CriarNode(key);
        if(node == NULL)
            return 0;
        
        int position = keyDivision(key, hash);
        //int position = keyMultiplication(key, hash);
        //int position = keyFold(key, hash);

        if(hash->Node[position] != NULL){
            printf("colision\n");
        }
        hash->Node[position] = node;
        hash->amount++;
        return 1;
    }
    return 0;
}

int insertHashTratamentInt(Hash *hash, int key){
    int a;    
    Node *node = CriarNode(key);
    if(node == NULL)
        return 0;    
    Node *end = searchHashTratamentInt(hash, key, &a);
    Node *j = NULL;
    int aux = keyDivision(key, hash);
    if(a!=1){
        if(end!=NULL && end->situacion == 0) 
            j = end;
        else{
            j = end;
            int i = 0;
            while (i <= hash->sizeMax){
                if(hash->Node[aux]->situacion = 1){
                    aux = (aux-1+hash->sizeMax)%hash->sizeMax;
                    i++;
                }
                else{
                    i = hash->sizeMax + 2;
                }
            }
            if(i == hash->sizeMax+1){
                printf("overflow\n");
                return 0;
            }
            Node *point_aux = j->next;
            j->next = hash->Node[aux]->next;
            hash->Node[aux]->next = point_aux;
            printf("Colision key %d", key);
        }
        hash->Node[aux]->key = key;
        hash->Node[aux]->situacion = 1;
        return 1;
    }else{
        printf("Key exist\n");
        return 0;
    }
}

int insertHashTratamentExt(Hash *hash, int key){
    if(hash != NULL){
        // Before it was like this
        // if(hash != NULL && hash->amount < hash->sizeMax)
        Node *node = CriarNode(key);
        if(node == NULL)
            return 0;    
        
        int position = keyDivision(key, hash);
        // int position = keyMultiplication(key, hash);
        // int position = keyFold(key, hash);

        if(hash->Node[position] != NULL){
            Node* aux = hash->Node[position];
            while(aux->next!=NULL)
                aux = aux->next;   

            aux->next = node;
        }else{
            hash->Node[position] = node;
        }
        hash->Node[position]->situacion = 1;
        hash->amount++;
        return 1;
    }
    return 0;
}

void removeHash(Hash* hash, int key){
    if(hash != NULL){
        int position = keyDivision(key, hash);
        //int position = keyMultiplication(key, hash);
        //int position = keyFold(key, hash);
        hash->Node[position] = NULL;
        hash->amount--;
    }
}

void removeHashTratamentInt(Hash* hash, int key){
    if(hash != NULL){
        int position = keyDivision(key, hash);
        //int position = keyMultiplication(key, hash);
        //int position = keyFold(key, hash);
        int aux = position;
        while (hash->Node[aux]->key!=key && aux<hash->sizeMax){
            aux++;
        }
        if(hash->Node[aux]->key==key)
            hash->Node[aux] = NULL;
        hash->amount--;
    }
}

int removeHashTratamentExt(Hash* hash, int key){
    if(hash != NULL){
        int position = keyDivision(key, hash);
        //int position = keyMultiplication(key, hash);
        //int position = keyFold(key, hash);
        Node* node = hash->Node[position];
        Node* aux = hash->Node[position];   
        int a = 1;
        // while (a){
        //     if(node != NULL){
        //         a = 0;
        //     }else{
        //         a = 1;
        //         aux = node;
        //         node = node->next;
        //     }
        // }  
        printf("entrouu");
        if(node->key == key){
            printf("entrouu");
            hash->Node[position]->situacion = 0;
            hash->Node[position]->key = 0;
            node->situacion = 0;
            hash->amount--;
            node->key -55;
        }else{
            while (a)
            {
                node = node->next;
                if(node->key == key && node!= NULL){
                    node->situacion = 0;
                    hash->amount--;
                    a = 0;  
                }
                if(node==NULL)
                    return 0;
            }
        }
                  
        
        if(node==NULL)
            return 0;
        // aux->next = node;
        // hash->Node[position] = NULL;
        return 0;
    }
}

int searchHash(Hash* hash, int key){
    if(hash == NULL)
        return -1;

    int position = keyDivision(key, hash);
    //int position = keyMultiplication(key, hash);
    //int position = keyFold(key, hash);

    if(hash->Node[position] == NULL)
        return 0;
    return 1;
}

Node *searchHashTratamentInt(Hash* hash, int key, int *a){
    if(hash == NULL)
        return NULL;

    int position = keyDivision(key, hash);
    //int position = keyMultiplication(key, hash);
    // int position = keyFold(key, hash);

    Node *end = hash->Node[position];
    Node *aux = hash->Node[position];
    Node *j = NULL;    
    *a = *a-*a;
    
    while(*a == 0){
        if(end == NULL){
            return end;
        }
        if(end->situacion == 0){
            j = end;
        }
        if(end->key == key && end->situacion == 1){
            *a = 1;
        }else{
            end = end->next;
            if(end == aux){
                *a = 2;
                end = j;
            }
        }
    }
    return end;
}

int searchHashTratamentExt(Hash* hash, int key){
    if(hash == NULL)
        return -1;

    int position = keyDivision(key, hash);
    //int position = keyMultiplication(key, hash);
    //int position = keyFold(key, hash);

    if(hash->Node[position] == NULL)
        return 0;
    else{
        Node *aux;
        aux = hash->Node[position];
        while(hash->Node[position]->key!=key && hash->Node[position]->next!=NULL)
            aux = aux->next;
        return 0;
    }    
    return 1;
}

void imprimirHash(Hash* hash){
    for(int i = 0; i < hash->sizeMax; i++){
        if(hash->Node[i]!=NULL){
            Node* node = hash->Node[i];
            if(hash->Node[i]->situacion == 1)
                printf("\nposition [%d]", i);
            while (node!=NULL){
                if(hash->Node[i]->situacion == 1)                
                    printf(" -> %d", node->key);
                node = node->next;
            }
        }else
            printf("\n Null");
    }
    printf("\n");
}   

void imprimirHashI(Hash* hash){
    for(int i = 0; i < hash->sizeMax; i++){
        if(hash->Node[i]!=NULL){
            Node* node = hash->Node[i];
            if(hash->Node[i]->situacion == 1)
                printf("\nposition [%d] -- %d", i, hash->Node[i]->key);
            }else
                printf("\n Null");
    }
    printf("\n");
}