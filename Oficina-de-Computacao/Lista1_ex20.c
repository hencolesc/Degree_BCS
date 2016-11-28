// Exercicio 20 da Lista 1 de Oficina de Computação. Autor: Henrique Colodetti Escanferla.
#include <stdio.h>
#include <stdlib.h>
#define tam_max 501

void main()
{
int i, j, eh_igual, aux, v[tam_max], w[tam_max]; // i e j=> indice de vetor; aux=> receberá inteiros; eh_igual=> indicador de igualdade.

v[0]=0; // Se as 2 sequencias forem nulas, serao tratadas como iguais, assim, essas duas linhas são necessarias para evitar lixo de memoria e um
w[0]=0; // comando erroneo de diferença entre as sequencias. v[0] é igual a w[0] de imediato.
scanf("%d", &aux);
for (i=0; aux!=0; i++)
	{
	v[i]=aux;
	scanf("%d", &aux);
	}
scanf("%d", &aux);
for (j=0; aux!=0; j++)
	{
	w[j]=aux;
	scanf("%d", &aux);
	}
if (i!=j) // Se seus tamanhos são diferentes as sequencias são diferentes de imediato, o outro caso é se alguma sequencia é nula.
	printf("As sequencias não sao iguais.\n");
else
	{
	for(i-=1, j-=1, eh_igual=1; eh_igual && i!=-1; i--, j--) // Loop da verificação de igualdade.
		{
		if (v[i]!=w[j]) // Verifica se é igual.
			eh_igual=0;
		}
	if (eh_igual)
		printf("As sequencias sao iguais.\n");
	else
		printf("As sequencias nao sao iguais.\n");
	}
}
