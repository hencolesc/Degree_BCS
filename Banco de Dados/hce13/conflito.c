// Trabalho da disciplina CI218 - Sistemas de Bancos de Dados ministrado pelo docente Eduardo Cunha de Almeida
// Autor: Henrique Colodetti Escanferla - GRR20135427


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define BRANCO 0
#define CINZA 1
#define PRETO 2


// define item de uma lista
typedef struct node {
	int data;
	struct node * next;
} node_t;


// true se n/ houver o nº no array, false caso contrario
bool not_in_array(int num, int array[], int tam) {
	int i; // for loop
	bool not_found = true; // supostamente verdadeiro

	for(i = 0; i < tam; i++) {
		if(array[i] == num) { // achou o nº, saia do loop
			not_found = false;
			break;
		}
	}

	return not_found; // retorna resultado
}


// insere nodo na lista
node_t * insert_node(node_t * head, int data) {
	node_t * current = head;

	while(current != NULL && current->next != NULL) { // lista vazia ou chegou no item final
		current = current->next;
	}

	node_t * novo = (node_t *) malloc(sizeof(node_t));

	if(!novo) { // erro
		printf("Sem memoria disponivel!\n");
		exit(1);
	}else {
		novo->data = data; // insere dado no novo item da lista
		novo->next = NULL; // fim da lista
		if(current != NULL) {
			current->next = novo; // linka o ultimo nodo c/ o novo novo
		}
		else {
			head = novo; // 1º item da lista
		}
		return head; // retorna o inicio da lista
	}
}


// remover node da lista
void remove_node(node_t * ant, node_t * node, node_t * pos) {
	if(node == NULL || ant == NULL) {
		printf("Erro: ponteiro a remover ou o antecessor deste para linkar n/ existe!\n");
		exit(1);
	}

	free(node);
	ant->next = pos; // elimina o "buraco" na lista originado pela remocao
}


// imprime lista na tela
void print_list(node_t * head) {
	node_t * current = head;

	printf("A lista contem a seguinte informacao:\n");
    	while (current != NULL) {
        	printf("%d ", current->data);
        	current = current->next;
    	}
	printf("\n");
}


// deleta 1º item c/ a informacao pedida
node_t * remove_node_by_data(node_t * head, int data) {
	node_t * current = head;

	if(head == NULL) {
		printf("Erro: remover de lista vazia!\n");
		exit(1);
	}

	node_t * pos_current = head->next;

	if(head->data == data) { // remove 1º item da lista
		if(pos_current == NULL) { // caso unico item
			free(head);
			return NULL;
		}

		free(head);
		return pos_current; // caso contrario, libera o 1º e retorna a lista c/ o resto dos itens
	}

	while(pos_current->data != data && pos_current->next != NULL) { // lista vazia ou chegou no item final
		current = pos_current;
		pos_current = pos_current->next;
	}

	if(pos_current->data == data) {
		remove_node(current, pos_current, pos_current->next);
	}

	return head;
}


// true se a lista n/ contem nodo c/ a informacao "data", false caso contrario
bool not_contain_node(node_t * head, int data) {
	if(head == NULL) {
		return true;
	}

	while(head->data != data && head->next != NULL) { // percorre lista
		head = head->next;
	}

	if(head->data == data) { // achou
		return false;
	}

	return true; // fim da lista e n/ achou
}


// true se lista eh vazia, false caso contrario
bool list_is_empty(node_t * head) {
	if(head != NULL) {
		return false; // n/ eh vazia
	}

	return true; // eh vazia
}


// desaloca lista
node_t * clean_list(node_t * head) {
	node_t * current = head;

	while(head != NULL) {
		head = head->next;
		free(current);
		current = head;
	}

	return head;
}


// retorna informacao do indice na lista
int get_data_by_index_list(node_t * head, int index) {
	int i; // for loop

	for(i = 0; (head != NULL) && (i != index); i++) {
		head = head->next;
	}

	if(head != NULL) { // sai do loop porque encontrei o nodo do index e o head aponta para ele

		return head->data;
	}

	return -1; // indice fora da lista
}


// retorna indice da informacao na lista
int get_index_by_data_list(node_t * head, int data) {
	int i; // for loop

	for(i = 0; (head != NULL) && (head->data != data); i++) {
		head = head->next;
	}

	if(head != NULL) { // sai do loop porque encontrei o index do nodo: i

		return i;
	}

	return -1; // n/ ha data aqui
}


