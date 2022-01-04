//
// Created by morgr on 31/12/2021.
//

#include "Group.h"
#include <iostream>

int Group::getGroupId() {
    return group_id;
}
int Group::getNumPlayers()
{
    return this->num_of_players;
}
int Group::getPlayersAtZero()
{
    return players_at_zero;
}
Avltree<int,int>* Group::getPlayersTree()
{
    return levels_tree;
}
void Group::Merge(std::shared_ptr<Group> other_group)
{
    num_of_players = num_of_players+other_group->getNumPlayers();
    players_at_zero = players_at_zero + other_group->getPlayersAtZero();
    for(int i=0;i<scale+1;i++)
    {
        score_of_players_at_zero[i] += other_group->score_of_players_at_zero[i];
        scale_levels_trees_arr[i]->Merge(other_group->scale_levels_trees_arr[i]);
    }
    levels_tree->Merge(other_group->getPlayersTree());
}
void Group::addPlayer(int level_player, int score)
{
    num_of_players++;
    if (level_player == 0)
    {
        players_at_zero++;
        score_of_players_at_zero[score]++;
    }
    else
    {
        levels_tree->insert(1, level_player);
        scale_levels_trees_arr[score]->insert(1,level_player);
    }
}
void Group::removePlayer(int level_player, int score)
{
    num_of_players--;
    if (level_player == 0)
    {
        players_at_zero--;
        score_of_players_at_zero[score]--;
    }

    else{
        levels_tree->remove(level_player);
        scale_levels_trees_arr[score]->remove(level_player);
    }

}

void Group::increasePlayerLevel(int old_level, int new_level, int score) {
    if(old_level==0)
    {
        players_at_zero--;
        score_of_players_at_zero[score]--;
    }
    else{
        levels_tree->remove(old_level);
        scale_levels_trees_arr[score]->remove(old_level);
    }
    levels_tree->insert(1,new_level);
    scale_levels_trees_arr[score]->insert(1,new_level);
}
StatusType Group::getPercentOfPlayersWithScoreInBounds(int score, int lowerLevel, int higherLevel, double *players)
{
    int num_of_players_with_score=0;
    int all_of_players=0;
    Avltree<int,int>* tree = scale_levels_trees_arr[score];
    num_of_players_with_score = tree->getSumInBorder(lowerLevel, higherLevel);
    all_of_players= levels_tree->getSumInBorder(lowerLevel, higherLevel);
    if(all_of_players==0)
        return FAILURE;
    if(lowerLevel==0)
    {
        num_of_players_with_score+=score_of_players_at_zero[score];
        all_of_players+=players_at_zero;
    }
    *players = (double(num_of_players_with_score)/all_of_players)*100;
    return SUCCESS;
}
