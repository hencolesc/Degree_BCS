#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define BRANCO 0
#define CINZA 1
#define PRETO 2

int main(int argc, char **argv) {
	int v_num2;
	printf("Digite a quantidade de vertices: ");

	scanf("%d", &v_num2);


	int ** adj_list2 = (int **)malloc(v_num2 * sizeof(int *)), tam_adj_lists2[v_num2], node, adj, i = 0;

	for(i = 0; i < v_num2; i++) {
		tam_adj_lists2[i] = 0;
	}

	printf("Digite x nodos, terminando com -1, tal que n0 ---> n1, n0 ---> n2, n0 ---> n3, (...) , n0 ---> nx: ");
	scanf("%d", &node);


	while(node >= 0) {
		scanf("%d", &adj);

		while(adj >= 0) {
			if(tam_adj_lists2[node] == 0){ // aloca 1º item da lista
				adj_list2[node] = (int *)malloc(sizeof(int));
			}else { // aloca + 1 inteiro na lista de inteiros que ja foi alocada
				adj_list2[node] = (int *)realloc(adj_list2[node], sizeof(int));
			}

			adj_list2[node][tam_adj_lists2[node]] = adj; // aresta de Ti p/ Tj
			tam_adj_lists2[node]++; // incrementa tamanho dessa lista que aumentou em 1
			scanf("%d", &adj);
		}
		
		printf("Digite x nodos, terminando com -1, tal que n0 ---> n1, n0 ---> n2, n0 ---> n3, (...) , n0 ---> nx: ");
		scanf("%d", &node);
	}

	if(graph_no_cycle(adj_list2, tam_adj_lists2, v_num2)) {
		printf("Nao achou ciclo\n");
	}
	else {
		printf("Achou ciclo\n");
	}

	adj_list2 = clean_adj_list(adj_list2, v_num2); // libera lista de listas, o grafo do escalonamento atual

	return 0;
}
