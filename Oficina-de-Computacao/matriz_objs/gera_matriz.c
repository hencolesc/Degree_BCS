// Gera matriz de linhas e colunas passados como argumento e escreve em arquivo
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define QUANT_ARG 4
#define INDICE_LINHA 1
#define INDICE_COLUNA 2
#define INDICE_NOME_ARQ 3


// A função RandomInteger devolve um inteiro
// aleatório entre low e high inclusive,
// ou seja, no intervalo fechado low..high.
// Vamos supor que 0 <= low <= high < INT_MAX.
// O código foi copiado da biblioteca random
// de Eric Roberts.

int RandomInteger( int low, int high)
{
    int k;
    double d;
    d = (double) rand( ) / ((double) RAND_MAX + 1);
    k = d * (high - low + 1);
    return low + k;
}

int main(int argc, char *argv[])
{
int i, j, x;
FILE *arq;

if (argc != QUANT_ARG) // Verifica quant. de argumentos
    {
    perror("Quantidade incorreta de argumentos.\n");
    exit(1);
    }
if((arq = fopen(argv[INDICE_NOME_ARQ], "r+")) == NULL)
	{
	perror("Erro de arquivo.\n");
	exit(1);
	}
srand(time(0)); // Semente da seq. randomica
printf("GERANDO MATRIZ RANDÔMICA . . .\n");
for(i = 0; i < atoi(argv[INDICE_LINHA]); i++)
	{
	for(j = 0; j < atoi(argv[INDICE_COLUNA]); j++)
		{
		x = RandomInteger(0, 1);
		fprintf(arq, "%d ", x);
		printf("%d ", x);
		}
	printf("\n");
	}
printf("\n");
fclose(arq);
return 0;
}
