#include "BFS.h"

list <node_tree*> my_BFS(
	int board_n,int board_m,	//	Dimensões do board
	int *player, 				//  Vertice inicial, vetor de coordenadas do player em questão
	list <edge*> *all_edges 	//  Listas de adjacencia
	){
	/*	
		Return: 
			a função retorna uma lista de jogadas para que o jogador ganhe
			caso não seja possivel ganhar a lista e retornada vazia
	*/

	// 	Mudança de formato da lista de all_edges para uma matrix edges[M][N] para facilitar acesso *(A)
	// 													e
	//	inicializar uma matrix para cada nó do grafo caso ele tenha sido descoberto, 0 para todos menos vertice de entrada *(B)
	list <edge*> edges_matrix[board_n][board_m]; // *(A)
	int discovered[board_n][board_m];			 // *(B)

	int control = 0;
	for(int N=0 ;N < board_n; N++){
		for(int M=0; M < board_m; M++){
			edges_matrix[N][M] = all_edges[control];
			control++;

			discovered[N][M] = 0;
		}
	}
	discovered[player[0]][player[1]] = 1;

	//	iniciar o nó raiz com o vertice de entrada, colocar o vertice ná fila e na lista de nós da arvore BFS gerada
	int deep = 1;

	node_tree* root = new node_tree;
	root->node_deep = 0;
	root->jump = -1; //no jump
	root->value[0] = player[0];
	root->value[1] = player[1];
	root->parent[0] = -1; //no parent
	root->parent[1] = -1; //no parent

	queue <node_tree*> search_queue;
	search_queue.push(root);

	list <node_tree*> BFS_tree_nodes;
 	BFS_tree_nodes.push_front(root);

 	//	Percorre o grafo até encontrar a posição M-1, N-1 da matriz, ou até acabarem os nós
 	bool win = false;
 	while(!search_queue.empty()){

		node_tree node_now;
		node_now = (*search_queue.front());
		search_queue.pop();

		deep = node_now.node_deep+1; 

		list <edge*> node_adjacency_list;
		node_adjacency_list =  edges_matrix[node_now.value[0]][node_now.value[1]]; // Acesso a lista de adjacencia salva na matrix adaptada acima

		// Percorre lista de adjacencia de um nó, caso ele ainda não tenha sido descoberto
		list <edge*> :: iterator it;
		for(it = (node_adjacency_list).begin(); it != (node_adjacency_list).end(); it++){ 

        	int node_N,node_M;
        	node_N = (*it)->nodeB_n;
			node_M = (*it)->nodeB_m;

        	if(discovered[node_N][node_M] == 0){	// se o nó ainda não tiver sido descoberto
        		discovered[node_N][node_M] = 1;

        		node_tree* new_node_tree = new node_tree;
				new_node_tree->node_deep = deep; 				// deep
				new_node_tree->jump = (*it)->jump;				// jump
				new_node_tree->value[0] = node_N; 				// value_N
				new_node_tree->value[1] = node_M; 				// value_M
				new_node_tree->parent[0] = node_now.value[0];   // parent N
				new_node_tree->parent[1] = node_now.value[1];   // parent M

				BFS_tree_nodes.push_back(new_node_tree);
				search_queue.push(new_node_tree);

				// Caso encontre o final do tabuleiro para de gerar a árvore BFS
				if((new_node_tree->value[0] == board_n-1) && (new_node_tree->value[1] == board_m-1)){
					win = true;
					break;
				}
    		}
    	}
    	if(win){
    		break;
    	}

 	}
 	// Lista para retorno
 	list <node_tree*> fastest_path;

	// Caso o player não consiga ganhar retorna uma lista vazia
	if(!win){
		return fastest_path;
	}

	// Eliminar jogadas desnecessarias da lista, salva apenas as jogadas necessarias para ganhar
	int parent_n,parent_m;
	list <node_tree*> :: iterator itr;

	// Para isso, pega o pai do ultimo nó da lista, que representa o a vitoria
	itr = (BFS_tree_nodes).end();
	itr--;
	parent_n = (*itr)->parent[0];
	parent_m = (*itr)->parent[1];

	fastest_path.push_front(*itr);

	// Percorre apartir do ultimo nó da lista até a posição inicial do players salvando apenas os nós necessários para o caminho 
	itr--;
	for(; itr != (BFS_tree_nodes).begin(); itr--){
        if(((*itr)->value[0] == parent_n) && ((*itr)->value[1] == parent_m)){
        	parent_n = (*itr)->parent[0];
        	parent_m = (*itr)->parent[1];
			fastest_path.push_front(*itr);
		}
    }
    // Salva a raiz da árvore (não necessário)
	//fastest_path.push_front(root);

	BFS_tree_nodes.clear();

	return fastest_path;
};
