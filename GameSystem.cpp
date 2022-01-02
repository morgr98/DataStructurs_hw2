

#include "GameSystem.h"

StatusType GameSystem::addPlayer(int PlayerID, int GroupID, int score) {
    if(PlayerID<=0 || score<=0|| score >scale || GroupID<= 0 || GroupID>k){
        return INVALID_INPUT;
    }
    if(players.member(PlayerID))
    {
        return FAILURE;
    }
    num_of_players++;
    Player new_player(PlayerID,score,GroupID);
    players.insert(new_player,PlayerID);
    players_at_zero++;
    //Group* group = groups.find(GroupID);



    return  SUCCESS;
}
