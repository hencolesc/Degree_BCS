#include "polinomio.h"

/*----------------------------------------------------------------------------*/


polinomio constroi_polinomio(char *s) {

    /* Preencher com seu código aqui */
    int i,j,k, ind = 0;
    for(i = 0;i < (int)strlen(s);i++)
        if(s[i] == ' ') ind++;
    polinomio p = FLVazia();
    i = 0;
    int tam;
    while(i < (int)strlen(s))
    {
        j = i;
        while(s[j] != ' ' && j < strlen(s)) j++;
        tam = j-i+1;
        char temp[tam];
        for(k = 0;i < j;i++)
        {
            temp[k] = s[i];
            k++;
        }
        temp[tam-1] = '\0';
        insere( ind, atof(temp), p);
        ind--;
        i++;
    }
    return p;
}
/*----------------------------------------------------------------------------*/
void destroi_polinomio(polinomio p) {

	/* Preencher com seu código aqui */
    while(p->ini->p != NULL)
        retira(p->ini,p);
    free(p->ini);
    free(p);
 }
/*----------------------------------------------------------------------------*/
polinomio escreve_polinomio(polinomio p) {

	/* Preencher com seu código aqui */
	item *aux;
	aux = p->ini->p;
	while(aux->ind != 0)
	{
		if (aux->coef < 0 && aux == p->ini->p) printf(" - ");
		if (aux->coef != 0) printf("%dx^%d", abs(aux->coef), aux->ind);
		aux = aux->p;
		if (aux->ind != 0)
		{
			if (aux->coef < 0) printf(" - ");
			else if (aux->coef > 0) printf(" + ");
		}
	}
	if (aux->coef != 0)
	{
		if (aux->coef < 0) printf(" - ");
		else if (aux->coef > 0) printf(" + ");
		printf("%d", abs(aux->coef));
	}
	printf("\n");
	return p;
}
/*----------------------------------------------------------------------------*/
polinomio soma(polinomio p, polinomio q) {

    /* Preencher com seu código aqui */
    polinomio r = FLVazia();
    item *auxp = p->ini->p,*auxq = q->ini->p;
    if(auxp->ind > auxq->ind) while(auxp->ind > auxq->ind) { insere(auxp->ind,auxp->coef,r); auxp = auxp->p; }
    else if(auxq->ind > auxp->ind) while(auxq->ind > auxp->ind) { insere(auxq->ind,auxq->coef,r); auxq = auxq->p; }
    while(auxp != NULL && auxq != NULL)
    {
        insere(auxp->ind,((auxp->coef)+(auxq->coef)),r);
        auxp = auxp->p;
        auxq = auxq->p;
    }
    return r;
}
/*----------------------------------------------------------------------------*/
polinomio multiplica(polinomio p, polinomio q) {

    /* Preencher com seu código aqui */
    polinomio r = FLVazia();
    item *auxp = p->ini->p; // Auxiliares que guardarão o termo atual dos polinomios
    item *auxq = q->ini->p;
    item *auxr = r->ini->p;
    
    int ind = (p->ini->p->ind)+(q->ini->p->ind); // parenteses???
    float coef;
    
    while (ind >= 0) // Insere termos do grau de p*q até 0 com todos os coefs = 0
    {
    	insere(ind, 0, r);
    	ind--;
    }
    while (auxp != NULL)
    {
    	auxq = q->ini->p;
    	while (auxq != NULL)
    	{
    		auxr = r->ini->p;
    		while(auxr->ind >= 0)
    		{
    			if(auxr->ind == (auxp->ind)+(auxq->ind))
    			{
    				auxr->coef += auxp->coef*auxq->coef;
    				break;
    			}
    			auxr = auxr->p;
    		}
    		auxq = auxq->p;
    	}
    	auxp = auxp->p;
    }
    return r; // Devolve o polimonio r
}
/*----------------------------------------------------------------------------*/
polinomio subtrai(polinomio p, polinomio q) {

    /* Preencher com seu código aqui */
    polinomio r = FLVazia();
    item *auxp = p->ini->p,*auxq = q->ini->p;
    if(auxp->ind > auxq->ind) while(auxp->ind > auxq->ind) { insere(auxp->ind,auxp->coef,r); auxp = auxp->p;}
    else if(auxq->ind > auxp->ind) while(auxq->ind > auxp->ind) { insere(auxq->ind,auxq->coef,r); auxq = auxq->p;}
    while(auxp != NULL && auxq != NULL)
    {
        insere(auxp->ind,auxp->coef-auxq->coef,r);
        auxp = auxp->p;
        auxq = auxq->p;
    }
    return r;
}
/*----------------------------------------------------------------------------*/
polinomio derivada(polinomio p) {

    /* Preencher com seu código aqui */
    polinomio r = FLVazia();
    item *aux = p->ini->p;
    int ind;
    float coef;
    while(aux != NULL)
    {
        coef = aux->coef * (float)aux->ind;
        ind = aux->ind - 1;
        insere(ind,coef,r);
        aux = aux->p;
    }
    return r;
}
/*----------------------------------------------------------------------------*/
polinomio primitiva(polinomio p) {

    /* Preencher com seu código aqui */
    polinomio r = FLVazia();
    item *aux = p->ini->p;
    int ind;
    float coef;
    while(aux != NULL)
    {
        ind = aux->ind + 1;
        coef = ((aux->coef) / ((float)ind));
        insere(ind,coef,r);
        aux = aux->p;
   	}
   	r->fim->coef = 0;
    return r;
}
/*----------------------------------------------------------------------------*/
float avalia(polinomio p, float x) {

    /* Preencher com seu código aqui */
    float s = 0;
    item *aux = p->ini->p;
    while(aux != NULL)
    {
        s += aux->coef*((float)pow((double)x,(double)aux->ind));
        aux = aux->p;
    }
    return s;
}
