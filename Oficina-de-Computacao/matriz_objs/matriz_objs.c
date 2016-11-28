#include <stdio.h>
#include <stdlib.h>
#define MAX_LIN 3 // Maximo de linhas da matriz
#define MAX_COL 3 // Maximo de colunas da matriz
#define INDICE_NOME_ARQ 1 // O 1º argumento após o nome do programa é o nome do arquivo
#define QUANT_ARG 2 // Nome do programa e o nome do arquivo que contém a matriz

int recursao_enum_obj(unsigned short matriz[][MAX_COL], unsigned short lin, unsigned short col, unsigned short cont)
{ // Tratamos o inicio da enumeração de objs., sua recursão e finalização caso matriz[lin][col] == 1 na 1ª chamada
int enumerou = 0; // Indica se esta função enumerou algo

if (matriz[lin][col] == 1)
	{ // É objeto ñ numerado? Enumere-o, busque à esquerda, direita e abaixo
	enumerou = 1;
	matriz[lin][col] = cont;
	if (col) // Pode ir p/ esquerda? Casos especiais precisam desta recursao
		recursao_enum_obj(matriz, lin, col-1, cont);
	if (col != MAX_COL-1) // Pode ir p/ direita?
		recursao_enum_obj(matriz, lin, col+1, cont);
	if (lin != MAX_LIN-1) // Pode ir p/ baixo?
		recursao_enum_obj(matriz, lin+1, col, cont);
	}
return enumerou;
}

void recursao_detecta_objs(unsigned short matriz[][MAX_COL], unsigned short lin, unsigned short col,
						   unsigned short cont)
// Recursao detectora de objetos na matriz, numerando-os
// 0 é região ausente de objeto, 1 é objeto não enumerado, senão, é seu nº de contagem + 1
// Diagonais não estão em contato!!!
{
if (recursao_enum_obj(matriz, lin, col, cont)) // Testa se existe objeto e executa a enum. dele
	cont++; // Contou algo, cont se adequa p/ próx. obj.
// O if abaixo assegura percorrer toda a matriz c/ a garantia de objs. anteriores enumerados
if (col != MAX_COL-1) // Pode ir p/ direita?
	recursao_detecta_objs(matriz, lin, col+1, cont);
else if (lin != MAX_LIN-1) // Pode ir p/ 1ª coluna da próx. linha?
	     recursao_detecta_objs(matriz, lin+1, 0, cont);
}

void detecta_objs(unsigned short matriz[][MAX_COL]) {recursao_detecta_objs(matriz, 0, 0, 2);}
// Função que esconde a recursao detectora de objetos da matriz

void le_matriz(FILE *arq, unsigned short matriz[][MAX_COL]) // Le arquivo e guarda em matriz
{
int lin, col;

for(lin = 0; lin < MAX_LIN; lin++)
    for(col = 0; col < MAX_COL; col++)
        fscanf(arq, "%hu", &matriz[lin][col]);
}

void escreve_matriz(FILE *arq, unsigned short matriz[][MAX_COL]) // Escreve a matriz no mesmo arquivo de le_matriz
{
int col, lin;

rewind(arq); // Inicio do arquivo
for(lin = 0; lin < MAX_LIN; lin++)
    for(col = 0; col < MAX_COL; col++)
        {
        fprintf(arq, "%hu ", matriz[lin][col]);
        }
}

void print_matriz(unsigned short matriz[][MAX_COL])
{
int i, j;

for(i = 0; i < MAX_LIN; i++)
	{
	for(j = 0; j < MAX_COL; j++)
		printf("%hu ", matriz[i][j]);
	printf("\n");
	}
}

int main(int argc, char *argv[])
{
unsigned short matriz[MAX_LIN][MAX_COL]; // Objetos contém 1, se não, 0
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
le_matriz(arq, matriz); // Leitura
detecta_objs(matriz); // Nucleo do programa
print_matriz(matriz); // FUNÇÃO DE TESTE!!!
// escreve_matriz(arq, matriz); // Escrita
fclose(arq);
return 0;
}
