#include <stdio.h>
#include <stdlib.h>

enum colors {red, black};

typedef struct NODE *node;

typedef struct NODE{
	int key;
	int cor;
	node right, 
         left, 
         father;
}NODE;

struct RN{
	NODE *raiz;
};

typedef struct RN *RN;

static node externo = NULL;

RN createRN();
static node createNode(int key);
static void rotationLeft(RN tree, node x);
static void rotationRight(RN tree, node x);
static void RBinsertFixup(RN tree, node z);
int insertTree(RN tree, int key);
static void imprimeArvore(node x);
void imprimir(RN tree);
static node searchNode(node x, int key); 
static void transplantRN(RN T, node u, node v);
static node treeMin(node x) ;
static void arrangeRNRemocao(RN T, node x);
static void removeRN(RN T, node z);
int remover(RN tree, int key);
static void freeNode(node atual);
void preOrder(node pt);
void inOrder(node pt);
void posOrder(node pt);

void preOrder(node pt){
    if(pt != externo){
        printf(("-%d(%d)"), pt->key, pt->cor);
        preOrder(pt->left);
        preOrder(pt->right);
    }
}

void inOrder(node pt){
    if(pt != externo){
        inOrder(pt->left);
        printf(("- %d (%d) "), pt->key, pt->cor);
        inOrder(pt->right);
    }
}

void posOrder(node pt){
    if(pt != externo){
        posOrder(pt->left);
        posOrder(pt->left);
        printf(("- %d (%d) "), pt->key, pt->cor);
    }
}

RN createRN() {
    if (externo == NULL) {
        externo = malloc(sizeof(NODE));
        // externo = calloc(1, sizeof(NODE));
        externo->cor = black;
        externo->right = externo; 
        externo->left = externo;
        externo->father = externo;
    }
    RN new_tree = calloc(1, sizeof(struct RN));
    new_tree->raiz = externo;
    return new_tree;
}

static node createNode(int key) {
    node pt = malloc(sizeof(NODE));
    // node novo = calloc(1, sizeof(NODE));
    pt->key = key;
    pt->cor = red;
    pt->right = externo;
    pt->left = externo;
    pt->father = externo;
    return pt;
}

int insertTree(RN tree, int key) {
    node y, x, z;
    z = createNode(key);

    y = externo;
    x = tree->raiz;
    
    while (x != externo) {
        y = x;
        if (z->key == x->key) return 1;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }
    
    z->father = y;
    if (y == externo) tree->raiz = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    
    z->left = externo;
    z->right = externo;
    z->cor = red;

    RBinsertFixup(tree, z);
    return 0;
}

static void RBinsertFixup(RN tree, node z) {
	node y;
    while (z->father->cor == red) {
        if (z->father == z->father->father->left) {
        	y = z->father->father->right;
	        if (y->cor == red) {
                z->father->cor = black;
                y->cor = black;
                z->father->father->cor = red;
                z = z->father->father;
            } else {
            	if (z == z->father->right) {
                    z = z->father;
                    rotationLeft(tree, z);
                }
                z->father->cor = black;
                z->father->father->cor = red;
                rotationRight(tree, z->father->father);
            }
        } else {
            y = z->father->father->left;
            if (y->cor == red) {
                z->father->cor = black;
                y->cor = black;
                z->father->father->cor = red;
                z = z->father->father;
            } else {
                if (z == z->father->left) {
                    z = z->father;
                    rotationRight(tree, z);
                }
                z->father->cor = black;
                z->father->father->cor = red;
            	rotationLeft(tree, z->father->father);
            }	
        }
    }
    tree->raiz->cor = black;
}

static void rotationLeft(RN tree, node x) {
    node y;
    y = x->right;
    x->right = y->left;
    if (y->left != externo) y->left->father = x;
    y->father = x->father;
    if (x->father == externo) tree->raiz = y;
    else if (x == x->father->left) x->father->left = y;
    else
        x->father->right = y;
    y->left = x;
    x->father = y;
}

static void rotationRight(RN tree, node x) {
    node y;
    y = x->left;
    x->left = y->right;
    if (y->right != externo) y->right->father = x;
    y->father = x->father;
    if (x->father == externo) tree->raiz = y;
    else if (x == x->father->right) x->father->right = y;
    else
        x->father->left = y;
    y->right = x;
    x->father = y;
}