// le o proximo escalonamento da entrada
int read_escal(node_t ** num_list, node_t ** tnum_list, node_t ** cmd_list, node_t ** var_list, node_t ** ts_list) {
	// enumerar linhas do 0; nº da linha na entrada; nº da transacao; nº de transacoes no escalonamento atual
	int i = 0, num, tnum, ts_escal_num = 0;
	char cmd, var; // comando lido; variavel lida, '-' => N.A.
	node_t * ts_n_commit_list = NULL; // lista de transacoes n comitadas

	// enquanto n/ comitam as transacoes, ler 2 inteiros e 2 caracteres entre espacos
	while(fscanf(stdin, "%d %d %c %c", &num, &tnum, &cmd, &var) > 0) {
		// lista por ordem de chegada das transacoes, a partir de seus indices trabalhamos somente c/ nºs de 0 a n
		if(not_contain_node(* ts_list, tnum)) {
			* ts_list = insert_node(* ts_list, tnum);
		}

		tnum = get_index_by_data_list(* ts_list, tnum); // deixa o nº das transacoes "amigaveis" p/ indexar, de 0 a n

		if(not_contain_node(ts_n_commit_list, tnum)) {
			ts_n_commit_list = insert_node(ts_n_commit_list, tnum);
			ts_escal_num++; // conta transacoes no escalonamento em analise
		}
		else{
			if(cmd == 'C') {
				// verifica o fim do escalonamento quando as transacoes comitarem
				ts_n_commit_list = remove_node_by_data(ts_n_commit_list, tnum);
			}
		}

		if(list_is_empty(ts_n_commit_list)) {

			return ts_escal_num; // retorna a contagem

		}
		// salva linha p/ processar depois
		* num_list = insert_node(* num_list, i);
		* tnum_list = insert_node(* tnum_list, tnum);
		* cmd_list = insert_node(* cmd_list, cmd);
		* var_list = insert_node(* var_list, var);

		i++; // nº da linha no escalonamento
	}

	return 0; // aviso de EOF
}


// imprime listas de adjacencias dos vertices
void print_adj_list(int ** adj_list, int tam_adj_lists[], int v_num) {
	int i, j;

	printf("Imprimindo lista de adjacencias . . .\n\n%d vertices\n\n", v_num);

	for(i = 0; i < v_num; i++){
		printf("O vertice %d tem %d adjacencias\n\n", i, tam_adj_lists[i]);
	}

	for(i = 0, j = 0; i < v_num; i++) {
		printf("Vertice %d: ", i);

		for(j = 0; j < tam_adj_lists[i]; j++) { 
			printf("%d ", adj_list[i][j]);
		}

		printf("\n");
	}

	printf("\n");
}


