//
// Created by morgr on 31/12/2021.
//

#include "Group.h"
#include <iostream>
static int min(int a, int b);
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
        group_levels_tree->remove(old_level);
        scale_levels_trees_arr[score]->remove(old_level);
    }
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

    if(score<=scale && score>=1)
    {
        Avltree<int,int>* tree = scale_levels_trees_arr[score];
        num_of_players_with_score = tree->getSumInBorder(lowerLevel, higherLevel);
    }
    else
        num_of_players_with_score = 0;
    all_of_players= group_levels_tree->getSumInBorder(lowerLevel, higherLevel);
    if(lowerLevel==0)
    {
        if(score<=scale && score>=1)
        {
            num_of_players_with_score+=score_of_players_at_zero[score];
        }
        all_of_players+=players_at_zero;
    }
    if(all_of_players==0)
        return FAILURE;
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

static int min(int a, int b)
{
    return a>b ? b :a;
}

StatusType Group::getPlayersBound(int score, int m, int * LowerBoundPlayers,
                                       int * HigherBoundPlayers)
{
    if(m>num_of_players)
        return FAILURE;
    int lowest_level_to_check = group_levels_tree->findLowestLevelOutOfM(m);
    int num_of_players_inbound_at_score = 0;
    int num_of_players_at_min_at_score = 0;
    int players_above_min_at_score = 0;
    int total_of_players_at_min = 0;
    int total_of_players_at_range = 0;
    if(lowest_level_to_check == 0)
    {
        if(scale_levels_trees_arr[score]->getRoot() != nullptr)
            num_of_players_inbound_at_score = scale_levels_trees_arr[score]->getRoot()->getSum() + score_of_players_at_zero[score];
        else
            num_of_players_inbound_at_score=score_of_players_at_zero[score];
        num_of_players_at_min_at_score = score_of_players_at_zero[score];
        total_of_players_at_min = players_at_zero;
        total_of_players_at_range = num_of_players;
    }
    else
    {
        num_of_players_inbound_at_score = scale_levels_trees_arr[score]->countDataAboveKey(lowest_level_to_check);
        if(scale_levels_trees_arr[score]->findKey(lowest_level_to_check)!=nullptr)
            num_of_players_at_min_at_score = scale_levels_trees_arr[score]->findKey(lowest_level_to_check)->getData();
        total_of_players_at_min = group_levels_tree->findKey(lowest_level_to_check)->getData();
        total_of_players_at_range = group_levels_tree->countDataAboveKey(lowest_level_to_check);
    }
    players_above_min_at_score = num_of_players_inbound_at_score - num_of_players_at_min_at_score;
    int players_above_min = total_of_players_at_range - total_of_players_at_min;
    m = m-players_above_min;
    *LowerBoundPlayers = m - (total_of_players_at_min - num_of_players_at_min_at_score);
    if(*LowerBoundPlayers<0)
        *LowerBoundPlayers=0;
    *LowerBoundPlayers+=players_above_min_at_score;
    *HigherBoundPlayers = players_above_min_at_score + min(m,num_of_players_at_min_at_score);
    return SUCCESS;
}