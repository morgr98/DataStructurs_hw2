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
    return group_levels_tree;
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
    if(other_group->getGroupId()==1)
    {
        std::cout<<"here";
    }
    group_levels_tree->Merge(other_group->getPlayersTree());
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
        group_levels_tree->insert(1, level_player);
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
        group_levels_tree->remove(level_player);
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
        if (old_level == 1 && new_level == 5)
            int x =0;
        group_levels_tree->remove(old_level);
        scale_levels_trees_arr[score]->remove(old_level);
    }
    if(group_levels_tree->size!=0)
        int x =0;
    group_levels_tree->insert(1,new_level);
    scale_levels_trees_arr[score]->insert(1,new_level);
}
StatusType Group::changePlayerScore(int old_score, int new_score, int level)
{
    if(level==0)
    {
        score_of_players_at_zero[old_score]--;
        score_of_players_at_zero[new_score]++;
    }
    else
    {
        scale_levels_trees_arr[old_score]->remove(level);
        scale_levels_trees_arr[new_score]->insert(1,level);
    }
    return SUCCESS;
}
StatusType Group::getPercentOfPlayersWithScoreInBounds(int score, int lowerLevel, int higherLevel, double *players)
{
    int num_of_players_with_score=0;
    int all_of_players=0;

    if(score<scale && score>1)
    {
        Avltree<int,int>* tree = scale_levels_trees_arr[score];
        num_of_players_with_score = tree->getSumInBorder(lowerLevel, higherLevel);
    }
    else
        num_of_players_with_score = 0;
    all_of_players= group_levels_tree->getSumInBorder(lowerLevel, higherLevel);
    if(all_of_players==0)
        return FAILURE;
    if(lowerLevel==0)
    {
        if(score<scale && score>1)
        {
            num_of_players_with_score+=score_of_players_at_zero[score];
        }
        all_of_players+=players_at_zero;
    }
    *players = (double(num_of_players_with_score)/all_of_players)*100;
    return SUCCESS;
}

StatusType Group::averageHighestPlayerLevelByGroup(int m, double *avgLevel) {
    if(m>num_of_players){
        return  FAILURE;
    }
    int num=m;
    if(m>num_of_players - players_at_zero)
    {
        num=num_of_players- players_at_zero;
    }
    double sum= group_levels_tree->getHighestSumLevel(num);
    *avgLevel= (double (sum/m));
    return SUCCESS;
}
