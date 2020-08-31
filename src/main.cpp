#include <iostream>
#include <queue>
#include <fstream>

#include "BFS.h"
#include "graph.h"

using namespace std;

void clear_all(std::list <edge*> *all_edges, int size){
	for(int o=0 ;o < size; o++){
		all_edges[o].clear();
	}
	all_edges->clear();
};

int main(int argc, char *argv[]){
	// Recebendo as entradas ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if(argc > 2){
		cout << "Insira o caminho para o arquivo de entrada" << endl;
		return 0;
	}
	string filename = "";
	filename = argv[1];

	string line = "";
	ifstream file(filename);
	if(!file.is_open()){
		cout << "Não foi possivel abrir o arquivo de entrada" << endl;
		return 0;
	}

	int board_n, board_m, num_player;
	file >> board_n >> board_m >> num_player;

	int board[(board_n*board_m)];
	for(int k=0 ;k < board_n*board_m ; k++){
		file >> board[k];
	}

	int players[num_player+1][4];

	for(int p=0; p<num_player ;p++){
		file >> players[p][0]; // coord n
		file >> players[p][1]; // coord m
		players[p][2] = p; 	  // ordem de entrada
	}
	file.close();

	// Transforma a entrada em um grafo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//	Gera uma lista de adjacencia para cada vertice, consideramos um vertice cada uma posição [M][N] do board
	list <edge*> *all_edges; 
	all_edges = get_edges(board_n,board_m, board);

	// Descobre o caminho otimo para cada player, se existir ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	// Usar o BFS para descobrir se há um caminho ideal entre nó dos players e salvar caminho num vetor
	list <node_tree*> players_wincondition[num_player+1];

	bool all_lost = true;
	bool can_win[num_player];
	for( int i=0; i<num_player ;i++ ){
		can_win[i] = false;
		players_wincondition[i] = my_BFS(board_n,board_m,players[i],all_edges);
		if(players_wincondition[i].size() != 0){
			all_lost = false;
			can_win[i] = true;
		}  
	}

	//Simula o jogo apenas com jogadores que podem ganhar para descobrir o ganhador ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if(all_lost){
		cout << "SEM VENCEDORES" << endl;
		clear_all(all_edges,board_n*board_m); //limpando listas
		return 0;
	}
	// Inicializar valores
	player_info in_game_players[num_player];
	priority_queue <player_info> who_plays;

	for( int k=0 ; k<num_player ;k++ ){
		in_game_players[k].entry_time = players[k][2];
		in_game_players[k].last_jump = 0;
		in_game_players[k].deep_last_jump = 0;

		who_plays.push(in_game_players[k]); 
	}

	//list <node_tree*> players_wincondition[num_player+1] -> contém CAMINHO OTIMO DE UM PLAYER, usar player_info.entry_time para acessar
	// Game simulation
	while(1){
		priority_queue <player_info> next_round;
		while(!who_plays.empty()){
			player_info playing_now;
			playing_now = who_plays.top();
			who_plays.pop();

			if(can_win[playing_now.entry_time]){
				node_tree* play;
				play = players_wincondition[playing_now.entry_time].front(); //Acessa a lista de jogadas do player
				players_wincondition[playing_now.entry_time].pop_front();

				if(players_wincondition[playing_now.entry_time].size() == 0){
					cout << char(playing_now.entry_time+65) << endl;
					cout << play->node_deep << endl;
					
					clear_all(all_edges,board_n*board_m); //limpando listas
					return 0;
				}
				in_game_players[playing_now.entry_time].last_jump = play->jump;
				in_game_players[playing_now.entry_time].deep_last_jump = play->node_deep;

				next_round.push(in_game_players[playing_now.entry_time]);
			}
		}
		who_plays = next_round;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	clear_all(all_edges,board_n*board_m); //limpando listas
	return 0;
};
