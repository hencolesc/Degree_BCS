#include <malloc.h>
#include "grafo.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphviz/cgraph.h>
//------------------------------------------------------------------------------
// (apontador para) estrutura de dados que representa um vértice do grafo
// um nó da  lista de arestas deve ter um apontador pro vertice e um peso
// cada vértice tem um nome que é uma "string"
/*
 * seria 
 * 
 * lista* edges_in;
 * lista* edges_out;  // nulo se não for direcionado
 * char* v_name;
 * long int weigth
 * 
 * */
 
 struct no {
  char *vertex; // necessário para arestas
  vertice conteudo;
  long int peso;
  no proximo;
};
 
 struct lista {
  
  unsigned int tamanho;
  no primeiro;
};
 
struct vertice{
	lista edges_in;
  	lista edges_out;  // nulo se não for direcionado
  	char *v_name;
  	long int weigth;
	};
//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
// 
// o grafo pode ser
// - direcionado ou não
// - com pesos nas arestas ou não
// 
// além dos vértices e arestas, o grafo tem um nome, que é uma "string"
// 
// num grafo com pesos nas arestas todas as arestas tem peso, que é um long int
// 
// o peso default de uma aresta é 0
// Cada nó da lista vertex contém um apontador pra seu vértice e o apontador pro proximo vertice

 struct grafo {
	char *g_name;
	int directed;
  	int weighted;
  	lista vertex;

};	 

//------------------------------------------------------------------------------
// devolve o nome do grafo g
/*seria
 * return g->g_name;
 * 
 * 
 * */

char *nome_grafo(grafo g){
		return g->g_name;
	};

//------------------------------------------------------------------------------
// devolve 1, se g é direcionado, ou
//         0, caso contrário
// return g->directed;
int direcionado(grafo g){
	return g->directed;
	};

//------------------------------------------------------------------------------
// devolve 1, se g tem pesos nas arestas/arcos,
//      ou 0, caso contrário
// return g-> weighted;
int ponderado(grafo g){
	return g->weighted;
	};

//------------------------------------------------------------------------------
// devolve o número de vértices do grafo g
// return tamanho_lista(g->vertex);
unsigned int n_vertices(grafo g){
		return tamanho_lista(g->vertex);
	};

//------------------------------------------------------------------------------
// devolve o número de arestas/arcos do grafo g
/*
 * edge_arch_sum = 0;
 * lista* node = primeiro_no(g->vertex);
 *  for(i to tamanho_lista(g->vertex)){
 * 		edge_arch_sum += tamanho_lista(node->conteudo->edges_in); // cada nó da  lista 
 * 		node = próximo_no(node);
 * }
 * */
unsigned int n_arestas(grafo g){
	unsigned int edge_arch_sum = 0, i;
	no da_vez;
	da_vez = g->vertex->primeiro;
	
		for(i = 0; i < g->vertex->tamanho; i++){
			edge_arch_sum += da_vez->conteudo->edges_out->tamanho;
			da_vez = da_vez->proximo;
		}
	
	return edge_arch_sum;
	
	};



//------------------------------------------------------------------------------
// devolve o nome do vertice v
//return v->v_name;
char *nome_vertice(vertice v){
	
		return v->v_name;
	
	};

//------------------------------------------------------------------------------
// lê um grafo no formato dot de input, usando as rotinas de libcgraph
// 
// desconsidera todos os atributos do grafo lido exceto o atributo
// "peso" quando ocorrer; neste caso o valor do atributo é o peso da
// aresta/arco que é um long int
// 
// num grafo com pesos todas as arestas/arcos tem peso
// 
// o peso default de uma aresta num grafo com pesos é 0
// 
// todas as estruturas de dados alocadas pela libcgraph são
// desalocadas ao final da execução
// 
// devolve o grafo lido ou
//         NULL em caso de erro 
/*
 * coloca  em g o nome do grafo e a lista de vértices, ai para cada vertice  cria a lista de edges, pra cada edge cria um no na lista e faz ele apontar pro vertice 
 * 
 * */
