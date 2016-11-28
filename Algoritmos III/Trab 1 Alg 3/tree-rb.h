#ifndef _treerb_
#define _treerb_

#include "object.h"

/*----------------------------------------------------------------------------*/
/* Estrutura de arvore red black                                              */ 
/*----------------------------------------------------------------------------*/
typedef struct node_rb {
    enum { red = 118, black = 112 } color;
    object value;
    struct node_rb *left;
    struct node_rb *right;
    struct node_rb *parent;
} node_rb;

/*----------------------------------------------------------------------------*/
/* Funcoes para trabalhar com os node_rbs                                     */
/*----------------------------------------------------------------------------*/
node_rb   *node_rb_create                   (object *o);
void       node_rb_destroy                  (node_rb **n);

/*----------------------------------------------------------------------------*/
/* Funcoes basicas para utilizacao da arvore red black                        */
/*----------------------------------------------------------------------------*/
node_rb    *node_rb_insert                  (node_rb **root, object *o);
node_rb    *node_rb_remove                  (node_rb **root, object *o);
node_rb    *node_rb_search                  (node_rb *root, object *o);
node_rb    *node_rb_left_rotate             (node_rb **root, node_rb *node);
node_rb    *node_rb_right_rotate            (node_rb **root, node_rb *node);

node_rb nodoNulo;

#endif

