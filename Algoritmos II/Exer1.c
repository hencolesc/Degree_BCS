// Exercicio de fixação de Algoritmos 2. Autor: Henrique Colodetti Escanferla.
#include<stdio.h>
void main()
{
int n, x;
scanf("%d",&x);
scanf("%d",&n);
printf("%d", potencia(x, n));
printf("\n");
}
//-------------------------------------------------------------------------------
void countdown(int n)
{
if (n==1)
	{		
	printf("1 ");
	}
else
	{		
	printf("%d ", n);
	countdown(n-1);
	}
}
//-------------------------------------------------------------------------------
void countup(int x, int n)
{
if (x==n)
	{		
	printf("%d ", x);
	}
else
	{		
	printf("%d ", x);
	countup(x+1, n);
	}
}
//-------------------------------------------------------------------------------
int potencia(int x, int n)
{
if (n==0)
	{
	return 1;
	}
else
	{
	return x*potencia(x, n-1);
	}
}
//-------------------------------------------------------------------------------
int fatorial(int n)
{
if (n==0)
	{
	return 1;
	}
else
	{
	return n*fatorial(n-1);
	}
}
