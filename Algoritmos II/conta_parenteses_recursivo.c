#include <stdio.h> // Versão recursiva do contador de parenteses em string. Autor: Henrique Colodetti Escanferla.

int recursao(char s[], int i, int x) // 0 => String invalida; 1=> String valida
{
if (x<0)
    return 0;
if (s[i]=='\0')
    if (!x)
        return 1;
    else
        return 0;
if (s[i]=='(')
    return recursao(s, i+1, x+1);
if (s[i]==')')
    return recursao(s, i+1, x-1);
return recursao(s, i+1, x);
}

int main()
{
char s[30];

scanf("%s", s);

if (recursao(s, 0, 0))
    printf("Quantidade de parenteses valida.\n");
else
    printf("Quantidade de parenteses invalida.\n");
return 0; // FIM DO PROGRAMA
}
