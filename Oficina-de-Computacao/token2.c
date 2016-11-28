#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define QUANT_ARG 2
#define INDICE_NOME_ARQ 1
#define STRING_DELIMITADORA " "

int main(int argc, char *argv[])
{
 FILE *arq;
 char *linha;
 char *token;
 size_t len;

 if (argc != QUANT_ARG)
    {
    perror("Quantidade incorreta de argumentos.\n");
    exit(1);
    }

 if((arq = fopen(argv[INDICE_NOME_ARQ], "r+")) == NULL)
    {
    perror("Erro de arquivo.\n");
    exit(1);
    }

 while((getline(&linha, &len, arq)) > 0)
 {
	printf("Endereço de linha: %p\n", &linha);
    printf("Linha: %s", linha);
    linha[strlen(linha)-1] = '\0';
    while((token = strsep(&linha, STRING_DELIMITADORA)) != NULL)
      {
      printf("Endereço de token: %p\n", &token);
      printf("token: %s\n", token);
      }
 }
 printf("Endereço de linha no final da main: %p\n", &linha);
 printf("Endereço de token no final da main: %p\n", &token);
 return 0;
}
