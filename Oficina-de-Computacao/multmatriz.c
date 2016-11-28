// Exercicio Multiplica Matriz de Oficina de Computação. Autor: Henrique Colodetti Escanferla.

#include <stdio.h>
#include <stdlib.h>

int** le_matriz(int l, int c) // Recebe tamanho (l e c) e elementos de matriz e retorna ponteiro de vetores em arranjo D².
{
int **x, i, j; // i e j=> linha e coluna da matriz; x=> vetor de ponteiros que aponta p/ o inicio da matriz.

if (l*c!=0)
	{
	x=(int**)malloc(sizeof(int*)*l); // Cria-se a 1ª coluna de ** com o tamanho a caber as linhas.
	if (x==NULL)
		{
		printf("Erro na alocação de **x\n");
		return NULL;
		}
	for(i=0; i<l; i++)
		{
		x[i]=(int*)malloc(sizeof(int)*c); // Cria-se * que aponta para cada uma das linhas.
		if (x[i]==NULL)
			{
			printf("Erro na alocação de **x[%d]\n", i);
			return NULL;
			}
		}
	for(i=0; i<l; i++) // Loop das linhas.
		{
		for(j=0; j<c; j++) // Loop das colunas.
			{
			scanf("%d", &x[i][j]);
			}
		}
	return x;
	}
else // Se linha ou coluna é zero, a matriz não existe.
	{
	return NULL;
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

void printf_mat(int **mat, int l, int c) // Imprime matriz de "l" linhas e "c" colunas.
{
int i, j; // i e j=> indices que percorrem a matriz.

for(i=0; i<l; i++)
	{
	for(j=0; j<c; j++)
		{
		printf("%d ", mat[i][j]);
		}
	}
printf("\n"); // Pula linha.
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

int** mult_mat(int** mat1, int l1, int c1, int** mat2, int l2, int c2) // Retorna matriz resultante de mat1*mat2 e seu tamanho
																	   // l1xc2.
{
if (c1==l2)
	{
	int **mult, i, j, x, prod; // mult=> matriz produto; i, j, x, y, z e w=> par de indices que percorrem 
										// "mult", "mat1" e "mat2" respectivamente; prod=> produto de linhaXcoluna de "mat1" e "mat2".
	mult=(int**)malloc(sizeof(int*)*l1); // Cria-se a 1ª coluna que apontará para apontadores das linhas.
	if (mult==NULL)
		{
		printf("Erro na alocação de **mult\n");
		return NULL;
		}
	for(i=0; i<l1; i++)
		{
		mult[i]=(int*)malloc(sizeof(int)*c2); // Cria-se * que aponta para cada uma das linhas.
		if (mult[i]==NULL)
			{
			printf("Erro na alocação de **mult[%d]\n", i);
			return NULL;
			}
		}
	for(i=0; i<l1; i++) // Loop de linhas.
		{
		for(j=0; j<c2; j++) // Loop de colunas.
			{
			prod=0;
			for(x=0; x<c1; x++) // Loop de linhas e colunas de "mat1" e "mat2" na formação de "prod".
				{
				prod+=mat1[i][x]*mat2[x][j];
				}
			mult[i][j]=prod; // Insere "prod" como elemento de "mult".
			}
		}
	return mult; // Devolve a matriz produto.
	}
else // Neste caso, a matriz produto não existe.
	{
	return (int**)-1; // Isto avisará que não ocorreu a multiplicação por tal fato.
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

void main()
{
int **mat1, **mat2, **mult, l1, c1, l2, c2; // mat1, mat2 e mult=> aponta p/ o inicio da matriz; l1, c1, l2, c2=> linha e coluna da matriz;

scanf("%d %d", &l1, &c1);
while (l1*c1>0) // Condiçao p/ fim de execução.
	{
	mat1=le_matriz(l1, c1); // Leitura das linhas de entrada.
	scanf("%d %d", &l2, &c2);
	mat2=le_matriz(l2, c2);
	if (mat1==NULL)
				{
				printf("Erro na alocação de mat1\n");
				} 
	if (mat2==NULL)
				{
				printf("Erro na alocação de mat2\n");
				}
	mult=mult_mat(mat1, l1, c1, mat2, l2, c2); // Aqui ocorre a multiplicação matricial.
	if (mult!=-1) // Ver linha 98.
		{
		printf("%d %d ", l1, c2); // App tamanho da matriz resultante.
		printf_mat(mult, l1, c2); // App da matriz resultante.
		}
	else
		{
		printf("Matrizes com dimensões incompativeis\n"); // App msg.
		}
	scanf("%d %d", &l1, &c1); // Começo da leitura das linhas de entrada p/ verificar condição de fim de execução.
	free(mat1); // Libera espaço alocado.
	mat1=NULL; // Anula endereço de memoria.
	free(mat2); // Libera espaço alocado.
	mat2=NULL; // Anula endereço de memoria.
	}
}
