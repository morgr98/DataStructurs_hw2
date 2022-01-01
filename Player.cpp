
#include "Player.h"

int Player::getGroupId() {
    return group_id;
}

int Player::getId() {
    return player_id;
}

int Player::getLevel() {
    return level;
}

int Player::getScore() {
    return score;
}

void Player::increaseLevel(int add_level) {
    level+=add_level;
}

void Player::updateGroup(int group_id1) {
    group_id=group_id1;
}

void Player::updateScore(int new_score) {
    score=new_score;
}