
#ifndef DATASTRUCTURS_HW2_HASHTABLES_H
#define DATASTRUCTURS_HW2_HASHTABLES_H

template<class T>
class NodeHT{
    T data;
    int key;
    NodeHT<T>* pre;
    NodeHT<T>* next;
public:
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
    NodeHT<T>* getNext()
    {
        return next;
    }

    NodeHT<T>* getpre()
    {
        return pre;
    }

    void setNext(NodeHT<T>* nodeHt)
    {
        next=nodeHt;
    }

    void setPre(NodeHT<T>* nodeHt)
    {
        pre=nodeHt;
    }

};


template<class T>
class HashTables {
    int m;
    NodeHT<T>** chain;
public:
    HashTables(int m): m(m){
        chain = new NodeHT<T>*[m];
        for (int i = 0; i < m; ++i) {
            chain[i]= nullptr;
        }
    }
    ~HashTables()=default;
    HashTables(HashTables<T>& hashTables)=default;

    bool member(int key);
    void insert(T data, int key);
    void remove(int key);
};

template<class T>
bool HashTables<T>::member(int key) {
    {
        int h=key%m;
        NodeHT<T>* nodeHt=chain[h];
        while(nodeHt!= nullptr && nodeHt->getKey()!= key)
        {
            nodeHt=nodeHt->getNext();
        }
        if(nodeHt!= nullptr)
        {
            return true;
        }
        return false;
    }
}

template<class T>
void HashTables<T>::insert(T data, int key) {
    int h=key%m;
    NodeHT<T> *new_node= new NodeHT<T>(data,key);
    NodeHT<T>* nodeHt=chain[h];
    if(nodeHt== nullptr)
    {
        NodeHT<T> *dummy= new NodeHT<T>(data,-1);
        chain[h]=dummy;
        dummy->setNext(new_node);
        new_node->setPre(dummy);
    }
    else
    {
        while(nodeHt->getNext()!= nullptr)
        {
            nodeHt=nodeHt->getNext();
        }
        nodeHt->setNext(new_node);
        new_node->setPre(nodeHt);
    }
}

template<class T>
void HashTables<T>::remove(int key) {
    int h=key%m;
    NodeHT<T>* nodeHt=chain[h];
    NodeHT<T>* nodeHt_pre=nodeHt;
    nodeHt=nodeHt->getNext();
    while (nodeHt->getKey()!= key)
    {
        nodeHt=nodeHt->getNext();
        nodeHt_pre=nodeHt_pre->getNext();
    }
    nodeHt_pre->setNext(nodeHt->getNext());
    if(nodeHt->getNext()!= nullptr)
    {
        nodeHt->getNext()->setPre(nodeHt_pre);
    }
    delete nodeHt;
}

#endif //DATASTRUCTURS_HW2_HASHTABLES_H
