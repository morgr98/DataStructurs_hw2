

#include "GameSystem.h"

StatusType GameSystem::mergeGroups(int GroupID1, int GroupID2)
{
    if (GroupID1<=0 || GroupID2<=0 || GroupID1>k || GroupID2>k)
        return INVALID_INPUT;
  //  if(GroupID1==39&&GroupID2==5)
  //      std::cout<<"here";
    groups->Union(GroupID1, GroupID2);
    return SUCCESS;
}

StatusType GameSystem::addPlayer(int PlayerID, int GroupID, int score) {
   // if(GroupID== 23)
  //  {
  //      std::cout<<"h";
  //  }
    if(PlayerID<=0 || score<=0|| score >scale || GroupID<= 0 || GroupID>k){
        return INVALID_INPUT;
    }
    if(players->member(PlayerID))
    {
        return FAILURE;
    }
    num_of_players++;
    std::shared_ptr<Player> new_player;
    try{
        new_player = std::make_shared<Player>(PlayerID,score,GroupID);
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    players->insert(new_player,PlayerID);
    players_at_zero++;
    score_of_players_at_zero[score]++;
    std::shared_ptr<Group> group = groups->find(GroupID);
    group->addPlayer(0,score);
    return SUCCESS;
}

StatusType GameSystem::removePlayer(int PlayerID) {
    if (PlayerID<=0)
        return INVALID_INPUT;
    if(PlayerID== 1255983752)
    {
        int x=0;
    }
    std::shared_ptr<Player> player_to_remove = players->find(PlayerID);
    if(player_to_remove== nullptr)
    {
        return FAILURE;
    }
    int level = player_to_remove->getLevel();
    int score = player_to_remove->getScore();
    std::shared_ptr<Group> group = groups->find(player_to_remove->getGroupId());
    group->removePlayer(level,score);
    if (level==0)
    {
        players_at_zero--;
        score_of_players_at_zero[score]--;
    }

    else
    {
        levels_tree->remove(level);
        scale_levels_trees_arr[score]->remove(level);
    }
    num_of_players--;
    return SUCCESS;
}

StatusType GameSystem::increasePlayerIDLevel(int PlayerID, int LevelIncrease) {
    if(PlayerID<= 0 || LevelIncrease<=0)
    {
        return  INVALID_INPUT;
    }
    if(PlayerID == 621292714)
        int x=0;
    if(!players->member(PlayerID))
    {
        return FAILURE;
    }
    std::shared_ptr<Player> player= players->find(PlayerID);
    int old_level = player->getLevel();
    int score = player->getScore();
    player->increaseLevel(LevelIncrease);
    std::shared_ptr<Group> group= groups->find(player->getGroupId());
    group->increasePlayerLevel(old_level,player->getLevel(),player->getScore());
    if(old_level!=0)
    {
        scale_levels_trees_arr[player->getScore()]->remove(old_level);
        levels_tree->remove(old_level);
    }
    else{
        players_at_zero--;
        score_of_players_at_zero[score]--;
    }
    scale_levels_trees_arr[player->getScore()]->insert(1,player->getLevel());
    levels_tree->insert(1,player->getLevel());
    return SUCCESS;
}

StatusType GameSystem::changePlayerIDScore(int PlayerID, int NewScore) {
   // if(PlayerID==1773324543)
  //  {
   //     std::cout<<"h";
   // }
    if(NewScore<=0 || NewScore > scale || PlayerID<=0)
    {
        return INVALID_INPUT;
    }
    if(!players->member(PlayerID))
    {
        return FAILURE;
    }
    std::shared_ptr<Player> player= players->find(PlayerID);
    std::shared_ptr<Group> group= groups->find(player->getGroupId());
    int old_score= player->getScore();
    int level = player->getLevel();
    group->changePlayerScore(old_score, NewScore, level);
    player->updateScore(NewScore);
    if(level==0)
    {
        score_of_players_at_zero[old_score]--;
        score_of_players_at_zero[NewScore]++;
    }
    else
    {
        scale_levels_trees_arr[old_score]->remove(player->getLevel());
        scale_levels_trees_arr[NewScore]->insert(1,player->getLevel());
    }
    return SUCCESS;
}

StatusType GameSystem::getPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel,
                                                            double *players)
{
    if(GroupID<0||GroupID>k||players==nullptr)
        return INVALID_INPUT;
    int num_of_players_with_score=0;
    int all_of_players=0;
    if(higherLevel<lowerLevel)
    {
        return FAILURE;
    }
    if (GroupID==0)
    {
        all_of_players= levels_tree->getSumInBorder(lowerLevel, higherLevel);
        if(score<=scale && score>=1)
        {
            Avltree<int,int>* tree = scale_levels_trees_arr[score];
            num_of_players_with_score = tree->getSumInBorder(lowerLevel, higherLevel);
        }
        else
            num_of_players_with_score = 0;
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
    std::shared_ptr<Group> group = groups->find(GroupID);
    return group->getPercentOfPlayersWithScoreInBounds(score, lowerLevel, higherLevel, players);
}

StatusType GameSystem::averageHighestPlayerLevelByGroup(int GroupID, int m, double *avgLevel) {
    if(GroupID>k || GroupID <0 || m<=0)
    {
        return INVALID_INPUT;
    }
    if(GroupID!=0)
    {
        std::shared_ptr<Group> group = groups->find(GroupID);
        return  group->averageHighestPlayerLevelByGroup(m,avgLevel);
    }
    if(m>num_of_players)
    {
        return FAILURE;
    }
    int num=m;
    if(m>num_of_players - players_at_zero)
    {
        num=num_of_players- players_at_zero;
    }
    double sum= levels_tree->getHighestSumLevel(num);
    *avgLevel= (double (sum/m));
    return SUCCESS;
}

StatusType GameSystem::getPlayersBound(int GroupID, int score, int m, int * LowerBoundPlayers,
                           int * HigherBoundPlayers)
{
    if (GroupID<0||GroupID>k||m<0||score<=0||score>scale)
        return INVALID_INPUT;
    if (m==0)
    {
        *LowerBoundPlayers = 0;
        *HigherBoundPlayers = 0;
        return SUCCESS;
    }
    if(score==6&&GroupID==0&&m==9)
        int x =0;
    if (GroupID==0)
    {
        if(m>num_of_players)
            return FAILURE;
        int lowest_level_to_check = levels_tree->findLowestLevelOutOfM(m);
        int num_of_players_inbound_at_score = 0;
        int num_of_players_at_min_at_score = 0;
        int players_above_min_at_score = 0;
        int total_of_players_at_min = 0;
        int total_of_players_at_range = 0;
        if(lowest_level_to_check == 0)
        {
            num_of_players_inbound_at_score = scale_levels_trees_arr[score]->getSize() + score_of_players_at_zero[score];
            num_of_players_at_min_at_score = score_of_players_at_zero[score];
            total_of_players_at_min = players_at_zero;
            total_of_players_at_range = num_of_players;
        }
        else
        {
            num_of_players_inbound_at_score = scale_levels_trees_arr[score]->countDataAboveKey(lowest_level_to_check);
            if(scale_levels_trees_arr[score]->findKey(lowest_level_to_check)!=nullptr)
                num_of_players_at_min_at_score = scale_levels_trees_arr[score]->findKey(lowest_level_to_check)->getData();
            total_of_players_at_min = levels_tree->findKey(lowest_level_to_check)->getData();
            total_of_players_at_range = levels_tree->countDataAboveKey(lowest_level_to_check);
        }
        players_above_min_at_score = num_of_players_inbound_at_score - num_of_players_at_min_at_score;
        int players_above_min = total_of_players_at_range - total_of_players_at_min;
        m = m-players_above_min;
        *LowerBoundPlayers = m - (total_of_players_at_min - num_of_players_at_min_at_score);
        if(*LowerBoundPlayers<0)
            *LowerBoundPlayers=0;
        *LowerBoundPlayers+=players_above_min_at_score;
        *HigherBoundPlayers = players_above_min_at_score + num_of_players_at_min_at_score;
        return SUCCESS;
    }
    std::shared_ptr<Group> group = groups->find(GroupID);
    if(GroupID==41)
        int x=0;
    return group->getPlayersBound(score, m, LowerBoundPlayers, HigherBoundPlayers);

}


/*
int* num_of_players_inbound_by_scale = new int[scale+1];
int* num_of_players_at_min_by_scale = new int[scale+1];

for(int i=1;i<scale+1;i++)
{
    if(lowest_level_to_check==0)
    {
        num_of_players_inbound_by_scale[i] = scale_levels_trees_arr[i]->getSize();
    }
    num_of_players_inbound_by_scale[i] = scale_levels_trees_arr[i]->countDataAboveKey(lowest_level_to_check);
    if(scale_levels_trees_arr[i]->findKey(lowest_level_to_check)!=nullptr)
        num_of_players_at_min_by_scale[i] = scale_levels_trees_arr[i]->findKey(lowest_level_to_check)->getData();
    else
        num_of_players_at_min_by_scale[i]=0;
}*/