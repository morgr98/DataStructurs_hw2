
#ifndef DATASTRUCTURS_HW2_GAMESYSTEM_H
#define DATASTRUCTURS_HW2_GAMESYSTEM_H
#include "Group.h"
#include "Player.h"
#include "avl.h"
#include "HashTables.h"
#include "library2.h"
#include "UnionFind.h"

class GameSystem {
    UnionFind<std::shared_ptr<Group>>* groups;
    //Group* data_groups;
    HashTable<std::shared_ptr<Player>>* players;
    Avltree<int,int>* levels_tree;
    Avltree<int,int>** scale_levels_trees_arr;
    int k;
    int scale;
    int num_of_players;
    int players_at_zero;
public:
    GameSystem(int k, int scale): k(k), scale(scale), num_of_players(0), players_at_zero(0){
        groups = new UnionFind<std::shared_ptr<Group>>(k);
        players= new HashTable<std::shared_ptr<Player>>(100);
        //data_groups= new Group[k+1];
        levels_tree = new Avltree<int,int>;
        scale_levels_trees_arr = new Avltree<int,int>*[scale+1];
        for (int i=0;i<scale+1;i++)
        {
            scale_levels_trees_arr[i] = new Avltree<int,int>();
            Node<int,int>* root = scale_levels_trees_arr[i]->root;
        }
        std::shared_ptr<Group> group;
        for (int i = 1; i <= k; ++i) {
            group = std::make_shared<Group>(i,scale);
            groups->makeSet(std::move(group),i);
            //data_groups[i]=group;
        }
    }
    /*GameSystem(GameSystem& other) = default;
    *{
        //not sure
        k = other.k;
        num_of_players = other.num_of_players;
        scale = other.scale;
        players_at_zero = other.players_at_zero;
        groups = other.groups;
        players = other.players;
        scale_levels_trees_arr=other.scale_levels_trees_arr;
        groups = other.groups;
    }*/
    ~GameSystem(){
        players->destroy();
        levels_tree->destroy();
        groups->destroy();
        for (int i=0;i<scale+1;i++)
        {
            scale_levels_trees_arr[i]->destroy();
        }
        delete[] scale_levels_trees_arr;
    };

    StatusType mergeGroups(int GroupID1, int GroupID2);

    StatusType addPlayer(int PlayerID, int GroupID, int score);

    StatusType removePlayer(int PlayerID);

    StatusType increasePlayerIDLevel(int PlayerID, int LevelIncrease);

    StatusType changePlayerIDScore(int PlayerID, int NewScore);

    StatusType getPercentOfPlayersWithScoreInBounds (int GroupID, int score, int
    lowerLevel, int higherLevel, double * players);

};


#endif //DATASTRUCTURS_HW2_GAMESYSTEM_H
