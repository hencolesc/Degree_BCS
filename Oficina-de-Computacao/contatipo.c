// Exercicio CONTATIPO avaliado pelo ambiente BOCA na disciplina de Oficina de Computação. Autor: Henrique Colodetti Escanferla.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void le_frase(char []);

void main()
{
int i, cont; // i=> indice de string; cont=> contador de ocorrencias.
char s[200], fim[]="FIM", Tipo[]="Tipo", tipo[]="tipo", bloco[]="0000"; // Strings d 4 caracteres para detectar palavras "tipo" e "Tipo".

le_frase(s);
while (strcmp(s, fim)) // Quando a frase for "FIM", o programa termina como foi pedido.
	{
	for (i=0, cont=0; s[i]!='\0'; i++) // Frase acaba em "\0".
		{
		bloco[0]=s[i]; // O "bloco" ira andar pela string "s" englobando 4 cedulas.
		bloco[1]=s[i+1];
		bloco[2]=s[i+2];
		bloco[3]=s[i+3];
		if ((!strcmp(Tipo, bloco) && (s[i+4]==' ' || s[i+4]=='.' || s[i+4]==',' || s[i+4]==';' || s[i+4]==':' || s[i+4]=='\0')) || 
		(!strcmp(tipo, bloco) && (s[i+4]==' ' || s[i+4]=='.' || s[i+4]==',' || s[i+4]==';' || s[i+4]==':' || s[i+4]=='\0') && s[i-1]==' '))
			cont++; // Conta-se 1.
		}
	printf("%d\n", cont); // Mostra o resultado e pula linha.
	le_frase(s);
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

void le_frase(char s[])
{
int i; // i=> indice da string.
char aux; // aux=> recebera caracteres.

scanf("%c", &aux);
while (aux=='\n')
	scanf("%c", &aux); 
for (i=0; aux!='\n';i++)
	{
	s[i]=aux;
	scanf("%c", &aux);
	}
s[i]='\0'; // Fim da string.
}
