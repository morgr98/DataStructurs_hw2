

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
    num_of_players++;
    Player* new_player;
    try{
        new_player = new Player(PlayerID,score,GroupID);
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    players.insert(new_player,PlayerID);
    players_at_zero++;
    Group* group = groups.find(GroupID);
    group->addPlayer(0,score);
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
    group->removePlayer(level,player_to_remove->getScore());
    if (level==0)
        players_at_zero--;
    else
    {
        levels_tree.remove(level);
        scale_levels_trees_arr[score].remove(level);
    }
    return SUCCESS;
}

StatusType GameSystem::increasePlayerIDLevel(int PlayerID, int LevelIncrease) {
    if(PlayerID<= 0 || LevelIncrease<=0)
    {
        return  INVALID_INPUT;
    }
    if(!players.member(PlayerID))
    {
        return FAILURE;
    }
    Player * player= players.find(PlayerID);
    int old_level = player->getLevel();
    player->increaseLevel(LevelIncrease);
    Group* group= groups.find(player->getGroupId());
    group->increasePlayerLevel(old_level,player->getLevel(),player->getScore());

    if(old_level!=0)
    {
        scale_levels_trees_arr[player->getScore()].remove(old_level);
        levels_tree.remove(old_level);
    }
    else{
        players_at_zero--;
    }
    scale_levels_trees_arr[player->getScore()].insert(1,player->getLevel());
    levels_tree.insert(1,player->getLevel());
    return SUCCESS;
}

StatusType GameSystem::changePlayerIDScore(int PlayerID, int NewScore) {
    if(NewScore<=0 || NewScore > scale || PlayerID<=0)
    {
        return INVALID_INPUT;
    }
    if(!players.member(PlayerID))
    {
        return FAILURE;
    }
    Player * player= players.find(PlayerID);
    //Group* group= groups.find(player->getGroupId());
    int old_score= player->getScore();
    player->updateScore(NewScore);
    scale_levels_trees_arr[old_score].remove(player->getLevel());
    scale_levels_trees_arr[NewScore].insert(1,player->getLevel());
    return  SUCCESS;
}

void GameSystem::destroy() {

  //  players.destroy();
    //levels_tree.destroy();
  //  groups.destroy();

    for (int i=0;i<scale+1;i++)
    {
        scale_levels_trees_arr[i].destroy();
    }
    delete [] scale_levels_trees_arr;
}
