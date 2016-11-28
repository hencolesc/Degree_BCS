#include <stdio.h>

void prox_combinacao(unsigned combinacao[], unsigned qt_potencias, unsigned qt_turbinas)
{// Gera proxima combinação ajeitando de acordo com a base do nº por meio de "empréstimos" de algarismos a esquerda
short i;
unsigned short base = qt_turbinas + 1, soma = 0;

for (i = 0; combinacao[i] == 0 ; ++i) // 1º algarimos a esquerda != 0
	combinacao[i] = base - 1; // Tais algarismos se tornam o maior da base

combinacao[i] -= 1; // Empresta 1 do algarismo a esquerda, isto gera a prox. combinação em ordem decrescente

for(i = qt_potencias - 1; soma < qt_turbinas && i >= 0; --i)
    soma += combinacao[i]; // Em qual algarismo a soma passou ou ficou igual a qt_turbinas?

if ((short)(soma - qt_turbinas) >= 0)
		{ // O loop abaixo pega um atalho pulando intervalos de combinações que tem soma de turbinas > qt_turbinas
        combinacao[i + 1] -= soma - qt_turbinas; // Retira o tanto que passou de qt_turbinas
		for (; i >= 0; --i) // Zera o resto a direita do nº
			{
            combinacao[i] = 0;
			}
		// Encontra 1º algarismo diferente de zero. Muitas combinações inuteis sao descartadas neste for acima
		}
}

unsigned short neh_overflow(unsigned combinacao[], unsigned qt_potencias)
{// Retorna 1 se chegar na ultima combinação valida. Desculpe por se chamar assim hu3hu3hu3. combinacao[] = {0, 0, . . ., 0}
short i;

for (i = qt_potencias - 1; i >= 0; --i)
	if (combinacao[i])
		return 1;
return 0;
}

int main(void)
{
unsigned x = 0, combinacao[50], qt_potencias = 25, qt_turbinas = 10;
short i;

for (i = 0; i < qt_potencias; ++i)
	combinacao[i] = qt_turbinas;

while(neh_overflow(combinacao, qt_potencias))
	{
	++x;
	prox_combinacao(combinacao, qt_potencias, qt_turbinas);
	for (i = qt_potencias - 1; i >= 0; --i)
		printf("%u ", combinacao[i]);
	printf("\n");
	}
printf("nº de combinações sem repetição = %d\n", x);

return 0;
}
