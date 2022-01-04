
#ifndef DATASTRUCTURS_HW2_HashTable_H
#define DATASTRUCTURS_HW2_HashTable_H

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

    NodeHT<T>* getPre()
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

const int DEFAULT_SIZE = 101;
template<class T>
class HashTable {
    int m;
    int arr_size;
    int curr_size;
    double top_threshold;
    double bottom_threshold;
    int min_size;
    NodeHT<T>** chain;
public:
    HashTable():  m(DEFAULT_SIZE-1), arr_size(DEFAULT_SIZE), min_size(DEFAULT_SIZE){};
    HashTable(int arr_size):m(arr_size-1), arr_size(arr_size), min_size(arr_size){
        top_threshold = 1;
        bottom_threshold = 0.5;
        chain = new NodeHT<T>*[arr_size];
        for (int i = 0; i < arr_size; ++i) {
            chain[i]= nullptr;
        }
    }
    ~HashTable()
    {
        this->destroy();
    }
    HashTable(HashTable<T>& hashtable)=default;/*{
        m=hashtable.m;
        arr_size = hashtable.arr_size;
        curr_size=hashtable.curr_size;
        top_threshold=hashtable.top_threshold;
        bottom_threshold=hashtable.bottom_threshold;
        min_size=hashtable.min_size;
        for(int i=0;i<arr_size;i++)
        {
            chain[i] = hashtable.chain[i];
        }
    }*/
    void newUpdate(int arr_size);
    void destroy();
    bool member(int key);
    T find(int key);
    void insert(T data, int key);
    void remove(int key);
    void changeSize(bool increase);
};
template<class T>
void HashTable<T>::destroy()
{
    for (int i=0;i<arr_size;i++)
    {
        NodeHT<T>* dummy_node=chain[i];
        if (dummy_node==nullptr)
            continue;
        NodeHT<T>* iterator = dummy_node->getNext();
        while (iterator!=nullptr)
        {
            NodeHT<T>* node_to_delete = iterator;
            iterator = iterator->getNext();
            delete node_to_delete;
        }
        delete dummy_node;
    }
    delete[] chain;
}

template<class T>
void HashTable<T>::newUpdate(int arr_size1) {
    m=arr_size1-1;
    arr_size=arr_size1;
    min_size=arr_size1;
    curr_size=0;
    top_threshold = 1;
    bottom_threshold = 0.5;
    chain = new NodeHT<T>*[arr_size];
    for (int i = 0; i < arr_size; ++i) {
        chain[i]= nullptr;
    }
}

template<class T>
bool HashTable<T>::member(int key) {
    {
        {
            int h = key % m;
            NodeHT<T> *nodeHt = chain[h];
            while (nodeHt != nullptr && nodeHt->getKey() != key) {
                nodeHt = nodeHt->getNext();
            }
            if (nodeHt != nullptr) {
                return true;
            }
            return false;
        }
    }
}
template<class T>
T HashTable<T>::find(int key) {
    {
        {
            int h = key % m;
            NodeHT<T> *nodeHt = chain[h];
            while (nodeHt != nullptr && nodeHt->getKey() != key) {
                nodeHt = nodeHt->getNext();
            }
            if (nodeHt != nullptr) {
                return nodeHt->getData();
            }
            return nullptr;
        }
    }
}
template<class T>
void HashTable<T>::insert(T data, int key) {
    int h=key%m;
    NodeHT<T> *new_node= new NodeHT<T>(data,key);
    NodeHT<T>* nodeHt=chain[h];
    if(nodeHt == nullptr)
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
    curr_size++;
    if ((double(curr_size)/arr_size)>=1)
        changeSize(true);
}

template<class T>
void HashTable<T>::remove(int key) {
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
    curr_size--;
    if ((double(curr_size)/arr_size)<=bottom_threshold && arr_size/2>=min_size)
        changeSize(false);
}

template<class T>
void HashTable<T>::changeSize(bool increase)
{
    int old_size = arr_size;
    if (increase)
        arr_size = arr_size * 2;
    else
        arr_size = arr_size/2;
    NodeHT<T>** old_chain = chain;
    chain = new NodeHT<T>*[arr_size];
    m = arr_size-1;
    for (int i=0;i<arr_size;i++)
    {
        chain[i] = nullptr;
    }
    curr_size = 0;
    for (int i=0;i<old_size;i++)
    {
        NodeHT<T>* dummy_node=old_chain[i];
        if (dummy_node==nullptr)
            continue;
        NodeHT<T>* iterator = dummy_node->getNext();
        while (iterator!=nullptr)
        {
            NodeHT<T>* node_to_add = iterator;
            insert(node_to_add->getData(), node_to_add->getKey());
            iterator=iterator->getNext();
            delete node_to_add;
        }
        delete dummy_node;
    }
    delete[] old_chain;
}

#endif //DATASTRUCTURS_HW2_HashTable_H
