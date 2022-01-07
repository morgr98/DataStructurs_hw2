#ifndef DATASTRUCTURS_HW2_UNIONFIND_H
#define DATASTRUCTURS_HW2_UNIONFIND_H

#include "avl.h"

template<class T>
class NodeUF{
    T data;
    int size;
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
    T* getDataPtr(){
        return &data;
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
        for(int i=0;i<num+1;i++)
        {
            parents[i]=-1;
            size[i]=0;
            groups[i]=nullptr;
        }
    }

    UnionFind(UnionFind& UF)= default;
    ~UnionFind(){this->destroy();};
    void newUpdate(int num);
    void destroy();
    void makeSet(T data, int id);
    T find(int id);
    void Union(int id1, int id2);
};

template<class T>
void UnionFind<T>::destroy() {
    delete[] parents;
    delete[] size;
    for (int i=0;i<num_elements+1;i++)
    {
        if(groups[i]!= nullptr){
            delete groups[i];
        }
    }
    delete[] groups;
}
template<class T>
void UnionFind<T>::newUpdate(int num) {
    num_elements= num;
    parents= new int[num+1];
    size= new int[num+1];
    groups= new NodeUF<T>*[num+1];
    for(int i=0;i<num+1;i++)
    {
        parents[i]=-1;
        size[i]=0;
        groups[i]=nullptr;
    }
}


template<class T>
void UnionFind<T>::makeSet(T data, int id) {
    groups[id]=new NodeUF<T>(data);
    size[id]=1;
}

template<class T>
T UnionFind<T>::find(int id) {
    //what if id doesnt exist?
    if (id>num_elements)
        return nullptr;
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
    //should check first their parent, no? gilad added
    id1 = find(id1)->getGroupId();
    id2 = find(id2)->getGroupId();
    if (id1 == id2)
        return;
    int size1= size[id1], size2=size[id2];
    if(size1>size2)
    {
        parents[id2]=id1;
        size[id1]+=size[id2];
        groups[id1]->getData()->Merge(groups[id2]->getData());
    }
    else
    {
        parents[id1]=id2;
        size[id2]+=size[id1];
        groups[id2]->getData()->Merge(groups[id1]->getData());
    }
}

#endif //DATASTRUCTURS_HW2_UNIONFIND_H
