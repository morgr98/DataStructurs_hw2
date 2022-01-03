
#ifndef DATASTRUCTURS_HW2_GROUP_H
#define DATASTRUCTURS_HW2_GROUP_H

#include "avl.h"
#include "HashTables.h"
#include "Player.h"

class Group {
    int group_id;
    int num_of_players;
    Avltree<int,int> levels_tree;
    Avltree<int,int>* scale_levels_trees_arr;
    //HashTables<Player> players;
    int players_at_zero;

public:
    Group(){};
    Group(int id, int scale): group_id(id), num_of_players(0), players_at_zero(0){
        scale_levels_trees_arr = new Avltree<int,int>[scale];
    };
    ~Group()=default;
    Group( Group& group)=default;

    int getGroupId();
    int getNumPlayers();
    int getPlayersAtZero();
    Avltree<int,int>* getPlayersTree();
    void addPlayer(int level_player, int score);
    void removePlayer(int level_player, int score);
    void Merge(Group* other_group);
    void increasePlayerLevel(int old_level, int new_level, int score);
};


#endif //DATASTRUCTURS_HW2_GROUP_H
