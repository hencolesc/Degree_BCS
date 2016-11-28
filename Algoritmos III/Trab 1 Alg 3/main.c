/*----------------------------------------------------------------------------*/
/* Universidade Federal do Parana                                             */
/*                                                                            */
/* Algoritmos e Estruturas de dados III                                       */
/* Professora Carmem - Segundo Semestre de 2014                               */
/* Segundo Trabalho de Implementacao (Arvore Rubro-Negra)                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include "tree-rb.h"

void imprime_rb(node_rb *r, char a);
void imprime_234(node_rb *r, char a);

int main(int argc, char *argv[]) {
    object n = 0;
	node_rb *root = &nodoNulo;
	node_rb *nodoBusca;
	char op = 'a';
	while(op != 'f')
	{
		nodoNulo.value = 0;
		nodoNulo.color = black;
		nodoNulo.left = &nodoNulo;
		nodoNulo.right = &nodoNulo;
		nodoNulo.parent = &nodoNulo;
		scanf("%c", &op);
		if(op == 'i')
		{
			scanf("%d",(int*)&n);
			root = node_rb_insert(&root, &n);
		}
		else if(op == 'b')
		{
			scanf("%d",&n);
			nodoBusca = node_rb_search(root, &n);
			nodoBusca->value == n ? puts("1") : puts("0");
		}
		else if(op == 'r')
		{
			scanf("%d",&n);
			root = node_rb_remove(&root, &n);
		}
		else if(op == 'p')
		{
			char string[3];
			scanf("%s", string);
			string[0] == 'r' ? imprime_rb(root,'f') : imprime_234(root,'f');
			printf("\n");
		}
	}
    return 0;
}

void imprime_rb(node_rb *r, char a)
{
	if(a == 's') printf(" ");
	printf("(%d:%c", r->value, r->color);
	if(r->left != &nodoNulo) imprime_rb(r->left,'s');
	if(r->right != &nodoNulo) imprime_rb(r->right,'s');
	printf(")");
	return;
}

void imprime_234(node_rb *r, char a)
{
	if(a == 's') printf(" ");
	printf("(");
	if(r->left != &nodoNulo && r->left->color == red) printf("%d;",r->left->value);
	printf("%d",r->value);
	if(r->right != &nodoNulo && r->right->color == red) printf(";%d",r->right->value);
	if(r->left != &nodoNulo)
	{
		if(r->left->color == black) imprime_234(r->left,'s');
		else
		{
			if(r->left->left != &nodoNulo) imprime_234(r->left->left,'s');
			if(r->left->right != &nodoNulo) imprime_234(r->left->right,'s');
		}
	}
	if(r->right != &nodoNulo)
	{
		if(r->right->color == black) imprime_234(r->right,'s');
		else
		{
			if(r->right->left != &nodoNulo) imprime_234(r->right->left,'s');
			if(r->right->right != &nodoNulo) imprime_234(r->right->right,'s');
		}
	}
	printf(")");
	return;
}


