#include <stdio.h>

int main()
{
int x, i=2;

printf("Digite um inteiro: ");
scanf("%d", &x);
printf("\n");
while(x>1)
    if (x%i==0)
        {
        printf("%d ", i);
        x=x/i;
        }
    else
        i++;
printf("\n");
return 0;
}