grafo le_grafo(FILE *input){
	Agraph_t *g;
	int i = 0, node_number, j = 0;
	no da_vez, a_da_vez; 
	Agedge_t *edge;
	
	
	g = agread(input, NULL);
	
	grafo graph;
	graph = malloc(sizeof(struct grafo));
	graph->directed = 0;
	
	//inicia grafo
	graph->directed = agisdirected(g);
	graph->g_name = (char*) malloc(255*sizeof(char));
	strcpy(graph->g_name,agnameof(g));
	graph->vertex = constroi_lista();
	
	//declara o primeiro nó da lista de vertices
	da_vez = malloc(sizeof(struct no));
	
	da_vez->conteudo =  malloc(sizeof(struct vertice));
	da_vez->vertex = NULL;
	graph->vertex->primeiro = da_vez;
	
	da_vez = graph->vertex->primeiro;
	
	//comeca a iniciar os vertices
	node_number = agnnodes(g);
	
	Agnode_t *nodo;
	nodo = agfstnode(g);
	for(i; i < node_number; i++){
		//busca o nome do vertice
		
		da_vez->conteudo->v_name = agnameof(nodo);
		
		if(agisundirected(g)){
			graph->directed = 0;
		//constroi a lista de edges sem direção
		
		da_vez->conteudo->edges_out = constroi_lista();
		//aloca o primeiro nó
		da_vez->conteudo->edges_out->primeiro = malloc(sizeof(struct no));
		
		//pega o primeiro edge
		
		edge = agfstedge(g, nodo);
		a_da_vez = da_vez->conteudo->edges_out->primeiro;
		da_vez->conteudo->edges_out->tamanho = 0;
		
		//pegas as edges
		while(edge != NULL){
			char *peso = agget(edge, "peso");
			
			if(peso != NULL){
				graph->weighted = 1;
			}
			if(da_vez->conteudo->v_name != agnameof(aghead(edge)) ){
				
				a_da_vez->vertex = (char*) malloc(255*sizeof(char));
				strcpy(a_da_vez->vertex,agnameof(aghead(edge)));
				
				if(peso == NULL)
					a_da_vez->peso = 0; // peso
				else
					a_da_vez->peso = atoi(peso);
					
				
				da_vez->conteudo->edges_out->tamanho += 1;
				
				a_da_vez->proximo = malloc(sizeof(struct no));
				a_da_vez = a_da_vez->proximo;
			}else{
			}
				
				edge = agnxtedge(g,edge, nodo);
				
		}
	}
	
	
		if(agisdirected(g)){
			
			graph->directed = 1;
			//constroi a lista de edges_in
			
			da_vez->conteudo->edges_in = constroi_lista();
			//aloca o primeiro nó
			da_vez->conteudo->edges_in->primeiro = malloc(sizeof(struct no));
			
			//pega o primeiro edgein
			//Agedge_t *edge;
			edge = agfstin(g, nodo);
			a_da_vez = da_vez->conteudo->edges_in->primeiro;
			da_vez->conteudo->edges_in->tamanho = 0;
			
			//pegas as edges_in
			while(edge != NULL){
				char *peso = agget(edge, "peso");
				if(peso != NULL){
					graph->weighted = 1;
				}
				if(da_vez->conteudo->v_name != agnameof(agtail(edge)) ){
					a_da_vez->vertex = (char*) malloc(255*sizeof(char));
					strcpy(a_da_vez->vertex,agnameof(aghead(edge)));
					
					if(peso == NULL)
						a_da_vez->peso = 0; // peso
					else
						a_da_vez->peso = atoi(peso);
						
					
					da_vez->conteudo->edges_in->tamanho += 1;
					
					a_da_vez->proximo = malloc(sizeof(struct no));
				}
					edge = agnxtin(g,edge);
					a_da_vez = a_da_vez->proximo;
			}
		
		
		
			//constroi a lista de edges_out
			
			da_vez->conteudo->edges_out = constroi_lista();
			//aloca o primeiro nó
			da_vez->conteudo->edges_out->primeiro = malloc(sizeof(struct no));
			
			//pega o primeiro edge_out
			//Agedge_t *edge;
			edge = agfstout(g, nodo);
			a_da_vez = da_vez->conteudo->edges_out->primeiro;
			da_vez->conteudo->edges_out->tamanho = 0;
			
			//pegas as edges_out
			while(edge != NULL){
				char *peso = agget(edge, "peso");
				if(peso != NULL){
					graph->weighted = 1;
				}
					
				if(da_vez->conteudo->v_name != agnameof(aghead(edge)) ){
					a_da_vez->vertex = (char*) malloc(255*sizeof(char));
					strcpy(a_da_vez->vertex,agnameof(aghead(edge)));
					
					if(peso == NULL)
						a_da_vez->peso = 0; // peso
					else
						a_da_vez->peso = atoi(peso);
						
					
					da_vez->conteudo->edges_out->tamanho += 1;
					
					a_da_vez->proximo = malloc(sizeof(struct no));
				}
					edge = agnxtout(g,edge);
					a_da_vez = a_da_vez->proximo;
			}
		}
		
		a_da_vez = NULL;
		//vai pro proximo no
		da_vez->proximo = malloc(sizeof(struct no));
		da_vez = da_vez->proximo;
		da_vez->conteudo = malloc(sizeof(vertice));
		da_vez->vertex = NULL;
		graph->vertex->tamanho += 1;
		nodo = agnxtnode(g, nodo);
	}
	agclose(g);
	return(graph);
};  

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
// 
// devolve 1 em caso de sucesso ou
//         0 caso contrário
// 
// g é um (void *) para que destroi_grafo() possa ser usada como argumento de
// destroi_lista()

