// Exercicio 14 da Lista 1 de Oficina de Computação. Autor: Henrique Colodetti Escanferla.
#include <stdio.h>
#define tam_max 501

int obtem_vetor(int [], int, int);


void main()
{
int v[tam_max], tam, stop;

printf("Digite o tamanho maximo do vetor, de 0 a %d: ", tam_max);
scanf("%d", &tam);
printf("\nDigite o nº inteiro indicador do final da sequencia de entrada: ");
scanf("%d", &stop);
printf("\nA quantidade de nºs lidos foi de: %d\n", obtem_vetor(v, tam, stop));
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

int obtem_vetor(int v[], int tam, int stop)
{
int i=0, aux; // i=> indice do vetor "v".

scanf("%d", &aux);
while (i<tam && aux!=stop)
	{
	v[i]=aux;
	scanf("%d", &aux);
	i++;
	}
return i;
}
