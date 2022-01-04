
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "UnionFind.h"
#include "HashTables.h"
#include "GameSystem.h"
#include "library2.h"
using namespace std;

int main(int argc, const char**argv){
/*
    UnionFind<int> uf(5);
    uf.makeSet(1,1);
    uf.makeSet(2,2);
    uf.makeSet(3,3);
    uf.Union(1,2);
   // cout<<uf.find(1)<<endl;
*/
/*
    HashTable<int> hs(2);
    hs.insert(1,1);
    hs.insert(2,2);
    hs.insert(1,11);
    hs.insert(1,12);
    hs.insert(1,3);
    hs.insert(1,13);
    hs.remove(13);
    hs.remove(3);
    hs.remove(12);
    cout<<hs.member(1)<<endl;
    cout<<hs.member(11)<<endl;
    cout<<hs.member(12)<<endl;
    cout<<hs.member(13)<<endl;
    cout<<hs.member(15)<<endl;
    cout<<"!!!"<<endl;
    GameSystem gm(5,100);
    for (int i = 1; i < 5; ++i) {

        cout<<gm.getA().groups[i]->getData().getGroupId()<<endl;
    }
     */
/*
    Avltree<int, int> tree;
    tree.insert(1,1);
    tree.insert(2,2);
    tree.insert(3,3);
    tree.insert(4,4);
    tree.insert(5,5);
    tree.insert(6,6);
    tree.insert(7,7);
    tree.insert(8,8);
    tree.insert(9,9);
    tree.insert(11,11);
    tree.insert(15,15);
    tree.insert(10,10);
    tree.insert(14,14);
    tree.insert(24, 24);
    tree.insert(13,13);
    tree.insert(20,20);
    tree.insert(29,29);
    tree.insert(19,19);
    tree.insert(18,18);
    tree.insert(12,12);
    tree.insert(30,30);
    tree.insert(31,31);

*/
/*
    Avltree<int ,int > tree1;
    Avltree<int, int> tree2;
    tree1.insert(1,1);
    tree2.insert(2,2);
    tree1.insert(3,3);
    tree2.insert(4,4);
    tree1.insert(5,5);
    tree2.insert(6,6);
    tree1.insert(7,7);
    tree2.insert(8,8);
    tree1.insert(9,9);

    tree1.Merge(tree2);

*/
//testing rr roll
/*
    tree.insert(&node_12);
    tree.insert(&node_8);
    tree.insert(&node_15);
    tree.insert(&node_6);
    tree.insert(&node_10);
    tree.insert(&node_14);
    tree.insert(&node_24);
    tree.insert(&node_4);
    tree.insert(&node_11);
    tree.insert(&node_13);
    tree.insert(&node_20);
    tree.insert(&node_29);
    tree.insert(&node_30);
    tree.insert(&node_31);
*/
    //testing left roll
/*
    tree.insert(node_12);
    tree.insert(node_8);
    tree.insert(node_15);
    tree.insert(node_6);
    tree.insert(node_10);
    tree.insert(node_14);
    tree.insert(node_24);
    tree.insert(node_4);
    tree.insert(node_11);
    tree.insert(node_13);
    tree.insert(node_20);
    tree.insert(node_29);
    tree.insert(node_19);
    tree.insert(node_18);
    //testing left right roll

    tree.insert(node_15);
    tree.insert(node_10);
    tree.insert(node_20);
    tree.insert(node_19);
    tree.insert(node_24);
    tree.insert(node_6);
    tree.insert(node_13);
    tree.insert(node_12);
    tree.insert(node_14);
    tree.insert(node_4);
    tree.insert(node_8);
    tree.insert(node_11);
*/
//testing rl
/*
    int arr[12];
    tree.inorder(tree.getRoot(), arr, 0);
    for (int i = 0; i < 12; i++) {
        cout << arr[i] << endl;
    }
    tree.remove(&node_1);
    tree.inorder(tree.getRoot(), arr, 0);
    cout << "second loop" << endl;
    for (int i = 0; i < 11; i++) {
        cout << arr[i] << endl;
    }
    */

GameSystem game(10, 5);
/*
game.addPlayer(1,1,1);
game.addPlayer(2,1,1);
game.addPlayer(3,3,2);
game.addPlayer(1,1,1);
game.addPlayer(4,2,2);
game.addPlayer(5,2,1);
game.mergeGroups(1,2);
game.increasePlayerIDLevel(1,1);
game.increasePlayerIDLevel(2,2);
game.increasePlayerIDLevel(5,1);
game.removePlayer(5);
 */
return 0;
};