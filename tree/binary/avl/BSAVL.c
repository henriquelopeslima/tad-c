#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

struct node
{
    int key;
    int bal;
    struct node* left;
    struct node* right;
};

struct tree{
    struct node* tree;
    int height;
};

typedef struct node node;
typedef struct tree tree;

node *ptraiz = NULL;

node* createNode(int x);
node* successor(node **pt, node  **pai_s);
void case1(node **pt, bool *h);
void case2(node **pt, bool *h);
bool isAVL(node *pt);
int insert(int x, node **pt, bool *h);
void removerAVL(int x, node **pt, bool *h);
void preOrder(node *pt);
void inOrder(node *pt);
void posOrder(node *pt);

node* createNode(int x){
    node* NO = malloc(sizeof(node));
    NO->left = NULL;
    NO->right = NULL;
    NO->bal = 0;
    NO->key = x;
    return NO;
}

node* successor(node **pt, node  **pai_s){
    node *s = (*pt)->right;
    *pai_s = (*pt);
    if(s != NULL){
        while (s->left!=NULL)
        {
            (*pai_s) = s;
            s = s->left;
        }
    }
    return s;
}

void case1(node **pt, bool *h){ 
    node *ptu, *ptv;
    ptu = (*pt)->left;
    if(ptu->bal <= 0){
        printf("Rigth rotation\n");
        (*pt)->left = ptu->right;
        ptu->right = (*pt);
        if(ptu->bal==0){
            (*pt)->bal=-1;
            ptu->bal=1;
            *h = false;
        }else{
            (*pt)->bal=0;
            ptu->bal=0;
        }
        (*pt) = ptu;
    }
    else{
        printf("Rigth-Left rotation\n");
        ptv = ptu->right;
        ptu->right = ptv->left;
        ptv->left = ptu;
        (*pt)->left = ptv->right;
        ptv->right = (*pt);
        if(ptv->bal == -1){
            (*pt)->bal = 1;
        }else{
            (*pt)->bal = 0;
        }
        if(ptv->bal == 1){
            ptu->bal = -1;
        }else{
            ptu->bal = 0;
        }
        (*pt) = ptv;
        ptv->bal=0;
    }
}

void case2(node **pt, bool *h){
    node *ptu, *ptv;
    ptu = (*pt)->right;
    if(ptu->bal >=0){
        printf("Left rotation %d\n",(*pt)->key);
        (*pt)->right = ptu->left;
        ptu->left = (*pt);
        if(ptu->bal==0){
            (*pt)->bal = 1;
            ptu->bal = -1;
            *h=false;
        }else{
            (*pt)->bal = 0;
            ptu->bal = 0;
            
        }
        (*pt) = ptu;
    }
    else{
        printf("Left-Rigth rotation\n");
        ptv = ptu->left;
        ptu->left = ptv->right;
        ptv->right = ptu;
        (*pt)->right = ptv->left;
        ptv->left = (*pt);
        if(ptv->bal == 1){
            (*pt)->bal = -1;
        }else{
            (*pt)->bal = 0;
        }
        if(ptv->bal == -1){
            ptu->bal = 1;
        }else{
            ptu->bal = 0;
        }
        (*pt) = ptv;
        ptv->bal = 0;
    }
}

int insert(int x, node **pt, bool *h){
    if((*pt) == NULL){
        node *no = createNode(x);
        (*pt)=no;
        *h = true;
    }else{
        if(x == (*pt)->key){
            printf("the key %d exist",x);
            return -1;
        }
        if(x < (*pt)->key){
            insert(x, &(*pt)->left, h);
            if(*h){
                switch ((*pt)->bal){
                    case 1 :
                        (*pt)->bal = 0; 
                        *h = false;
                        break;
                    case 0 :
                        (*pt)->bal = -1;
                        break;
                    case -1:
                        case1(&(*pt), h);
                        *h=false;
                        break;
                    default:
                        break;
                }
            } 
        }else{
            insert(x, &(*pt)->right, h);
            if(*h){
                switch ((*pt)->bal){
                    case -1 :
                        (*pt)->bal = 0; 
                        *h = false;
                        break;
                    case 0 :
                        (*pt)->bal = 1;
                        break;
                    case 1:
                        case2(&(*pt), h);
                        *h=false;
                        break;
                    default:
                        break;
                }
            } 
        }
    }   
}

