#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node* left;
    struct node* right;
};

struct tree{
    struct node* tree;
};

typedef struct node node;
typedef struct node tree;

node *raiz = NULL;
node *father = NULL;

node* createNode(){
	node* NO = malloc(sizeof(node));
    NO->left = NULL;
    NO->right = NULL;
    return NO;
}

node* createTree(){
	tree* TREE = malloc(sizeof(tree));
    return TREE;
}

void preOrder(node *ptraiz){
    if(ptraiz != NULL){
        printf("| %d ",ptraiz->key);
        preOrder(ptraiz->left);
        preOrder(ptraiz->right);
    }
}

void inOrder(node *ptraiz){
    if(ptraiz != NULL){
        inOrder(ptraiz->left);
        printf(" | %d ",ptraiz->key);
        inOrder(ptraiz->right);
    }
}

void posOrder(node *ptraiz){
    if(ptraiz != NULL){
        posOrder(ptraiz->left);
        posOrder(ptraiz->right);
        printf(" | %d ",ptraiz->key);
    }
}

// x eh o inteiro, pt eh a raiz, f eh o inteiro que vai indicar um significado sobre o ponteiro encontrado
node* search(int x, node *pt, int *f){
    if(pt == NULL){
        *f = 0;
        return NULL;
    }else{
        if(x == pt->key){
            *f = 1;
            return pt;
        }else{
            if(x < pt->key){
                if(pt->left == NULL){
                    *f = 2;
                    return pt;
                }else{
                   return search(x, pt->left, f); 
                }
            }else{
                if(pt->right == NULL){
                    *f = 3;
                    return pt;
                }else{
                    return search(x, pt->right, f);
                }
            }
        }
    }
}

// x eh o inteiro, pt eh a raiz, f eh o inteiro que vai indicar um significado sobre o ponteiro encontrado, father eh um ponteiro que aponta para o pai de pt
node* searchFather(int x, node *pt, int *f, node **father){
    if(pt == NULL){
        *f = 0;
        *father = NULL;
        return NULL;
    }else{
        if(x == pt->key){
            *f = 1;
            return pt;
        }else{
            *father = pt;
            if(x < pt->key){
                if(pt->left == NULL){
                    *f = 2;
                    return pt;
                }else{
                    return searchFather(x, pt->left, f, father); 
                }
            }else{
                if(pt->right == NULL){
                    *f = 3;
                    return pt;
                }else{
                    return searchFather(x, pt->right, f, father);
                }
            }
        }
    }
}

// passe um ponteiro para encontrar o sucessor dele e passe um ponteiro de ponteiro para guardar o pai do sucessor
node* successor(node *pt, node  **pai_s){
    node *s = pt->right;
    if(s != NULL){
        while (s->left != NULL)
        {
            *pai_s = s;
            s = s->left;
        }
    }
    return s;
}

node* moveFather(node **pt1, node **pt, node **pt2){
    if(*pt1 == NULL){
        raiz = *pt2;
    }else{
        if(*pt == (*pt1)->left){
            (*pt1)->left = *pt2;
        }else{
            (*pt1)->right = *pt2;
        }
    }
    return NULL;
}

void remover(int x, node *pt, int *f, node *pt1){
    pt = raiz;
    pt = searchFather(x, pt, f, &pt1);
    if(*f!=1){
        printf("Element not exist\n");
        if(pt->left == NULL)
            moveFather(&pt1, &pt, &pt->right);
        else{
            if(pt->right == NULL){
                moveFather(&pt1, &pt, &pt->left);
            }else{
                node *s, *pai_s;
                s = successor(pt, &pai_s);
                if(pt->right != s) {
                    moveFather(&pai_s, &s, &(s->right));
                    s->right = pt->right;
                }
                moveFather(&pt1, &pt, &s);
                s->left = pt->left;
            }
        }
    }
}

int heightBST(node *pt){
    //
}

void insert(node *ptraiz, int x){
    node *pt = ptraiz;
    int f;
    pt = search(x, pt, &f);
    if(f == 1){
        printf("Invalid insertion\n");
    }
    else{
        node* no = createNode();
        no->key = x;
        if(f == 0){
            raiz = no;
        }else
        {
            if(f == 2)
                pt->left = no;
            else
                pt->right = no;                
        }
    }
}

int main(){

    raiz = NULL;    
    node *no;
    node *fat;
    no = raiz;
    int t = 0;    
    fat = NULL;

    insert(raiz, 12);
    insert(raiz, 2);
    insert(raiz, 14);
    insert(raiz, 13);
    insert(raiz, 11);
    insert(raiz, 3);
    insert(raiz, 20);
    insert(raiz, 1);

    preOrder(raiz);
    printf("|\n");
    
    // node *s, *father;
    // s = successor(raiz, &father);    
    // printf("o sucessor de %d eh s %d\n",raiz->key ,s->key);
    // printf("o pai do sucessor eh %d",father->key);
    
    // father = searchFather(3, raiz, &t, &fat);

    // if(fat != NULL){
    //    printf("\n-tree : %d\n-father : %d\n-son : %d\n", raiz->key, fat->key, father->key);
    // }else{  
    //     printf("eh nulo\n");
    // }

    // int j;
    // father=NULL;
    // remover(12, raiz, &j, father);
    
    
    preOrder(raiz);
    printf("|\n");

    return 0;
}