//
// Created by morgr on 31/12/2021.
//

#include "Group.h"

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
    return &levels_tree;
}
void Group::Merge(Group* other_group)
{
    num_of_players = num_of_players+other_group->getNumPlayers();
    players_at_zero = players_at_zero + other_group->getPlayersAtZero();
    levels_tree.Merge(other_group->levels_tree);
}
void Group::addPlayer(int level_player)
{
    if (level_player == 0)
        players_at_zero++;
    else
    {
        levels_tree.insert(1, level_player);
    }
}
void Group::removePlayer(int level_player)
{
    if (level_player == 0)
        players_at_zero--;
    else
        levels_tree.remove(level_player);
}

