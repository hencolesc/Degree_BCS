// Exercicio de Algoritmo II. Autor: Henrique Colodetti Escanferla.

#include <stdio.h>

int fib(int);

void main()
{
int x;

scanf("%d", &x);
printf("%d\n", fib(x));
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

int fib(int n)
{
if (n<=2)
	return n-1;
else
	return fib(n-1)+fib(n-2);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

int min_vet()
{

}
