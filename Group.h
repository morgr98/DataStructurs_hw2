
#ifndef DATASTRUCTURS_HW2_GROUP_H
#define DATASTRUCTURS_HW2_GROUP_H

#include "avl.h"
#include "HashTables.h"
#include "Player.h"

class Group {
    int group_id;
    int num_of_players;
    Avltree<int,int> levels_tree;
    //HashTables<Player> players;
    int players_at_zero;

public:
    Group(){};
    Group(int id): group_id(id), num_of_players(0), players_at_zero(0){};
    ~Group()=default;
    Group( Group& group)=default;

    int getNumPlayers();
    int getPlayersAtZero();
    Avltree<int,int>* getPlayersTree();
    void addPlayer(Player player, int score_player, int level_player);
    int getGroupId();
    void Merge(Group& other_group);
};


#endif //DATASTRUCTURS_HW2_GROUP_H
