#include <stdio.h>
#include <stdlib.h>

struct no
{
	int elemento;
	struct no *dir;
	struct no *esq;
	struct no *pai;
};
typedef struct no No;

No *raiz = NULL;

int tam = 7;
No *busca(int elemento, No *atual)
{
	if (atual == NULL)
	{
		return NULL;
	}
	else
	{
		if (atual->elemento == elemento)
		{
			return atual;
		}
		else
		{
			if (elemento < atual->elemento)
			{
				if (atual->esq == NULL)
				{
					return atual;
				}
				else
				{
					return busca(elemento, atual->esq);
				}
			}
			else
			{
				if (elemento > atual->elemento)
				{
					if (atual->dir == NULL)
					{
						return atual;
					}
					else
					{
						return busca(elemento, atual->dir);
					}
				}
			}
		}
	}
	return NULL;
}

void inserir(int elemento)
{
	if (elemento > 0)
	{
		No *aux;
		aux = busca(elemento, raiz);
		No *pt1 = malloc(sizeof(No));
		pt1->elemento = elemento;
		pt1->esq = NULL;
		pt1->dir = NULL;
		pt1->pai = NULL;
		if (aux == NULL)
		{
			raiz = pt1;
		}
		else
		{
			if (aux->elemento < elemento)
			{
				pt1->pai = aux;
				aux->dir = pt1;
			}
			else
			{
				pt1->pai = aux;
				aux->esq = pt1;
			}
		}
	}
}

void Remove(int elemento)
{
	No *aux = busca(elemento, raiz);
	No *lixo = aux;
	if (aux == NULL || aux->elemento != elemento)
	{
		printf("Nao e possivel remover o elemento %d\n", elemento);
	}
	else
	{
		if (aux->dir == NULL && aux->esq == NULL)
		{
			if (aux->elemento > aux->pai->elemento)
			{
				aux->pai->dir = NULL;
			}
			else
			{
				if (aux->elemento < aux->pai->elemento)
				{
					aux->pai->esq = NULL;
				}
			}
			free(lixo);
		}
		else
		{
			if (aux->dir == NULL || aux->esq == NULL)
			{
				if (aux->dir != NULL && aux->esq == NULL)
				{
					aux->pai->dir = aux->dir;
				}
				else
				{
					if (aux->esq != NULL && aux->dir == NULL)
					{
						aux->pai->esq = aux->esq;
					}
				}
				free(aux);
			}
			else
			{
				if (aux->dir != NULL && aux->esq != NULL)
				{
					aux = aux->esq;
					while (aux->dir != NULL)
					{
						aux = aux->dir;
					}
					int a = aux->elemento;
					Remove(aux->elemento);
					lixo->elemento = a;
				}
			}
			printf("Elemento removido com sucesso!!!\n");
		}
	}
}

void imprimirIN(No *aux)
{
	if (aux->esq != NULL)
	{
		imprimirIN(aux->esq);
	}
	printf("%d ", aux->elemento);
	if (aux->dir != NULL)
	{
		imprimirIN(aux->dir);
	}
}

void imprimirPOS(No *aux)
{
	if (aux->esq != NULL)
	{
		imprimirPOS(aux->esq);
	}
	if (aux->dir != NULL)
	{
		imprimirPOS(aux->dir);
	}
	printf("%d ", aux->elemento);
}

void imprimirPRE(No *aux)
{
	printf("%d ", aux->elemento);
	if (aux->esq != NULL)
	{
		imprimirPRE(aux->esq);
	}
	if (aux->dir != NULL)
	{
		imprimirPRE(aux->dir);
	}
}

int somapar(No *aux)
{
	if ((aux->dir == NULL) && (aux->esq == NULL))
	{
		if (aux->elemento % 2 == 0)
		{
			return aux->elemento;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if ((aux->dir != NULL) && (aux->esq != NULL))
		{
			if (aux->elemento % 2 == 0)
			{
				return aux->elemento + somapar(aux->dir) + somapar(aux->esq);
			}
		}
		else
		{
			if (aux->esq != NULL)
			{
				if (aux->elemento % 2 == 0)
				{
					return aux->elemento + somapar(aux->esq);
				}
				else
				{
					return somapar(aux->esq);
				}
			}
			else
			{
				if (aux->elemento % 2 == 0)
				{
					return aux->elemento + somapar(aux->dir);
				}
				else
				{
					return somapar(aux->dir);
				}
			}
		}
	}
	return 0;
}

int main()
{
	inserir(500);
	inserir(400);
	inserir(600);
	inserir(350);
	inserir(450);
	inserir(550);
	inserir(650);
	inserir(300);
	Remove(300);
	imprimirIN(raiz);
	printf("\n------------------------------------------\n");
	imprimirPOS(raiz);
	printf("\n------------------------------------------\n");
	imprimirPRE(raiz);
	return 0;
}
