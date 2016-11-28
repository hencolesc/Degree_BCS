// Exercicio 16 da Lista 1 de Oficina de Computação. Autor: Henrique Colodetti Escanferla.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

float somaval(float [], int);

void main()
{
int i=0; // i=> indice do vetor "v".
float v[30], aux; // aux=> receberá nºs reais.

scanf("%f", &aux);
while (aux!=0 && i<30)
	{
	v[i]=aux;
	scanf("%f", &aux);
	i++;
	}
printf("A soma dos %d valores digitados eh de: %f\n", i, somaval(v, i));
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

float somaval(float v[], int tam)
{
float soma=0; // soma=> guarda os valores somando-os aqui. 
int i; // i=> indice do vetor.  

for (i=0; i<tam; i++)
	{
	soma+=v[i];
	}
return soma;
}
