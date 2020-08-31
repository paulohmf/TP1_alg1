#ifndef __TP1__
#define __TP1__

#include "util.cc"

#endif

using namespace std;

//	Cria todos os movimentos válidos e a lista de adjacência para cada vertice baseado no tamanho do pulo 
list <edge*>* get_edges
	(
	int board_n, 		// Tamanho N do board
	int board_m,		// Tamanho M do board
	int *plain_board	// Versão plana do tabuleiro
	);
	// Retorno:
	//	retorna um vetor de listas de adjacencia para cada nó do grafo,
	//	as listas são formadas por um conjunto de Edges

	// Edges seguem o formato:
	//		int nodeB_n,nodeB_m; -> nó "vizinho"
	//		int jump;            -> peso da arresta