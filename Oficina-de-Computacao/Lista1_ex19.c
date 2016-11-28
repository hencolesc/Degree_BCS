// Exercicio 19 da Lista 1 de Oficina de Computação. Autor: Henrique Colodetti Escanferla.
#include <stdio.h>
#include <stdlib.h>
#define tam_max 501

void contafreq(int []);

void main()
{
int i=0; // i=> indice do vetor "v".
int ent[tam_max], aux; // aux=> receberá nºs.

printf("Digite uma sequencia de inteiros terminada por 0: ");
scanf("%d", &aux);
while (aux!=0 && i<tam_max)
	{
	ent[i]=aux;
	scanf("%d", &aux);
	i++;
	}
ent[i]=0; // Final da sequencia.
contafreq(ent);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

void contafreq(int ent[])
{
int k, aux, cont_ent; // k=> indice de vetor; cont_ent=> contador de ocorrencias em vetor; aux=> receberá inteiros.

printf("Digite uma sequencia de inteiros terminada por 0: ");
scanf("%d", &aux);
while (aux!=0)
	{
	for (k=0, cont_ent=0; ent[k]!=0 && cont_ent==0; k++) // Contador de ocorrencias.
		{
		if (aux==ent[k])
			cont_ent++;
		}
	if (cont_ent)
		printf("\nPertence.\n");
	else
		printf("\nNao pertence.\n");
	scanf("%d", &aux);
	}
}
