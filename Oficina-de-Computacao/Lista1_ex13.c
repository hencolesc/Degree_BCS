// Exercicio 13 da Lista 1 de Oficina de Computação. Autor: Henrique Colodetti Escanferla.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define num_hab 501

float med_sal(int, float []);
int maior_idade(int, int []);
int menor_idade(int, int []);
float med_idade(int, int []);
int quant(int, char [], float [], int []);

void main()
{
int i=0, idade[num_hab], filhos[num_hab];
float salario[num_hab];
char sexo[num_hab];

printf("Digite a idade: ");
scanf("%d", &idade[0]);
printf("\n");
while (idade[i]!=0) // Condição do fim da entrada de dados.
	{
	printf("Digite o sexo (\"m\" ou \"f\"): ");
	scanf("%c", &sexo[i]);
	scanf("%c", &sexo[i]);
	printf("\n");
	printf("Digite o salario (ex.: 500.55): ");
	scanf("%f", &salario[i]);
	printf("\n");
	printf("Digite o Nº de filhos: ");
	scanf("%d", &filhos[i]);
	printf("\n");
	i++;
	printf("Digite a idade: ");
	scanf("%d", &idade[i]);
	printf("\n");
	}
i--;
printf("A média salarial do grupo eh de: %f\n", med_sal(i, salario));
printf("A maior idade do grupo eh de: %d\n", maior_idade(i, idade));
printf("A menor idade do grupo eh de: %d\n", menor_idade(i, idade));
printf("A média da idade do grupo eh de: %f\n", med_idade(i, idade));
printf("A quantidade de mulheres que ganham até 500 reais e tem 3 filhos eh de: %d\n", quant(i, sexo, salario, filhos));
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

float med_sal(int tam, float salario[])
{
float soma=0;
int aux=tam; // Salva valor de "tam".

for (; tam>=0; tam--)
	{
	soma+=salario[tam];
	}
return soma/(aux+1);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

int maior_idade(int tam, int idade[])
{
int maior=0;

while (tam>=0)
	{
	if (idade[tam]>maior)
		maior=idade[tam];
	tam--;
	}
return maior;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

int menor_idade(int tam, int idade[])
{
int menor=idade[tam];
tam--;

while (tam>=0)
	{
	if (idade[tam]<menor)
		menor=idade[tam];
	tam--;
	}
return menor;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

float med_idade(int tam, int idade[])
{
float soma=0;
int aux=tam; // Salva valor de "tam".

for (; tam>=0; tam--)
	{
	soma+=idade[tam];
	}
return soma/(aux+1);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

int quant(int tam, char sexo[], float salario[], int filhos[])
{
int cont=0;

while (tam>=0)
	{
	if ((sexo[tam]=='f')&&(salario[tam]<=500)&&(filhos[tam]==3))
		cont++;
		tam--;
	}
return cont;
}
