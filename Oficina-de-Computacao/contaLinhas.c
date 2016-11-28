// Exercicio de Oficina de Computação no ambiente BOCA - Autor: Henrique Colodetti Escanferla.

#include <stdio.h>
#define MAX_LENGTH 255

void le_linha(char linha[])
{
int i; // i=> indice da string.
char c;

linha[0]=getchar();
while (linha[0]=='\n') // Impede inclusão do enter oriundo de uma entrada anterior, afinal, uma linha começando com '\n' nao faz sentido.
	linha[0]=getchar();
for(i=1; linha[i-1]!='\n' && i<=MAX_LENGTH; i++)
	{
	linha[i]=getchar();
	}
if (i==MAX_LENGTH+1) // Caso a linha ultrapasse o tamanho maximo.
	{
	for (; (c=getchar())!=EOF && c!='\n';) ; // Descarta parte inutilizada do buffer.
	linha[MAX_LENGTH]='\0';
	}
else
	linha[i-1]='\0';
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

void main()
{
char texto[MAX_LENGTH], consulta[MAX_LENGTH]; // texto e consulta=> strings que recebem linhas de texto e termo de consulta respectivamente.
int cont, i, j, k, acabou_txt, achou; // cont=> contador de 'linha' com ocorrencia de 'consulta'; i,j e k=> indices de strings; 
									  // acabou_txt=> anuncia fim de texto; achou=> anuncia ocorrencia de 'consulta'.
while(1)
	{
	le_linha(consulta); // Leitura da string de consulta.
	printf("%s\n", consulta);
	if (consulta[0]=='F' && consulta[1]=='I' && consulta[2]=='M' && consulta[3]=='\0')
		break; // Fim do processo.
	cont=0; // Zera contagem.
	while(1)
		{
		le_linha(texto); // Leitura de uma linha de texto.
		if (texto[0]=='.' && texto[1]=='.' && texto[2]=='.' && texto[3]=='.' && texto[4]=='.' && texto[5]=='\0')
			break; // Fim do texto.
		for(i=0, achou=0; texto[i]!='\0' && achou==0 && i<=256; i++)
			{
			printf("Linha 48\n");
			printf("%s\n", consulta);
			for (j=0, k=i, achou=1; consulta[j]!='\0' && achou==1; j++, k++) // Pressupoe que é verdade e verifica a ocorrencia começando em "i".
				{
				printf("Linha 52\n");
				if (texto[k]!=consulta[j])
					{
					printf("N\n");
					achou=0; // Não há ocorrencia para dado "i" atual.
					}
				}
			if (achou)
				{
				printf("S\n");
				cont++; // Conta-se tal linha onde houve ocorrencia.
				}
			}
		}
	printf("%d\n", cont); // Imprime resultado.
	}
}
