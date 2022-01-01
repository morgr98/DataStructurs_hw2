
#ifndef DATASTRUCTURS_HW2_GROUP_H
#define DATASTRUCTURS_HW2_GROUP_H

#include "avl.h"
#include "HashTables.h"
#include "Player.h"

class Group {
    int group_id;
    int num_of_players;
    Avltree<int,int> levels_tree;
    HashTables<Player> players;

public:
    Group(){};
    Group(int id): group_id(id), num_of_players(0){};
    ~Group()=default;
    Group(Group& group)=default;

    void addPlayer(Player player, int score_player, int level_player);
    int getGroupId();



};


#endif //DATASTRUCTURS_HW2_GROUP_H
