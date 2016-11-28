// Exercicio Avaliativo de Oficina de Computação. Data: 08\10\2013. Autor: Henrique Colodetti Escanferla.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float** le_matriz(FILE* arq, int l, int c) // Recebe tamanho (l e c) e arquivo de dados. Le arquivo convertendo strings pra float e inserindo na
										   // matriz. Retorna ponteiro de vetores em arranjo D².
{
float** x; // x=> vetor de ponteiros que aponta p/ o inicio da matriz.
int i, j, lixo; // i e j=> linha e coluna da matriz; lixo=> recebe o final da linha ("0").

if (l*c!=0)
	{
	x=(float**)malloc(sizeof(float*)*l); // Cria-se a 1ª coluna de ** com o tamanho a caber as linhas.
	if (x==NULL)
		{
		printf("Erro na alocação de **x\n");
		return NULL;
		}
	for(i=0; i<l; i++)
		{
		x[i]=(float*)malloc(sizeof(float)*c); // Cria-se * que aponta para cada uma das linhas.
		if (x[i]==NULL)
			{
			printf("Erro na alocação de *x[%d]\n", i);
			return NULL;
			}
		}
	for(i=0; i<l; i++) // Loop das linhas.
		{
		for(j=0; j<c; j++) // Loop das colunas.
			{
			fscanf(arq, "%f", &x[i][j]);
			}
		fscanf(arq, "%d", &lixo); // Descarta o inteiro "0~9" que indica fim da linha de dados.
		}
	return x;
	}
else // Se linha ou coluna é zero, a matriz não existe.
	{
	return NULL;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------

void imprime_mat(float** x, int l , int c)
{
int i, j; // i e j=> indices da matriz.

for(i=0; i<l; i++)
	{
	for(j=0; j<c; j++)
		{
		printf("%f ", x[i][j]);
		}
	}
printf("\n"); // Pula linha.
}

//------------------------------------------------------------------------------------------------------------------------------------------------

void med_desv_col(float** x, int l, int c)
{
float med, desv, desv_max, desv_min; // med, desv, desv_max e desv_min=> media por coluna, desvio por coluna, desvio maximo de coluna e desvio
int i, j, col_max=1, col_min=1; // minimo de coluna respectivamente. i, j, col_max e col_min=> indices da matriz, nº da coluna de maior e menor desvio
						  // respectivamente.
FILE* arq=fopen("media.txt", "w"); // Arq. de saída.

for(j=0; j<c; j++)
	{
	for(i=0, med=0; i<l; i++)
		{
		med+=x[i][j]; // Soma a coluna inteira.
		}
	med=med/l;
	fprintf(arq, "%f ", med); // Escreve media da coluna em arq.
	for(i=0, desv=0; i<l; i++)
		{
		desv+=pow(x[i][j]-med, 2); // Numerador dentro da raiz na fórmula do desvio.
		}
	desv=sqrt(desv/(l-1)); // Forma a fração e tira sua raiz. Este é o desvio padrão da coluna.
	fprintf(arq, "%f ", desv); // Escreve desvio da coluna em arq.
	if (j!=0) // O 1º desvio é formado p/ comparar os outros desvios. Neste caso, este if não é feito.
		{
		if (desv>desv_max)
			{
			col_max=j+1;
			desv_max=desv;
			}
		else if (desv<desv_min)
				{
				col_min=j+1;
				desv_min=desv;
				}
		}
	else // Neste caso, salvamos a base da comparação.
		{
		desv_max=desv;
		desv_min=desv;
		}
	}
fprintf(arq, "%d %d", col_max, col_min); // Escreve coluna de desvio max e min em arq.
fclose(arq);
}

//------------------------------------------------------------------------------------------------------------------------------------------------

void main()
{
int l, c; // l e c=> linhas e colunas dos dados.
FILE* arq=fopen("testing", "r"); // Arq. de teste.

fscanf(arq, "%d %d", &l, &c);
med_desv_col(le_matriz(arq, l, c), l, c);
fclose(arq);
}
