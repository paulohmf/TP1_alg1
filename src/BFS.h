#ifndef __TP1__
#define __TP1__

#include "util.cc"

using namespace std;

list <node_tree*> my_BFS
	(
	/*	Return: 
			a função retorna uma lista de jogadas para que o jogador ganhe
			caso não seja possivel ganhar a lista e retornada vazia
	*/

	int board_n,int board_m,	//	Dimensões do board
	int *player, 				//  Vertice inicial, vetor de coordenadas do player em questão
	list <edge*> *all_edges 	//  Listas de adjacencia
	
	);

#endif