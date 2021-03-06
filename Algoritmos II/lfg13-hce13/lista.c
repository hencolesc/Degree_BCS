#include "lista.h"

/*Preencher com o c�digo fonte */
inline lista *FLVazia()
{
	lista *a = (lista*)malloc(sizeof(lista));
	a->ini = (item*)malloc(sizeof(item));
	a->fim = a->ini;
	a->fim->p = NULL;
	return a;
}

inline int vazia(lista a)
{
	return (a.ini == a.fim);
}

inline void insere(int ind, float coef, lista *a)
{
	a->fim->p = (item*)malloc(sizeof(item));
	a->fim = a->fim->p;
	a->fim->ind = ind;
	a->fim->coef = coef;
	a->fim->p = NULL;
} 

inline void retira(item *p,lista *a)
{
	if(vazia(*a) || p == NULL || p->p == NULL)
	{
		printf("Erro: Lista vazia ou posicao inexistente \n");	
		return;
	}
	item *q = p->p;
	p->p = q->p;
	if(p->p == NULL) a->fim = p;
	free(q);
}
