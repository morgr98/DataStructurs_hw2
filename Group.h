
#ifndef DATASTRUCTURS_HW2_GROUP_H
#define DATASTRUCTURS_HW2_GROUP_H

#include "avl.h"


class Group {
    int group_id;
    int num_of_players;
    Avltree<int,int> levels_tree;
};


#endif //DATASTRUCTURS_HW2_GROUP_H
