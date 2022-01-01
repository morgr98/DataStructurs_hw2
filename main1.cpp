
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "UnionFind.h"
#include "HashTables.h"
using namespace std;

int main(int argc, const char**argv){
    UnionFind<int> uf(5);
    uf.makeSet(1,1);
    uf.makeSet(2,2);
    uf.makeSet(3,3);
    uf.Union(1,2);
    cout<<uf.find(1)<<endl;

    HashTables<int> hs(10);
    hs.insert(1,1);
    hs.insert(2,2);
    hs.insert(1,11);
    hs.insert(1,12);
    hs.insert(1,3);
    hs.insert(1,13);
    hs.remove(13);
    cout<<hs.member(1)<<endl;
    cout<<hs.member(11)<<endl;
    cout<<hs.member(12)<<endl;
    cout<<hs.member(13)<<endl;
    cout<<hs.member(15)<<endl;
/*
    Node<int, int> node_8(8,8);
    Node<int, int> node_15(15,15);
    Node<int, int> node_6(6,6);
    Node<int, int> node_10(10,10);
    Node<int, int> node_14(14,14);
    Node<int, int> node_24(24, 24);
    Node<int, int> node_4(4,4);
    Node<int, int> node_11(11,11);
    Node<int, int> node_13(13,13);
    Node<int, int> node_20(20,20);
    Node<int, int> node_29(29,29);
    Node<int, int> node_19(19,19);
    Node<int, int> node_18(18,18);
    */
//testing rr roll
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
    tree.insert(node_30);
    tree.insert(node_31);
    //testing left roll
    */
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
    */
/*
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

//testing rl
    tree.insert(node_5);
    tree.insert(node_2);
    tree.insert(node_8);
    tree.insert(node_1);
    tree.insert(node_4);
    tree.insert(node_10);
    tree.insert(node_6);
    tree.insert(node_3);
    tree.insert(node_7);
    tree.insert(node_9);
    tree.insert(node_12);
    tree.insert(node_11);

    int arr[12];
    tree.inorder(tree.getRoot(), arr, 0);
    for (int i = 0; i < 12; i++) {
        cout << arr[i] << endl;
    }
    tree.remove(node_1);
    tree.inorder(tree.getRoot(), arr, 0);
    cout << "second loop" << endl;
    for (int i = 0; i < 11; i++) {
        cout << arr[i] << endl;
    }



    return 0;
    */
};