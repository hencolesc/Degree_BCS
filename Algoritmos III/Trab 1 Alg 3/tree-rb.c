#include "tree-rb.h"


/*----------------------------------------------------------------------------*/
/* Cria um novo no da arvore red black e retorna um ponteiro para este no     */
/*----------------------------------------------------------------------------*/
node_rb *node_rb_create(object *o) {
      node_rb *novoNodo = (node_rb*)malloc(sizeof(node_rb));
      novoNodo->value = *o;
      novoNodo->left = &nodoNulo;
      novoNodo->right = &nodoNulo;
      novoNodo->parent = &nodoNulo;
      return novoNodo;
}

/*----------------------------------------------------------------------------*/
/* Destroi e libera a memoria alocada para este no                            */
/*----------------------------------------------------------------------------*/
void node_rb_destroy(node_rb **n) {
      free(*n);
}

/*----------------------------------------------------------------------------*/
/* Essa função arruma a árvore red-black após a inserção, caso necessário.
/*----------------------------------------------------------------------------*/
void arrumaArvRN(node_rb **root, node_rb *novoNodo) {
    node_rb *tio, *avo;
    while(novoNodo->parent->color == red) {
        avo = novoNodo->parent->parent;
        if(novoNodo->parent == avo->left) {        /* insercao na subarv.esq */
            tio = avo->right;
            if (tio->color == red) {                                    /* cor a dir. do avo e'  vermelho */
                novoNodo->parent->color = black;                        /* Caso 1 */
                tio->color = black;
                avo->color = red;
                novoNodo = avo;
			}
			else {                                                      /* cor a dir. do avo e' preto */
			    if(novoNodo == novoNodo->parent->right) {               /* desbal. na subarv.dir do filho esq */
			        novoNodo = novoNodo->parent;                        /* Caso 2: esq-dir */
                    novoNodo = node_rb_left_rotate(root, novoNodo);
                }
                novoNodo->parent->color = black;                        /* Caso 3  esq-esq*/
                avo->color = red;
                avo = node_rb_right_rotate(root, avo);
            }
        }
        else {                                                          /* insercao na subarv.dir */
            tio = avo->left;
            if (tio->color == red) {                                    /* cor a esq. do avo e'  vermelho */
                novoNodo->parent->color = black;                        /* Caso 1 */
                tio->color = black;
                avo->color = red;
                novoNodo = avo;
            }
            else {                                                      /* cor a esq. do avo e' preto */
                if(novoNodo == novoNodo->parent->left) {                /* desbal. na subarv.esq do filho dir */
                    novoNodo = novoNodo->parent;                        /* Caso 2: dir-esq */
                    novoNodo = node_rb_right_rotate(root, novoNodo);
                }
                novoNodo->parent->color = black;                        /* Caso 3  dir-dir*/
                avo->color = red;
                avo = node_rb_left_rotate(root, avo);
            }

        }
    }
    node_rb *p;
    p = *root;
    p->color = black;
}

/*----------------------------------------------------------------------------*/
/* Essa funcao deve inserir um novo objeto na arvore red black                */
/*----------------------------------------------------------------------------*/
node_rb *node_rb_insert(node_rb **root, object *o) {
    node_rb *x = *root;
    node_rb *novoNodo = node_rb_create(o);
    node_rb* aux = &nodoNulo;
    while(x != &nodoNulo)
    {
        aux = x;
        if(*o < x->value) x = x->left;
        else x = x->right;
    }
    novoNodo->parent = aux;
    if(aux == &nodoNulo)
        {
    	*root = novoNodo;
    	}
    else if(*o < aux->value){
    	aux->left = novoNodo;
    	}
    else
        {
    	aux->right = novoNodo;
    	}
    novoNodo->color = red;
    arrumaArvRN(root, novoNodo);
    return *root;
}

/*----------------------------------------------------------------------------*/
/* Retorna o menor numero da arvore de raiz p                                 */
/*----------------------------------------------------------------------------*/
node_rb *menorNo(node_rb *p) {
    if(p->left == &nodoNulo) return p;
    return menorNo(p->left);
}

/*----------------------------------------------------------------------------*/
/* Retorna o no sucessor de p                                                 */
/*----------------------------------------------------------------------------*/
node_rb *sucessor(node_rb *p) {
    if (p->right == &nodoNulo) return &nodoNulo;
    p = p->right;
    return menorNo(p);
}

