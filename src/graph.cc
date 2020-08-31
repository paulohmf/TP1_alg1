#include "graph.h"

list <edge*>* get_edges
	(
	int board_n, 		// Tamanho N do board
	int board_m,		// Tamanho M do board
	int *plain_board	// Versão plana do tabuleiro
	){

	// Tranforma a versão plana do tabuleito em uma versão bidimensional [M][N] 
	int board[board_n][board_m];
	int aux = 0;
	for(int N=0 ;N < board_n; N++){
		for(int M=0; M < board_m; M++){
			board[N][M] = plain_board[aux];
			aux++;
		}
	}

	// Cria a lista de listas de adjacencia que sera retornada pela função
	list <edge*> *all_edges = new list <edge*>[board_n*board_m];

	//	Cria todos os movimentos válidos e a lista de adjacência para cada vertice baseado no tamanho do pulo 
	int control = 0;
	for(int N=0 ;N < board_n; N++){
		for(int M=0; M < board_m; M++){
			int jump = board[N][M];

			if(jump > 0){
				if(M+jump < board_m){
					edge *right = new edge();
					right->jump = jump;
					right->nodeB_n = N;
					right->nodeB_m = M+jump;
					all_edges[control].push_back(right);
				}

				if(M-jump >= 0){
					edge *left = new edge();
					left->jump = jump;
					left->nodeB_n = N;
					left->nodeB_m = M-jump;
					all_edges[control].push_back(left);
				}

				if(N-jump >= 0){
					edge *up = new edge();
					up->jump = jump;
					up->nodeB_n = N-jump;
					up->nodeB_m = M;
					all_edges[control].push_back(up);
				}

				if(N+jump < board_n){
					edge *down = new edge();
					down->jump = jump;
					down->nodeB_n = N+jump;
					down->nodeB_m = M;
					all_edges[control].push_back(down);
				}
			}
			control++;
		}

	}
	return all_edges;
};