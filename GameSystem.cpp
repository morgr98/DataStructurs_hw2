

#include "GameSystem.h"

StatusType GameSystem::mergeGroups(int GroupID1, int GroupID2)
{
    if (GroupID1<=0 || GroupID2<=0 || GroupID1>k || GroupID2>k)
        return INVALID_INPUT;
    groups.Union(GroupID1, GroupID2);
    return SUCCESS;
}

StatusType GameSystem::addPlayer(int PlayerID, int GroupID, int score) {
    if(PlayerID<=0 || score<=0|| score >scale || GroupID<= 0 || GroupID>k){
        return INVALID_INPUT;
    }
    if(players.member(PlayerID))
    {
        return FAILURE;
    }
    num_of_players++;\
    Player* new_player;
    try{
        new_player = new Player(PlayerID,score,GroupID);
    }
    catch(std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    players.insert(new_player,PlayerID);
    players_at_zero++;
    Group* group = groups.find(GroupID);
    group->addPlayer(0);
    return SUCCESS;
}

StatusType GameSystem::removePlayer(int PlayerID) {
    if (PlayerID<=0)
        return INVALID_INPUT;
    Player* player_to_remove = players.find(PlayerID);
    int level = player_to_remove->getLevel();
    int score = player_to_remove->getScore();
    if(player_to_remove== nullptr)
    {
        return FAILURE;
    }
    Group* group = groups.find(player_to_remove->getGroupId());
    group->removePlayer(level);
    if (level==0)
        players_at_zero--;
    else
    {
        levels_tree.remove(PlayerID);
        scale_levels_trees_arr[score].remove(level);
    }
    return SUCCESS;



}