int destroi_grafo(void *g){
	no da_vez, da_vez_prox;
	grafo g2 = g;
	int i = 0;
	da_vez = g2->vertex->primeiro;
	for(i = 0; i < g2->vertex->tamanho;i++){
			
		destroi_lista(da_vez->conteudo->edges_out, NULL);
		destroi_lista(da_vez->conteudo->edges_in, NULL);
		free(da_vez->conteudo);
		da_vez_prox = da_vez->proximo;
		free(da_vez);
		da_vez = da_vez_prox;
		
	}
	destroi_lista(g2->vertex, NULL);
	return 1;
	
	};

//------------------------------------------------------------------------------
// escreve o grafo g em output usando o formato dot, de forma que
// 
// 1. todos os vértices são escritos antes de todas as arestas/arcos 
// 
// 2. se uma aresta tem peso, este deve ser escrito como um atributo 
//    de nome "peso"
//
// devolve o grafo escrito ou
//         NULL em caso de erro 

grafo escreve_grafo(FILE *output, grafo g){
	no da_vez, a_da_vez;
	int i = 0, node_number, j = 0;
		
	da_vez = g->vertex->primeiro;	
	node_number = g->vertex->tamanho;
	if(g->directed){
			fprintf(output, "digraph %s{\n", g->g_name);
	}else{
			fprintf(output, "graph %s{\n", g->g_name);
	}


  for(i = 0; i < node_number; i++){


              fprintf(output, "       %s\n",da_vez->conteudo->v_name); 

                da_vez = da_vez->proximo;
        }

	da_vez = g->vertex->primeiro;

	for(i = 0; i < node_number; i++){
		
		
		a_da_vez = da_vez->conteudo->edges_out->primeiro;
		if(da_vez->conteudo->edges_out->tamanho != 0){
			for(j = 0;j < da_vez->conteudo->edges_out->tamanho;j++){
				if(g->directed == 0){
					fprintf(output, "	%s -- %s",da_vez->conteudo->v_name, a_da_vez->vertex);
					if(g->weighted)
						fprintf(output, "\t[peso==%ld]",a_da_vez->peso);
					fprintf(output, ";\n");
				}else{
						fprintf(output, "	%s -> %s",da_vez->conteudo->v_name, a_da_vez->vertex);
						if(g->weighted)
							fprintf(output, "\t[peso==%ld]",a_da_vez->peso);
						fprintf(output, ";\n");
				}
				a_da_vez = a_da_vez->proximo;
				
				
			}
		}
		
		da_vez = da_vez->proximo;
	}
	fprintf(output, "}\n");
	
	return(g);
	};

//------------------------------------------------------------------------------
// devolve a vizinhança do vértice v
/*
 * lista neighborhood;
 * node = primeiro_no(v->edges_in);
 * for(i to tamanho_lista(v->edges_in){
 * 	insere(node->vertex, neighborhood);
 * node = proximo_no(node);
 * }
 * 
 * */
lista vizinhanca(vertice v){
	
	return v->edges_out;
	
	};
//------------------------------------------------------------------------------
// devolve a vizinhança de entrada do vértice v
/*
 * lista neighborhood_in;
 * node = primeiro_no(v->edges_in);
 * for(i to tamanho_lista(v->edges_in){
 * 	insere(node->vertex, neighborhood_in);
 * node = proximo_no(node);
 * }
 * 
 * */
lista vizinhanca_entrada(vertice v){
	
	return v->edges_in;
	
	};

//------------------------------------------------------------------------------
// devolve a vizinhança de saída do vértice v
/*
 * lista neighborhood_out;
 * node = primeiro_no(v->edges_uout);
 * for(i to tamanho_lista(v->edges_out){
 * 	insere(node->vertex, neighborhood_out);
 * node = proximo_no(node);
 * }
 * 
 * */
lista vizinhanca_saida(vertice v){
	
	return v->edges_out;
	
	};

//------------------------------------------------------------------------------
// devolve o grau do vértice v
/*
 * return tamanho(v->edges_in);
 *  
 * */
unsigned int grau(vertice v){
	
	return v->edges_out->tamanho;
	
	};

//------------------------------------------------------------------------------
// devolve o grau de entrada do vértice v
/*
 * return tamanho(v->edges_in);
 *  
 * */
unsigned int grau_entrada(vertice v){
	return v->edges_in->tamanho;
	
	};

//------------------------------------------------------------------------------
// devolve o grau se saída do vértice v
/*
 * return tamanho(v->edges_out);
 *  
 * */
unsigned int grau_saida(vertice v){
	return v->edges_out->tamanho;
	};
