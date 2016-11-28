#ifndef _lista_
#define _lista_

/* PREENCHER COM SUAS DEFINIÇÕES DE TIPOS E FUNÇÕES */

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct item
{
	float coef;
	int ind;
	struct item *p;
}item;

typedef struct
{
	item *ini, *fim;
}lista;

inline lista *FLVazia();
inline int vazia(lista a);
inline void insere(int ind, float coef, lista *a);
inline void retira(item *p,lista *a);

#endif
