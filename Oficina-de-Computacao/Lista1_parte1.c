// Exercicios da Lista 1 Parte 1 de Oficina de Computação. Autor: Henrique Colodetti Escanferla.
#include <stdio.h>
#include <math.h>

void lista1_ex2();
float lista1_ex3(int);
void lista1_ex4();
void lista1_ex5(int);
void lista1_ex6(int);
void lista1_ex7();
float lista1_ex8(float);
float lista1_ex9(float);
float lista1_ex10(float);
int lista1_ex11(float);
void lista1_ex12();

void main(void)
{
lista1_ex12();
printf("\n");
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

/*void lista1_ex2()
{
unsigned char uc;
unsigned int ui;
char c;
int i;
float f;
double d;
long int li;
unsigned long int uli;
long double ld;

printf("O tamanho de unsigned char eh: %u\n", sizeof(uc));
printf("O tamanho de unsigned int eh: %u\n", sizeof(ui));
printf("O tamanho de char char eh: %u\n", sizeof(c));
printf("O tamanho de int eh: %u\n", sizeof(i));
printf("O tamanho de float eh: %u\n", sizeof(f));
printf("O tamanho de double eh: %u\n", sizeof(d));
printf("O tamanho de long int eh: %u\n", sizeof(li));
printf("O tamanho de unsigned long int eh: %u\n", sizeof(uli));
printf("O tamanho de long double eh: %u\n", sizeof(ld));
} */ // "Retirado" pois gerava avisos sobre a formatação irregular em compiladores diferentes.

//-------------------------------------------------------------------------------------------------------------------------------------------------

float lista1_ex3(int x)
{

if ((x==0)||(x==1))
	return 1;
else
	{
	float y=1;

	for (; x>=1; x--)
		{
		y*=x;
		}
	return y;
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

void lista1_ex4()
{
int fib0=0, fib1=1, aux, x;

printf("0 1 ");
for (x=18; x!=0; x--)
	{
 	aux=fib0+fib1;
	fib0=fib1;
	fib1=aux;
	printf("%d ", fib1); 
	}

}

//-------------------------------------------------------------------------------------------------------------------------------------------------

void lista1_ex5(int x)
{
if (x==1)
	printf("0");
else if (x==2)
		 printf("0 1");
	 else
			 {
			 printf("0 1 ");

			 int fib0=0, fib1=1, aux;

			 for (x-=2; x!=0; x--)
			 	{
			 	aux=fib0+fib1;
				fib0=fib1;
				fib1=aux;
				printf("%d ", fib1); 
			    }
			 }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

void lista1_ex6(int x)
{
short int eh_primo=1;
int n;

if (x!=2)
	for (n=2; n<=x/2; n++)
		{
		if (x%n==0)
			{
			eh_primo=0;
			break;
			}
		}
if (eh_primo==1)
	printf("%d eh um numero primo.", x);
else
	printf("%d nao eh um numero primo.", x);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

void lista1_ex7()
{
float a, b, c, delta, x1, x2;
char continua;

do
	{
	printf("\nDigite o coeficiente de x²: ");
	scanf("%f", &a);
	printf("\nDigite o coeficiente de x: ");
	scanf("%f", &b);
	printf("\nDigite o coeficiente independente: ");
	scanf("%f", &c);
	delta=b*b-4*a*c;
	if (delta>=0)
		{
		x1=(-b+sqrt(delta))/2*a;
		x2=(-b-sqrt(delta))/2*a;	
		printf("\nAs raizes da equação dada são %f e %f.", x1, x2);
		}
	else
		printf("\nNão existem raizes reais para a equação dada.");
	printf("\nPressione T para repetir o processo ou qualquer outra tecla para encerrar: ");
	continua=getchar();
	continua=getchar(); // Isto foi necessario pois o getchar recebia "ENTER" do comando anterior antes que o usuario pudesse digitar "T".
	}
while (continua!='T');
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

float lista1_ex8(float x)
{
int n=1;
float cosx=1;

for (; n<=14; n++)
	{
	cosx+=pow(-1, n)*pow(x, 2*n)/lista1_ex3(2*n);
	}
return cosx;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

float lista1_ex9(float x)
{
int n=1;
float cosx=1;

while (n<=14)
	{
	cosx+=pow(-1, n)*pow(x, 2*n)/lista1_ex3(2*n);
	n+=1;
	}
return cosx;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

float lista1_ex10(float x)
{
int termo=0;
float cosx=1;

do
	{
	termo+=1;
	cosx+=pow(-1, termo)*pow(x, 2*termo)/lista1_ex3(2*termo);
	}
while (termo<14);
return cosx;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

int lista1_ex11(float x)
{
int cont=1;
float vabs;

while (cont<sqrt(x))
	{
	cont+=1;
	}
if (cont-1-sqrt(x)<0)
	vabs=-1*(cont-1-sqrt(x));
else
	vabs=cont-1-sqrt(x);
if (cont-sqrt(x)<vabs)
	return cont;
else
	return cont-1;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

void lista1_ex12()
{
int anos=0, pafr=80, perm=45;

while (pafr>=perm)
	{
	anos+=1;
	pafr+=2;
	perm+=3;
	}
printf("Foram necessarios %d anos para que o peso de Ermengarda ultrapasse o peso de Alfranio.\nO peso de Alfranio e Ermengarda no momento da ultrapassagem é de, respectivamente, %d kilos e %d kilos.", anos, pafr, perm);
}