// gera matriz de adjacencia do grafo no escalonamento
int ** make_adj_list(int tam_adj_lists[], int v_num, node_t * num_list, node_t * tnum_list, node_t * cmd_list, node_t * var_list) {
	int **adj_list = (int **)malloc(v_num * sizeof(int *)); // lista de listas de adjacencias dos vertices
	// comparar num_line, cmd e var de transacoes Ti(antes) e Tj(depois); i e j for loops;
	int num_line, tnum_ant, tnum_pos, i, j;
	char cmd_ant, var_ant, cmd_pos, var_pos;

	// lista de tamanhos das listas de adj_list; lista de listas de inteiros
	for (i = 0; i < v_num; i++) { // tamanhos e enderecos comecam c/ 0/NULL p/ evitar double free ou corruption memory
		tam_adj_lists[i] = 0;
		adj_list[i] = NULL;
		
	}

	num_line = get_data_by_index_list(num_list, 0);
	tnum_ant = get_data_by_index_list(tnum_list, 0);
	cmd_ant = (char) get_data_by_index_list(cmd_list, 0);
	var_ant = (char) get_data_by_index_list(var_list, 0); // le 1º linha

	// percorre os escalonamentos em ordem de chegada, fim da lista retorna -1
	for(i = 0; num_line >= 0;) {

		if(cmd_ant == 'R') { // 2º caso da especificacao
			
			// le a prox. linha
			tnum_pos = get_data_by_index_list(tnum_list, num_line);
			cmd_pos = (char) get_data_by_index_list(cmd_list, num_line);
			var_pos = (char) get_data_by_index_list(var_list, num_line);

			// j c/eca c/ num_line pois eh o indice + 1 do indice de num_line
			for(j = num_line; tnum_pos >= 0;) { // loop percorre as linhas apos o num_line ate o fim das linhas (-1 na lista)

				if(tnum_pos != tnum_ant && cmd_pos == 'W' && var_pos == var_ant &&
				   not_in_array(tnum_pos, adj_list[tnum_ant], tam_adj_lists[tnum_ant])) {
					if(tam_adj_lists[tnum_ant] == 0){ // aloca 1º item da lista
						adj_list[tnum_ant] = (int *)malloc(sizeof(int));
					}else { // aloca + 1 inteiro na lista de inteiros que ja foi alocada
						adj_list[tnum_ant] = (int *)realloc(adj_list[tnum_ant], sizeof(int));
					}

					adj_list[tnum_ant][tam_adj_lists[tnum_ant]] = tnum_pos; // aresta de Ti p/ Tj
					tam_adj_lists[tnum_ant]++; // incrementa tamanho dessa lista que aumentou em 1
				}

				j++;
				// le quase a prox. linha
				tnum_pos = get_data_by_index_list(tnum_list, j);
				cmd_pos = (char) get_data_by_index_list(cmd_list, j);
				var_pos = (char) get_data_by_index_list(var_list, j);
			}
		}else {
			if(cmd_ant == 'W') { // 1º e 3º casos da especificacao
				// le a prox. linha
				tnum_pos = get_data_by_index_list(tnum_list, num_line);
				cmd_pos = (char) get_data_by_index_list(cmd_list, num_line);
				var_pos = (char) get_data_by_index_list(var_list, num_line);

				// j comeca c/ num_line pois eh o indice + 1 do indice de num_line
				// loop percorre as linhas apos o num_line ate o fim das linhas (-1 na lista)
				for(j = num_line; tnum_pos >= 0;) {
					if(tnum_pos != tnum_ant && cmd_pos != 'C' && var_pos == var_ant &&
					   not_in_array(tnum_pos, adj_list[tnum_ant], tam_adj_lists[tnum_ant])) {
						if(tam_adj_lists[tnum_ant] == 0){ // aloca 1º item da lista
							adj_list[tnum_ant] = (int *)malloc(sizeof(int));
						}else { // aloca + 1 inteiro na lista de inteiros que ja foi alocada
							adj_list[tnum_ant] = (int *)realloc(adj_list[tnum_ant], sizeof(int));
						}

						adj_list[tnum_ant][tam_adj_lists[tnum_ant]] = tnum_pos; // aresta de Ti p/ Tj
						tam_adj_lists[tnum_ant]++; // incrementa tamanho dessa lista que aumentou em 1
					}

					j++;
					// le quase a prox. linha
					tnum_pos = get_data_by_index_list(tnum_list, j);
					cmd_pos = (char) get_data_by_index_list(cmd_list, j);
					var_pos = (char) get_data_by_index_list(var_list, j);
				}	
			}
		}

		i++;
		num_line = get_data_by_index_list(num_list, i);
		tnum_ant = get_data_by_index_list(tnum_list, i);
		cmd_ant = (char) get_data_by_index_list(cmd_list, i);
		var_ant = (char) get_data_by_index_list(var_list, i); // le prox. linha
	}

	return adj_list; // devolve a lista de listas de adjacencias gerada
}


// libera lista de listas de adjacencias que representa o grafo
int ** clean_adj_list(int ** adj_list, int v_num) {
	int i; // iterador for loop

	for(i = 0; i < v_num; i++) {
		free(adj_list[i]); // libera lista de inteiros
		adj_list[i] = NULL;
	}

	free(adj_list); // libera lista de listas

	return NULL;
}


// imprime pilha
void print_pile(int * pile, int tam_pile) {
	int i; // for loop

	printf("Imprimindo pilha . . .\n\n");
	for(i = tam_pile - 1; i >= 0; i--) {
		printf("%d\n", pile[i]);
	}
}


void print_cycle(int *pile, int tam_pile, int start_end_vert_cycle) {
	int i; // for loop

	printf("\n\nCiclo encontrado . . .\n");

	// o vertice que esta no começo e no final do ciclo eh o v_prox encontrado em terr_cycle
	for(i = 0; pile[i] != start_end_vert_cycle; i++) {
	}

	for(; i < tam_pile - 1; i++) { // printa a partir de v_prox
		printf("%d ---> ", pile[i]);
	}

	printf("%d ---> %d\n", pile[i], start_end_vert_cycle); // termina com o arco do topo da pilha com v_prox, fechando o ciclo
	printf("Fim da impressao do ciclo encontrado\n\n");
}


