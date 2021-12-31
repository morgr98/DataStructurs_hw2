
#ifndef DATASTRUCTURS_HW2_HASHTABLES_H
#define DATASTRUCTURS_HW2_HASHTABLES_H

template<class T>
class NodeHT{
    T data;
    int key;
    NodeHT<T>* pre;
    NodeHT<T>* next;
    NodeHT(T data, int key):data(data),key(key), pre(nullptr), next(nullptr){};
    ~NodeHT()=default;
    NodeHT(NodeHT<T>& node)=default;

    T getData()
    {
        return data;
    }
    int getKey()
    {
        return key;
    }
    NodeHT<T> getNext()
    {
        return next;
    }

    NodeHT<T> getpre()
    {
        return pre;
    }

    void setNext(NodeHT<T> nodeHt)
    {
        next=nodeHt;
    }

    void setPre(NodeHT<T> nodeHt)
    {
        pre=nodeHt;
    }

};


template<class T>
class HashTables {
    int m;
    NodeHT<T>* chain;

    HashTables(int m): m(m){
        chain= new NodeHT<T>[m];
    }
    ~HashTables()=default;
    HashTables(HashTables<T>* hashTables)=default;

    bool member(int key);
    void insert(T data, int key);
    void delete(int key);
};

template<class T>
void HashTables<T>::insert(T data, int key) {
    {
        int h=key%m;
    }
}

#endif //DATASTRUCTURS_HW2_HASHTABLES_H
