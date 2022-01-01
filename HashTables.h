
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
class HashTables {
    int m;
    int arr_size;
    int curr_size;
    double top_threshold;
    double bottom_threshold;
    NodeHT<T>** chain;
public:
    HashTables(): arr_size(DEFAULT_SIZE), m(DEFAULT_SIZE+1){};
    HashTables(int arr_size): arr_size(arr_size), m(arr_size+1){
        top_threshold = 1;
        bottom_threshold = 0.5;
        chain = new NodeHT<T>*[arr_size];
        for (int i = 0; i < arr_size; ++i) {
            chain[i]= nullptr;
        }
    }
    ~HashTables()=default;
    HashTables(HashTables<T>& hashTables)=default;

    bool member(int key);
    void insert(T data, int key);
    void remove(int key);
    void increaseSize();
    void reduceSize();
};

template<class T>
bool HashTables<T>::member(int key) {
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
void HashTables<T>::insert(T data, int key) {
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
        increaseSize();
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
    curr_size--;
    if ((double(curr_size)/arr_size)<=bottom_threshold)
        reduceSize();
}

template<class T>
void HashTables<T>::increaseSize()
{
    int old_size = arr_size;
    arr_size = arr_size*2;
    NodeHT<T>** old_chain = chain;
    chain = new NodeHT<T>*[arr_size];
    m = arr_size+1;
    for (int i=0;i<old_size;i++)
    {
        NodeHT<T>* temp=old_chain[i];
        while (temp!=nullptr)
        {
            NodeHT<T>* node_to_add = temp;
            temp=temp->getNext();
            int h = node_to_add->getKey()%m;
            NodeHT<T>* nodeHt = chain[h];
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
            int h = temp->getKey()%m;
            chain
            temp=temp->getNext();
        }
    }

}

#endif //DATASTRUCTURS_HW2_HASHTABLES_H
