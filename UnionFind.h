#ifndef DATASTRUCTURS_HW2_UNIONFIND_H
#define DATASTRUCTURS_HW2_UNIONFIND_H

#include "avl.h"

template<class T>
class NodeUF{
    T data;
    int size;
    Avltree<int ,int> levels_tree;
public:
    NodeUF(T data): data(data),size(1){};

    NodeUF():data(data), size(0){};
    NodeUF(NodeUF &node) = default;

    ~NodeUF() = default;

    void setSize(int size1){
        size+=size1;
    }

    int getSize()
    {
        return size;
    }

    T getData(){
        return data;
    }

};

template<class T>
class UnionFind {
public:
    int num_elements;
    int *parents;
    int *size;
    NodeUF<T>** groups ;
    UnionFind()=default;
     UnionFind(int num): num_elements(num){
        parents= new int[num+1];
        size= new int[num+1];
        groups= new NodeUF<T>*[num+1];
        for(int i=1;i<num+1;i++)
        {
            parents[i]=-1;
            size[i]=0;
        }
    }

    UnionFind(UnionFind& UF)= default;
    ~UnionFind()=default;

    void makeSet(T data, int id);
    T find(int id);
    void Union(int id1, int id2);
};

template<class T>
void UnionFind<T>::makeSet(T data, int id) {
    groups[id]=new NodeUF<T>(data);
    size[id]=1;
}


template<class T>
T UnionFind<T>::find(int id) {
    int parent_num=id, cur_num=id;
    while (parents[parent_num]!=-1)
    {
        parent_num=parents[parent_num];
    }

    while (parents[cur_num]!=-1)
    {
        id=parents[cur_num];
        parents[cur_num]=parent_num;
        cur_num=id;
    }
    return groups[parent_num]->getData();
}

template<class T>
void UnionFind<T>::Union(int id1, int id2) {
    int size1= size[id1], size2=size[id2];
    if(size1>size2)
    {
        parents[id2]=id1;
        size[id1]+=size[id2];
       // groups[id1]->getData().Merge(groups[id2]->getData());
    }
    else
    {
        parents[id1]=id2;
        size[id2]+=size[id1];
       // groups[id2]->getData().Merge(groups[id1]->getData());
    }
}

#endif //DATASTRUCTURS_HW2_UNIONFIND_H
