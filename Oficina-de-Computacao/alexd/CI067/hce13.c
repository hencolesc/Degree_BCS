// 1º Trabalho da disciplina Oficina de Computação, CI067, Professor Alexandre Direne. Autor: Henrique Colodetti Escanferla.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define false (0>0)
#define true (!false)
// Char a~z para ASCII decimal => 97~122

void substitui(char s[], unsigned  int i, unsigned int letra)
{ // Insere char, com o codigo ASCII, no indice i da string s
if (i+1>strlen(s))
    {
    perror("Tentou substittuir fora do tamanho util da string.");
    exit(1);
    }
s[i]=(char)letra;
}

void insere(char s[], int i, unsigned int letra)
{ // Insere char, com o codigo ASCII, no indice i da string s, "empurrando" o resto p/ os lados
if (i>strlen(s))
    {
    perror("Tentou inserir fora do tamanho util da string.");
    exit(2);
    }

int x;

for (x=strlen(s); x>=i; x--)
    s[x+1]=s[x];
s[i]=(char)letra;
}

void deleta(char s[], unsigned int i)
{ // Deleta o indice i da string s, eliminando o "buraco"
if (i+1>strlen(s))
    {
    perror("Tentou retirar fora do tamanho util da string.");
    exit(3);
    }
for (; s[i+1]!='\0'; i++)
    s[i]=s[i+1];
s[i]='\0';
}

unsigned int esta_no_plano(char plano[][27], char s[], unsigned int tam)
{
unsigned int achou=false, i;

for(i=0; i<tam; i++)
    if (!strcmp(s, plano[i])) { achou=true; break; } // Achou ocorrencia no plano; interrompe o loop
return achou;
}

void copia_plano_edicao(char p_colar[][27], char p_copiar[][27], unsigned int e_colar[26], unsigned int e_copiar[26],
                        unsigned int tam)
{ // Copia plano e edição de copiar p/ colar
unsigned int i;

for(i=0; i<tam; i++)
    strcpy(p_colar[i], p_copiar[i]);
for(i=0; i<tam; i++)
    e_colar[i]=e_copiar[i];
}

void imprime_solucao(char p_min[][27], unsigned int ed_min[], unsigned int d_min)
{ // Imprime conforme é pedido, a edição feita, a palavra intermediaria resultante em uma linha e a distancia de edição
unsigned int i;

for(i=0; i<d_min; i++)
    switch (ed_min[i])
        {
        case 0: printf("Substitui: %s\n", p_min[i]); break;
        case 1: printf("Remove: %s\n", p_min[i]); break;
        case 2: printf("Insere: %s\n", p_min[i]); break;
        default: printf("Erro em imprime_plano. p_min[%d] = %s\n", i, p_min[i]); break;
        }
printf("Distancia = %d\n", d_min);
}

void faz_plano(char p_min[][27], char plano[][27], char a[], char b[], unsigned int ed_min[], unsigned int edicoes[],
               unsigned int dist, unsigned int* d_min)
{ //Gera todas as possibilidades de edições e coleta o 1º plano minimo possivel, dentre outros minimos, por retroação
unsigned int i, letra; // i=> indice de s1; letra=> a~z => 97~122 em ASCII;
char s1[27]; // s1 => string auxiliar guarda string a após 1 edição

if (dist==*d_min)
    return; // Plano atual é maior que o plano minimo atual
if (!strcmp(a, b)) // É solução ou ainda não?
    {
    if (dist<*d_min) // MUDE AQUI!
        {
        *d_min=dist; // Guarda o minimo
        copia_plano_edicao(p_min, plano, ed_min, edicoes, *d_min); // Salva o plano minimo
        }
    return;
    }
for(i=0; i<strlen(a); i++) // Loop p/ as posições
    {
    //if(a[i]==b[i])
      //  continue; // Indice atual ja esta correto, mudá-lo acarreta numa solução que não é mínima???
    for(letra=97; letra<123; letra++) // Loop p/ as letras
        {
        strcpy(s1, a);
        substitui(s1, i, letra);
        if (!strcmp(s1, a))
            continue; // Trocou alguma letra por ela mesma, este caminho é descartado
        if (esta_no_plano(plano, s1, dist))
            continue; // Plano atual tem palavra repetida, MUDE AQUI!
        strcpy(plano[dist], s1);
        edicoes[dist]=0; // Codigo p/ imprime_plano
        faz_plano(p_min, plano, s1, b, ed_min, edicoes, dist+1, d_min); // Recursão
        }
    }
for(i=0; i<strlen(a); i++) // Só um loop p/ as posições
    {
    strcpy(s1, a);
    deleta(s1, i);
    if (!strlen(s1))
        break; // s1 é string vazia, vai p/ os fors de inserir
    if (esta_no_plano(plano, s1, dist))
        continue; // Plano atual tem palavra repetida
    strcpy(plano[dist], s1);
    edicoes[dist]=1; // Codigo p/ imprime_plano
    faz_plano(p_min, plano, s1, b, ed_min, edicoes, dist+1, d_min); // Recursão
    }
for(i=0; i<=strlen(a); i++) // Só um loop p/ as posições
    for(letra=97; letra<123; letra++) // Loop p/ as letras
        {
        strcpy(s1, a);
        insere(s1, i, letra);
        if (strlen(s1)>strlen(b))
            return; // Esta edição aumentou distancia entre s1 e b, o caminho é descartado
        if (esta_no_plano(plano, s1, dist))
            continue; // Plano atual tem palavra repetida
        strcpy(plano[dist], s1);
        edicoes[dist]=2; // Codigo p/ imprime_plano
        faz_plano(p_min, plano, s1, b, ed_min, edicoes, dist+1, d_min); // Recursão
        }
}

int main()
{
char a[27], b[27], plano[26][27], p_min[26][27]; // plano e edicoes são auxiliares, p_min e ed_min terão a solução minima
unsigned int edicoes[26], ed_min[26], dist=0, d_min;

printf("Entre com a palavra inicial: ");
scanf("%s", a);
printf("Entre com a palavra final: ");
scanf("%s", b);
if (strlen(a)>strlen(b)) // É garantido que existe um plano de edição de tamanho max(strlen(s1), strlen(s2))
    d_min=strlen(a)+1;   // Colocamos min(strlen(s1), strlen(s2))+1 p/ "podar"  galhos inuteis da arvore de possibilidades
else
    d_min=strlen(b)+1;
faz_plano(p_min, plano, a, b, ed_min, edicoes, dist, &d_min);
imprime_solucao(p_min, ed_min, d_min);
return 0;
}
