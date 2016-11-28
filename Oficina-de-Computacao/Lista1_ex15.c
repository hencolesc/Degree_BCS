// Exercicio 15 da Lista 1 de Oficina de Computação. Autor: Henrique Colodetti Escanferla.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tam_max 501

int conta_ocorr(char [], char);

void main()
{
char c, s[tam_max]; // c=> Recebe a entrada.
int i; // i=> Indice do vetor.

printf("Digite uma sequencia de caracteres e '0' para encerra-la: ");
c='\n';
while (c=='\n'||c==' ')
	{
	scanf("%c", &c);
	}
for (i=0; c!='0'; i++)
	{
	s[i]=c;
	c='\n';
	while (c=='\n'||c==' ')
		{
		scanf("%c", &c);
		}
	}
s[i]='0'; // '0' é o ultimo caracter do vetor.
i++; // "i" contem o tamanho do vetor.
printf("Digite um caracter para a verificação: ");
c='\n';
while (c=='\n'||c==' ')
	{
	scanf("%c", &c);
	}
printf("O nº de ocorrencias de %c foi de: %d\n", c, conta_ocorr(s, c));
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

int conta_ocorr(char s[], char c)
{
int cont=0, i; // i=> Indice do vetor; cont=> Contador de ocorrencias.
if (c!=0)
	{
	for (i=0; s[i]!='0'; i++)
		{
		if (s[i]==c)
			cont++;
		}
	return cont;
	}
else
	return 1;
}