static node searchNode(node x, int key) {
    if (x == externo || x->key == key) return x;
    if (key < x->key) searchNode(x->left, key);
    else searchNode(x->right, key);
}

int remover(RN tree, int key) {
    node z = searchNode(tree->raiz, key);
    node aux = z;
    if (z == externo) return 1;
    else
        removeRN(tree, z);
    free(aux);
    return 0;
}

static void removeRN(RN T, node z) {
    node x, y = z;

    int yCorOriginal = y->cor;

    if (z->left == externo) {
        x = z->right;
        transplantRN(T, z, z->right);
    } else if (z->right == externo) {
        x = z->left;
        transplantRN(T, z, z->left);
    } else {
        y = treeMin(z->right);
        yCorOriginal = y->cor;
        x = y->right;
        if (y->father == z) x->father = y;
        else {
            transplantRN(T, y, y->right);
            y->right = z->right;
            y->right->father = y;
        }
        transplantRN(T, z, y);
        y->left = z->left;
        y->left->father = y;
    }
    if (yCorOriginal == black) arrangeRNRemocao(T, x);
}

static void transplantRN(RN T, node u, node v) {
    if (u->father == externo) T->raiz = v;
    else if (u == u->father->left) u->father->left = v;
    else 
        u->father->right = v;
    v->father = u->father;
}

static void arrangeRNRemocao(RN T, node x) {
    node w;
    while (x != T->raiz && x->cor == black) {
        if (x == x->father->left) {
            w = x->father->right;
            if (w->cor == red) {
                w->cor = black;
                x->father->cor = red;
                rotationLeft(T, x->father);
                w = x->father->right;
                // printf("caso 1 onde o irmao 2 de x e` vermelho\n");
            }
            if (w->left->cor == black && w->right->cor == black) {
                w->cor = red;
                x = x->father;
                // printf("caso 2 onde o irmao w de x e` preto e os filhos de w sao pretos\n ");
            } else {
                if (w->right->cor == black) {
                    w->left->cor = black;
                    w->cor = red;
                    rotationRight(T, w);
                    w = x->father->right;
                    // printf("rotacao dupla\n");
                    // printf("o irmao w de x eh preto, o filho a esquerda de w eh vermelho e o filho a direita de w eh preto\n")
                }
                w->cor = x->father->cor;
                x->father->cor = black;
                w->right->cor = black;
                rotationLeft(T, x->father);
                x = T->raiz;
                // printf("o irmao w de x eh preto e o filho a direita de w eh vermelho\n");
            }
        } else {
            w = x->father->left;
            if (w->cor == red) {
                w->cor = black;
                x->father->cor = red;
                rotationRight(T, x->father);
                w = x->father->left;
            }
            if (w->right->cor == black && w->left->cor == black) {
                w->cor = red;
                x = x->father;
            } else {
                if (w->left->cor == black) {
                    w->right->cor = black;
                    w->cor = red;
                    rotationLeft(T, w);
                    w = x->father->left;
                    // printf("rotacao dupla\n");
                }
                w->cor = x->father->cor;
                x->father->cor = black;
                w->left->cor = black;
                rotationRight(T, x->father);
                x = T->raiz;
            }
        }
    }
    x->cor = black;
}

static node treeMin(node x) {
    node y = x;
    while (y->left != externo)
        y = y->left;
    return y;
}

void destroy(RN tree) {
    freeNode(tree->raiz);
    tree->raiz = externo;
}

static void freeNode(node current) {
    if (current == externo) return;
    freeNode(current->left);
    freeNode(current->right);
    free(current);
}

int main(){
    RN tree;
    tree = createRN();
    int ch, data;
    while(1){
        printf("\n1. Insert\n2. Delete\n3. Output\n4. Exit\n");
        scanf("%d", &ch);
        switch(ch){
			case 1:
				printf("Input the key:");
                scanf("%d", &data);
                if (insertTree(tree, data)) printf("Number [%d] already exists.\n", data);
                    else
                        printf("Number [%d] inserida.\n", data);
                break;
            case 2:
                printf("Delete the number:");
                scanf("%d", &data);
                if (remover(tree, data)) printf("Number [%d] not found.\n", data);
                    else
                        printf("Number [%d] remove.\n", data);
                break;
			case 3:
                printf("\nTree RN:\n");
                preOrder(tree->raiz);
                break;
            case 4:
                exit(0);
            default:
				printf("Wrong!!\n");
                break;
            }
       	printf("\n");
    }
	
	return 0;
}