

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
    if(PlayerID == 1871945604)
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
    if (GroupID==0)
    {
        all_of_players= levels_tree->getSumInBorder(lowerLevel, higherLevel);
        if(score<=scale && score>1)
        {
            Avltree<int,int>* tree = scale_levels_trees_arr[score];
            num_of_players_with_score = tree->getSumInBorder(lowerLevel, higherLevel);
        }
        else
            num_of_players_with_score = 0;
        if(lowerLevel==0)
        {
            if(score<=scale && score>1)
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
    if(m==27)
    {
        int x=27;
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

