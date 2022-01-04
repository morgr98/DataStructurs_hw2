
#ifndef DATASTRUCTURS_HW2_GROUP_H
#define DATASTRUCTURS_HW2_GROUP_H

#include "avl.h"
#include "HashTables.h"
#include "Player.h"

class Group {
    int group_id;
    int num_of_players;
    Avltree<int,int>* levels_tree;
    Avltree<int,int>** scale_levels_trees_arr;
    //HashTables<Player> players;
    int players_at_zero;
    int scale;

public:
    Group(){};
    Group(int id, int scale): group_id(id), num_of_players(0), players_at_zero(0), scale(scale){
        levels_tree = new Avltree<int,int>;
        scale_levels_trees_arr = new Avltree<int,int>*[scale+1];
        for (int i=0;i<scale+1;i++)
        {
            scale_levels_trees_arr[i] = new Avltree<int,int>();
        }
    };
    ~Group(){
        delete levels_tree;
        for (int i=0;i<scale+1;i++)
        {
            delete scale_levels_trees_arr[i];
        }
        delete[] scale_levels_trees_arr;

    };
    Group(Group const& group)=default;

    int getGroupId();
    int getNumPlayers();
    int getPlayersAtZero();
    Avltree<int,int>* getPlayersTree();
    void addPlayer(int level_player, int score);
    void removePlayer(int level_player, int score);
    void Merge(std::shared_ptr<Group> other_group);
    void increasePlayerLevel(int old_level, int new_level, int score);
};


#endif //DATASTRUCTURS_HW2_GROUP_H