void removerAVL(int x, node **pt, bool *h){
    if((*pt)==NULL){
        printf("Element not found\n");
    }else if(x < (*pt)->key){      
        removerAVL(x, &(*pt)->left, h);
        if(*h){
            switch ((*pt)->bal)
            {
                case -1 :
                    (*pt)->bal = 0;
                    break;
                case 0 :
                    (*pt)->bal = 1;
                    *h = false;
                    break;
                case 1 :
                    case2(&(*pt), h);
                    break;
            }
        }
    }else if(x > (*pt)->key){
                removerAVL(x, &(*pt)->right, h);
                if(*h){
                    switch ((*pt)->bal)
                    {
                    case 1:
                        (*pt)->bal = 0;
                        break;
                    case 0:
                        (*pt)->bal = -1;
                        *h = false;
                        break;
                    case -1:
                        case1(&(*pt), h);
                        break;
                    }
                }
    }else{
        node *aux = (*pt);
        if(aux->right == NULL){
            (*pt) = aux->left;
            *h = true;
        }else if(aux->left == NULL){
            (*pt) = (*pt)->right;
            *h = true;
        }else{
            node *pai_s;
            aux = successor(&aux, &pai_s);
            (*pt)->key = aux->key;
            removerAVL(aux->key, &(*pt)->right, h);
            if(aux->right == NULL && aux->left==NULL){
                if(*h){
                switch ((*pt)->bal){
                    case 1 :
                        (*pt)->bal = 0;
                        break;
                    case 0 :
                        (*pt)->bal = -1;
                        *h = 0;
                        break;
                    case -1 :
                        case1(&(*pt), h);
                        break;
                }
            
                }
            }
            else{
            if(*h){
                switch ((*pt)->bal){
                    case 1 :
                        (*pt)->bal = 0;
                        break;
                    case 0 :
                        (*pt)->bal = -1;
                        *h = 0;
                        break;
                    case -1 :
                        case2(&(*pt), h);
                        break;
                }
            
            }
            }
           free(aux);
        }  
    }  
}

void preOrder(node *pt){
    if(pt != NULL){
        printf(("|%d(%d)"), pt->key, pt->bal);
        preOrder(pt->left);
        preOrder(pt->right);
    }
}

void inOrder(node *pt){
    if(pt != NULL){
        inOrder(pt->left);
        printf(("| %d (%d) "), pt->key, pt->bal);
        inOrder(pt->right);
    }
}

void posOrder(node *pt){
    if(pt != NULL){
        posOrder(pt->left);
        posOrder(pt->left);
        printf(("| %d (%d) "), pt->key, pt->bal);
    }
}

int main(){

    int keys[] = {13,5,21,2,8,16,26,1,3,6,10,14,18,23,29,
    4,7,9,11,15,17,19,22,24,27,31,12,20,25,28,30,32,33};
    //int keys[] = {8, 5, 7, 4, 12,14, 10, 9, 3, 6, 11, 13}; // da lista
    //  int keys[] = {8, 5, 7, 4, 12,14, 10, 9, 3, 6, 11, 15, 16};
    // int keys[] = {83, 70, 65, 89, 98, 77, 79, 78, 87};
    // int keys[] = {8, 4, 15, 2, 6, 13, 16, 1, 3, 5, 7, 12, 14, 17, 11};
    
    // Create tree
    tree TREE;
    node *pt = NULL;
    TREE.tree = pt;

    bool h = false;

    
    // insert(8, &TREE.tree, &h);
    // insert(5, &TREE.tree, &h);
    // insert(7, &TREE.tree, &h);
    // insert(4, &TREE.tree, &h);
    // insert(12, &TREE.tree, &h);
    // insert(14, &TREE.tree, &h);
    // insert(10, &TREE.tree, &h);
    // insert(9, &TREE.tree, &h);
    // insert(3, &TREE.tree, &h);
    // insert(6, &TREE.tree, &h);
    // insert(11, &TREE.tree, &h);
    // insert(13, &TREE.tree, &h);
    //preOrder(TREE.tree);
    //printf("\n");
    // printf("inserindo\n");
    
    for(int i = 0; i < 33; i++){
         printf("Inserindo a chave %d\n", keys[i]);
         insert(keys[i], &TREE.tree, &h);
         preOrder(TREE.tree);
         printf("\n"); 
    }
    
    h = false;
    
    removerAVL(1, &TREE.tree, &h);
    preOrder(TREE.tree);
    printf("\n"); 
   

    // printf("Removendo\n");
    // for(int i = 0; i < 33; i++){
    //     printf("Removendo a chave %d\n",&keys[i]);
    //     removerAVL(keys[i], &TREE.tree, &h);
    //     preOrder(TREE.tree);
    //     printf("\n");
    // }
    
}