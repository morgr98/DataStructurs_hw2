
#ifndef DATASTRUCTURS_HW2_GAMESYSTEM_H
#define DATASTRUCTURS_HW2_GAMESYSTEM_H
#include "Group.h"
#include "Player.h"
#include "avl.h"
#include "HashTables.h"
#include "library2.h"
#include "UnionFind.h"

class GameSystem {
    UnionFind<Group> groups;
    Group* data_groups;
    HashTables<Player> players;
    Avltree<int,int> levels_tree;
    int k;
    int scale;
    int num_of_player;
public:
    GameSystem(int k, int scale): k(k), num_of_player(0), scale(scale){
        groups=UnionFind<Group>(k);
        players=HashTables<Player>(100);
        data_groups= new Group[k+1];
        for (int i = 1; i <= k; ++i) {
            Group group(i);
            groups.makeSet(group,i);
            data_groups[i]=group;
        }
    }
    ~GameSystem()=default;
    GameSystem(GameSystem& gameSystem)=default;

    StatusType addPlayer(int PlayerID, int GroupID, int score);

    UnionFind<Group> getA()
    {
        return groups;
    }


};


#endif //DATASTRUCTURS_HW2_GAMESYSTEM_H
