#ifndef DATASTRUCTURS_HW2_PLAYER_H
#define DATASTRUCTURS_HW2_PLAYER_H


class Player {
    int player_id;
    int score;
    int level;
    int group_id;
public:
    Player(int id, int score, int group_id): player_id(id), score(score), level(0), group_id(group_id){};
    ~Player()=default;
    Player(Player& player)=default;

    int getScore();
    int getLevel();
    int getId();
    int getGroupId();
    void updateScore(int new_score);
    void increaseLevel(int add_level);
    void updateGroup(int group_id);
};


#endif //DATASTRUCTURS_HW2_PLAYER_H