/*----------------------------------------------------------------------------*/
/* Essa função arruma a árvore red-black após a remoção, caso necessário.
/*----------------------------------------------------------------------------*/
void arrumaRem_RN(node_rb **root, node_rb *p) {
    node_rb *d;
    while((p != *root) && (p->color == black)) {
        if(p == p->parent->left) {                          /* extra BLACK a esquerda */
            d = p->parent->right;
            if(d->color == red) {                           /* Caso 1 */
                d->color == black;
                p->parent->color = red;
                p->parent = node_rb_left_rotate(root, p->parent);
                d = p->parent->right;
            }
            if((d->left->color == black) && (d->right->color == black)) {
                d->color = red;                             /* Caso 2 */
                p = p->parent;
            }
            else {
                if(d->left->color == red) {                 /* direita(d)->cor == RED */
                    d->color = red;                         /* Caso 3 */
                    d->left->color = black;
                    d = node_rb_right_rotate(root, d);
                    d = p->parent->right;
                }
                d->color = p->parent->color;                /* Caso 4 */
                p->parent->color = black;
                d->right->color = black;
                p->parent = node_rb_left_rotate(root, p->parent);
                p = *root;
            }
        }
        else {                                              /* extra BLACK a direita */
            d = p->parent->left;
            if(d->color == red) {                           /* Caso 1 */
                d->color == black;
                p->parent->color = red;
                p->parent = node_rb_right_rotate(root, p->parent);
                d = p->parent->left;
            }
            if((d->left->color == black) && (d->right->color == black)) {
                d->color = red;                             /* Caso 2 */
                p = p->parent;
            }
            else {
                if(d->right->color == red) {                /* esquerda(d)->cor == RED */
                    d->color = red;                         /* Caso 3 */
                    d->right->color = black;
                    d = node_rb_left_rotate(root, d);
                    d = p->parent->left;
                }
                d->color = p->parent->color;                /* Caso 4 */
                p->parent->color = black;
                d->left->color = black;
                p->parent = node_rb_right_rotate(root, p->parent);
                p = *root;
            }
        }
    }
    p->color = black;
}

/*----------------------------------------------------------------------------*/
/* Essa funcao deve remover um objeto da arvore red black                     */
/*----------------------------------------------------------------------------*/
node_rb *node_rb_remove(node_rb **root, object *o) {
    char aux = 'v';
    node_rb *filho;
    node_rb *nodoRem;
    node_rb *nodoK = node_rb_search(*root, o);					/* nodoK e' o nodo que tem a chave K a ser removida */
    if((nodoK->left == &nodoNulo) || (nodoK->right == &nodoNulo))
       nodoRem = nodoK;                                         /* se nodoK tem 0 ou 1 filho, remove nodoK */
    else                                                        /* senao remove o sucessor */
      nodoRem = sucessor(nodoK);                                /* neste caso o nodoRem nao tem filho esq */
    if(nodoRem->left != &nodoNulo)
        filho = nodoRem->left;
    else
        filho = nodoRem->right;
    filho->parent = nodoRem->parent;
    if(nodoRem->parent == &nodoNulo)
        *root = filho;
    else if(nodoRem == nodoRem->parent->left)
            nodoRem->parent->left = filho;
         else
            nodoRem->parent->right = filho;
    if(nodoK != nodoRem)                                        /* copia chave e dados do nodoRem para nodoK */
        nodoK->value = nodoRem->value;
    if (nodoRem->color == black)
        aux = 'b';
    node_rb_destroy(&nodoRem);                                  /* Libera espaço alocado para tal no */
    if (aux == 'b')
        arrumaRem_RN(root, filho);
    return *root;
}

/*----------------------------------------------------------------------------*/
/* Busca um objeto dentro dos nodes da arvore,                                */
/* retorno é um ponteiro para o no encontrado ou &nodoNulo                     */
/*----------------------------------------------------------------------------*/
node_rb *node_rb_search(node_rb *root, object *o) {
      if(root == &nodoNulo) return &nodoNulo;
      if (*o == root->value) return root;
      if (*o < root->value) return node_rb_search(root->left, o);
      return node_rb_search(root->right, o);
}

/*----------------------------------------------------------------------------*/
/* Rotaciona um no para a esquerda                                            */
/*----------------------------------------------------------------------------*/
node_rb *node_rb_left_rotate(node_rb **root, node_rb *node) {
      node_rb *q;
      q = node->right;
      if(node->parent->right == node) node->parent->right = q ; else node->parent->left = q;
      if(node->parent == &nodoNulo) *root = q;
      node->right = q->left;
      q->left = node;
      q->parent = node->parent;
      node->parent = q;
      return q;
}

/*----------------------------------------------------------------------------*/
/* Rotaciona um no para a direita                                             */
/*----------------------------------------------------------------------------*/
node_rb *node_rb_right_rotate(node_rb **root, node_rb *node) {
      node_rb *q;
      q = node->left;
      if(node->parent->right == node) node->parent->right = q ; else node->parent->left = q;
      if(node->parent == &nodoNulo) *root = q;
      node->left = q->right;
      q->right = node;
      q->parent = node->parent;
      node->parent = q;
      return q;
}
