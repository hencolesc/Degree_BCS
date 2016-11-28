
#ifndef _object_
#define _object_

#include <stdio.h>
#include <stdlib.h>

/*----------------------------------------------------------------------------*/
/* Objeto inserido dentro de cada no da arvore                                */ 
/*----------------------------------------------------------------------------*/
typedef int object;

/*----------------------------------------------------------------------------*/
/* Funcoes para trabalhar com o objeto                                        */
/* Dica:                                                                      */
/*      Utilizando as funcoes da manipulacao de objetos o codigo final sera   */
/*      mais generico e facil de ser reutilizado em implementacoes futuras    */
/*----------------------------------------------------------------------------*/
void    object_fprintf                  (FILE *stream, object o);
object  object_atoo                     (char *s);
int     object_cmp                      (object *o1, object *o2);
#endif

