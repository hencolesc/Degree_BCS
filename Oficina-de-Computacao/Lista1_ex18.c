// Exercicio 18 da Lista 1 de Oficina de Computação. Autor: Henrique Colodetti Escanferla.
#include <stdio.h>
#include <stdlib.h>
#define tam_max 501

void inverte(int [], int);

void main()
{
int i, aux, v[tam_max]; // i=> indice de vetor; aux=> receberá nºs.

scanf("%d", &aux);
for (i=0; aux!=0; i++)
	{
	v[i]=aux;
	scanf("%d", &aux);
	}
inverte(v, i); // Chama função definida nas linhas 23~30.
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

void inverte(int v[], int tam)
{
tam--;
for(; tam!=-1; tam--)
	{
	printf("%d\t", v[tam]);
	}
}
