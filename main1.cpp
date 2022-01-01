
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





    return 0;
};