// Link p/ algoritmo => https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/cycles-and-dags.html
// se territorio eh ciclico, true; false caso contrario
bool terr_cycle(int ** adj_list, int color[], int tam_adj_lists[], int start_v, int v_num) {
	// marcadores p/ n pegar um vertice adjacente ao top_pile + de 1 vez; tamanho da pilha; pilha de vertices p/ backtracking
	int prox_adj[v_num], tam_pile = 1, * pile = (int *)malloc(sizeof(int)), i;

	pile[0] = start_v; // empilha start_v, por onde comecaremos a buscar ciclos em seu territorio
	color[start_v] = CINZA; // marca vertice procurando um ciclo

	// inicialmente podemos pegar qualquer vertice adjacente ao top_pile, marcadores iniciam c/ 0
	for(i = 0; i < v_num; i++) {
		prox_adj[i] = 0;
	}

	while(tam_pile > 0) { // enquanto pilha n eh vazia
		int top_pile = pile[tam_pile - 1]; // topo da pilha

		if(prox_adj[top_pile] < tam_adj_lists[top_pile]) {
			int v_prox = adj_list[top_pile][prox_adj[top_pile]]; // verificar prox adjacente a vert, cada um so uma vez
			prox_adj[top_pile]++; // n pegue este vertice da lista de adjacentes de novo
			if(color[v_prox] == CINZA) {
				// print_cycle(pile, tam_pile, v_prox); // descomente p/ printar o ciclo encontrado
				free(pile); // libera pilha

				return true; // achou ciclo, pare de procurar
			}else {
				if(color[v_prox] == BRANCO) { // achei um vertice que n procurei ainda
					color[v_prox] = CINZA; // marca que esta procurando por aqui
					tam_pile++; // aumenta tamanho da pilha em 1
					pile = (int *)realloc(pile, tam_pile * sizeof(int)); // aumenta a pilha em 1
					pile[tam_pile - 1] = v_prox; // novo topo da pilha
				}
			}
		}else { // encontrou um caminho inevitavel p/ um sorvedouro => vertice beco s/ saida
			color[top_pile] = PRETO; // marca p/ n procurar + por aqui afinal eh um caminho p/ um sorvedouro
			tam_pile--; // diminui tamanho da pilha em 1
			pile = (int *)realloc(pile, tam_pile * sizeof(int)); // diminui a pilha em 1, eliminando o topo
		}
	}

	return false; // percorreu todo o territorio de vert e n achou ciclo
}


// Link p/ algoritmo => https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/cycles-and-dags.html
// se grafo eh aciclico, true; false caso contrario
bool graph_no_cycle(int ** adj_list, int tam_adj_lists[], int v_num) {
	// iterador de loop, vetor de inteiros p marcar os vertices do grafo
	int i, * color = (int *)malloc(v_num * sizeof(int));

	for(i = 0; i < v_num; i++) { // todos os vertices comecam brancos
		color[i] = BRANCO;
	}

	for(i = 0; i < v_num; i++) { // se vertice eh branco procura ciclo em seu territorio, caso contrario verifica proximo vertice

		if(color[i] == BRANCO && terr_cycle(adj_list, color, tam_adj_lists, i, v_num)) {
			free(color); // libera memoria

			return false; // achou ciclo, grafo n/ eh aciclico
		}
	}
	
	free(color); // libera memoria

	return true; // grafo eh aciclico
}


int main(int argc, char **argv) {
	// quantidade de vertices do grafo; contador p/ enumerar as linhas na saida
	int v_num, i = 1, j;
	// as 4 listas guardarao as informacoes dos escalonamentos; a 5º lista registra, por ordem de chegada, as transacoes; for loop
	node_t * num_list = NULL, * tnum_list = NULL, * cmd_list = NULL, * var_list = NULL, * ts_list = NULL;

	// enquanto n/ ler EOF, gerar grafo do escalonamento lido em "read_escal"
	while((v_num = read_escal(&num_list, &tnum_list, &cmd_list, &var_list, &ts_list)) > 0) {
		// tamanho das listas de adjacencias; lista de listas de adjacencias dos vertices
		int tam_adj_lists[v_num], ** adj_list = make_adj_list(tam_adj_lists, v_num, num_list, tnum_list, cmd_list, var_list);

		// desaloca listas
		num_list = clean_list(num_list);
		tnum_list = clean_list(tnum_list);
		cmd_list = clean_list(cmd_list);
		var_list = clean_list(var_list);
		
		printf("%d ", i); // nº da linha na saida

		// imprime as transacoes lidas na ordem da entrada entre virgulas
		for(j = 0; j < v_num - 1; j++) {
			printf("%d,", get_data_by_index_list(ts_list, j));
		}

		printf("%d ", get_data_by_index_list(ts_list, j)); // o ultimo nº da transacao n/ tera uma virgula depois dele

		if(graph_no_cycle(adj_list, tam_adj_lists, v_num)) {
			printf("SIM\n");
		}
		else {
			printf("NAO\n");
		}

		ts_list = clean_list(ts_list); // libera lista de transacoes do escalonamento atual
		adj_list = clean_adj_list(adj_list, v_num); // libera lista de listas, o grafo do escalonamento atual

		i++; // incrementa linha na saida
	}

	return 0;
}


