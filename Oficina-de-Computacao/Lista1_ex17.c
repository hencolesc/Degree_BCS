// Exercicio 17 da Lista 1 de Oficina de Computação. Autor: Henrique Colodetti Escanferla.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define tam_max 502

void contafreq(char [], char []);

void main()
{
int i=0; // i=> indice do vetor "v".
char ent[tam_max], sai[tam_max], aux; // aux=> receberá caracteres.

scanf("%c", &aux);
while (aux!='\n' && i<tam_max)
	{
	ent[i]=aux;
	scanf("%c", &aux);
	i++;
	}
ent[i]='\0'; // Final da string.
contafreq(ent, sai);
printf("%s\n", sai);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

void contafreq(char ent[], char sai[])
{
int i, j, k, l, cont_sai, cont_ent; // i, j, k, l=> indices de vetores; cont_sai, cont_ent=> contadores de ocorrencias em vetor.

sai[0]='\0'; // Desloca o fim da string p/ o seu começo.
for (i=0, l=0; ent[i]!='\0'; i++)
	{
	for (j=0, cont_sai=0; sai[j]!='\0'; j++)
			{
			if (ent[i]==sai[j]) // Elemento ja foi registrado, passar p/ o próx.
				{
				cont_sai++;
				break;
				}
			}
	if (!cont_sai) // Elemento não foi registrado.
		{
		for (k=0, cont_ent=0; ent[k]!='\0' && cont_ent<3; k++) // Contador de ocorrencias.
			{
			if (ent[i]==ent[k])
				cont_ent++;
			}
		if (cont_ent==3)
			{
			sai[l+1]=sai[l]; // O fim da string é deslocado em uma cédula.
			sai[l]=ent[i]; // Salva elemento p/ não ser verificado de novo e retorna-o por referência.
			l++;
			}
		}
	}
}
