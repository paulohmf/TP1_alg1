#include <list> 
#include <iterator> 
#include <queue>

struct edge{
	int nodeB_n,nodeB_m;
	int jump;
};

struct node_tree{
	int node_deep;
	int jump;
	int parent[2];
	int value[2];
};


struct player_info{
	int entry_time;
	int last_jump;
	int deep_last_jump;

	bool operator<(const player_info &object) const {
       	if(last_jump != object.last_jump){
       		return last_jump > object.last_jump;
       	}
       	return entry_time > object.entry_time;
    }
};
