// 1ª prova de Oficina de Computação. Autor: Henrique Colodetti Escanferla. Prof.: Luiz Eduardo.

#include<stdio.h>
#include<stdlib.h>

void le_matriz(int** mat) // Le entrada de dados padrão e insere numa matriz 9x9.
{
int i, j; // i e j=> indices da matriz.

for(i=0; i<9; i++) // Leitura por linha.
	{
	for(j=0; j<9; j++)
		{
		scanf("%d", &mat[i][j]); // Le inteiro.
		}
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------

int linha_1a9(int** mat) // Verifica a ocorrencia unica dos algarismos 1 a 9 em cada linha da mariz 9x9 e em cada 9 submatrizes 3x3. Retorna 1 p/ correto e 0 p/
							 // incorreto.
{
int i, j, cont, n; // i e j=> indices da matriz; cont=> contador de ocorrencias de inteiros; n=> contador de passos (valor 9 termina loop) OU nº 1~9 p/ contar ocorrencias.

for(i=0; i<9; i++) // Verificação por linha da matriz 9x9.
	{
	for (n=1, cont=0; n<10; n++) // Aqui n varia de 1 a 9 afim de verificar ocorrencias.
		{
		for(j=0; j<9; j++) // Loop de colunas para a verificação por linhas.
			{
			if (mat[i][j]==n)
				{
				cont++; // Houve ocorrencia.
				}
			}
		if (!cont || cont>1) // 0 ou maior que um não pode ocorrer.
			{
			return 0; // Retorna aviso de incorreto.
			}
		}
	}
return 1; // Se chegou aqui, esta correto.
}

//------------------------------------------------------------------------------------------------------------------------------------------

int submat_1a9(int** mat) // Verifica a ocorrencia unica dos algarismos 1 a 9 em cada 9 submatrizes 3x3. Retorna 1 p/ correto e 0 p/ incorreto.
{
int i, j, cont, num, l, c; // i e j=> indices da matriz; cont=> contador de ocorrencias de inteiros; num=> nº 1~9 p/ contar
							  // ocorrencias; l e c=> implementam i e j iniciais para as 9 submatrizes.

for(l=0; l<3; l++)
	{
	for(c=0; c<3; c++)
		{
		for(num=1, cont=0; num<10; num++) // Varia de 1 a 9 afim de verificar ocorrencias.
			{
			for(i=3*l; i<3+3*l; i++) // Loop dos "começos" das submatrizes para a verificação. Posições iniciais: 11, 14, 17, 41, 44, 47, 71, 74, 77.
				{	
				for(j=3*c; j<3+3*c; j++)
					{
					if (mat[i][j]==num)
						{
						cont++; // Houve ocorrencia.
						}
					}
				}
			}
		if (!cont || cont>1) // 0 ou maior que um não pode ocorrer.
			{
			return 0; // Retorna aviso de incorreto.
			}
		}
	}
return 1; // Se chegou aqui, esta certo.
}

//---------------------------------------------------------------------------------------------------------------------------------------------

int coluna_1a9(int** mat) // Verifica a ocorrencia unica dos algarismos 1 a 9 em cada coluna da mariz 9x9 e em cada 9 submatrizes 3x3. Retorna 1 p/ correto e 0 p/
							 // incorreto.
{
int i, j, cont, n; // i e j=> indices da matriz; cont=> contador de ocorrencias de inteiros; n=> contador de passos (valor 9 termina loop) OU nº 1~9 p/ contar ocorrencias.

for(i=0; i<9; i++) // Verificação por coluna da matriz 9x9.
	{
	for (n=1, cont=0; n<10; n++) // Aqui n varia de 1 a 9 afim de verificar ocorrencias.
		{
		for(j=0; j<9; j++) // Loop de colunas para a verificação por linhas.
			{
			if (mat[j][i]==n)
				{
				cont++; // Houve ocorrencia.
				}
			}
		if (!cont || cont>1) // 0 ou maior que um não pode ocorrer.
			{
			return 0; // Retorna aviso de incorreto.
			}
		}
	}
return 1; // Se chegou aqui, esta correto.
}

//------------------------------------------------------------------------------------------------------------------------------------------

void main()
{
int i, n, **mat; // n=> numero de instancias; mat=> matriz 9x9 de inteiros de 1 a 9 e i=> conta de 1 até 9 p/ alocação dinamica.

mat=(int**)malloc(sizeof(int*)*9);
for(i=0; i<9; i++)
	{
	mat[i]=(int*)malloc(sizeof(int)*9);
	}
scanf("%d", &n);
for(; n>0; n--) // Contador de execuções.
	{
	le_matriz(mat);
	printf("INSTANCIA %d\n", n);
	if (linha_1a9(mat) && submat_1a9(mat) && coluna_1a9(mat))
		{
		printf("SIM\n");
		}
	else
		{
		printf("NAO\n");
		}
	}
free(mat); // Libera memoria.
}
