#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <memory>

template<class T, class C>
class Node {
    typedef Node<T, C>* NodePtr;
    C key;
    T data;
    T sum_subtree;
    T levels_sum;
    Node<T, C>* parent;
    Node<T, C>* right;
    Node<T, C>* left;
    int h;

public:
    Node(T data, C key) : key(key), data(data), sum_subtree(data), levels_sum(data*key), parent(nullptr),
    right(nullptr), left(nullptr), h(0) {};
    ~Node()
     = default;
    void setKey(C key) {
        this->key = key;
    }

    C &getKey() {
        return this->key;
    }

    C *getKeyPtr() {
        return &(this->key);
    }

    void setData(T data) {
        this->data = data;
    }

    T &getData() {
        return this->data;
    }

    T *getDataPtr() {
        return &(this->data);
    }

    void setHeight(int h) {
        this->h = h;
    }

    int getHeight() {
        return this->h;
    }

    void setParent(NodePtr parent) {
        this->parent = parent;
    }

    NodePtr getParent() {
        return this->parent;
    }

    void setRight(NodePtr right) {
        this->right = right;
    }

    NodePtr getRight() {
        return this->right;
    }

    bool isLeaf() {
        return (this->hasLeft() == false && this->hasRight() == false);
    }

    void setLeft(NodePtr left) {
        this->left = left;
    }

    NodePtr getLeft() {
        return this->left;
    }

    bool hasParent() {
        if (this->parent == nullptr)
            return false;
        return true;
    }

    bool hasRight() {
        if (this->right == nullptr)
            return false;
        return true;
    }

    bool hasLeft() {
        if (this->left == nullptr)
            return false;
        return true;
    }

    bool isRight() {
        if (this->parent == nullptr)
            return false;
        if (this->parent->right == nullptr)
            return false;
        if (this->parent->right->key == this->key)
            return true;
        return false;
    }

    bool isLeft() {
        if (this->parent == nullptr)
            return false;
        if (this->parent->left == nullptr)
            return false;
        if (this->parent->left->key == this->key)
            return true;
        return false;
    }

    NodePtr HasOneSon() {
        if (this->right == nullptr && this->left != nullptr)
            return this->left;
        if (this->right != nullptr && this->left == nullptr)
            return this->right;
        return nullptr;
    }

    int getBF() {
        int h_r = -1, h_l = -1;
        if (this->left != nullptr)
            h_l = this->left->h;
        if (this->right != nullptr)
            h_r = this->right->h;
        return h_l - h_r;
    }

    void removeTies() {
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
    int getSum(){
        return sum_subtree;
    }
    void setSum(int new_sum)
    {
        sum_subtree=new_sum;
    }
    T getLevelSum()
    {
        return levels_sum;
    }
    void setLevelSum(T new_sum)
    {
        levels_sum = new_sum;
    }
};

static int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

template<class T, class C>
static int getNodeHeight(Node<T, C>* node) {
    if (node == nullptr)
        return 0;
    return node->getHeight();
}

template<class T, class C>
static void setNodeHeight(Node<T, C>* node) {
    if (node != nullptr) {
        if (node->isLeaf())
            node->setHeight(0);
        else
            node->setHeight(1 + max(getNodeHeight(node->getLeft()), getNodeHeight(node->getRight())));
    }
}

template<class T, class C>
static int getSum(Node<T, C>* node){
    if (node==nullptr)
        return 0;
    return node->getSum();
}

template<class T, class C>
static T getLevelSum(Node<T, C>* node)
{
    if (node== nullptr)
        return 0;
    return node->getLevelSum();
}

template<class T, class C>
class Avltree {
public:
    typedef Node<T, C>* NodePtr;
    NodePtr root;
    int size;

    Avltree() : root(nullptr), size(0) {}

    ~Avltree()
    {
        this->destroy();
    };

    void deleteAvlNode(NodePtr node);

    void destroy();

    int insert(T data, C key);

    void remove(C key);

    NodePtr removebinary(NodePtr node);

    NodePtr getNextLeft(NodePtr node);

    void makeATree(NodePtr datas [], int start, int end);
    NodePtr buildATree(NodePtr datas [], int start, int end);

    int inorder(NodePtr root,NodePtr order [], int count, int n);
    int preorder(NodePtr root, NodePtr order[], int count);

    int inorderKeys(NodePtr root, C** order, int count);

    void roll(NodePtr node, int bf);

    void llRoll(NodePtr node);

    void lrRoll(NodePtr node);

    void rrRoll(NodePtr node);

    void rlRoll(NodePtr node);

    NodePtr findKey(C key);

    NodePtr getRoot();
    void updateRanks(NodePtr node);
    void updateRanksIteration(NodePtr node);
    void updateTreeRanks();
    void updateTreeRanksAux(Node<T,C>* node);
    T getSumInBorder(C key1, C key2);
    T getHighestSumLevel(C m);
    C findLowestLevelOutOfM(T m);
    T countDataAboveKey(C min_key);

    int getSize()
    {
        return size;
    }

    void Merge(Avltree<T,C>* other);


};

template<class T, class C>
void Avltree<T, C>::deleteAvlNode(Node<T,C>* node)
{
    if (node!=nullptr)
    {
        deleteAvlNode(node->getLeft());
        deleteAvlNode(node->getRight());
        delete node;
        node = nullptr;
    }
}

template<class T, class C>
void Avltree<T, C>::destroy() {
    deleteAvlNode(root);
    root = nullptr;
    size = 0;
}


template<class T, class C>
Node<T, C>* Avltree<T, C>::getRoot() {
    return root;
}

template<class T, class C>
Node<T, C>* Avltree<T, C>::findKey(C key) {
    if (root == nullptr)
        return nullptr;
    NodePtr iterator = root;
    while (iterator != nullptr) {
        if (iterator->getKey() == key)
            return iterator;
        if (iterator->getKey() < key) {
            iterator = iterator->getRight();
            continue;
        }
        if (iterator->getKey() > key) {
            iterator = iterator->getLeft();
        }
    }
    return nullptr;
}

template<class T, class C>
int Avltree<T, C>::insert(T data, C key) {
    if (root == nullptr) {
        Node<T,C>* node = new Node<T,C>(data, key);
        root = node;
        size++;
        return 1;
    }
    Node<T,C>* existing_node = this->findKey(key);
    if (existing_node != nullptr)
    {
        existing_node->setData(existing_node->getData()+data);
        updateRanksIteration(existing_node);
        return 1;
    }
    Node<T,C>* node = new Node<T,C>(data, key);
    size++;
    NodePtr iterator = root;
    while (iterator != nullptr) {
        if (iterator->getKey() < key) {
            if (!(iterator->hasRight()))
                break;
            iterator = iterator->getRight();
            continue;
        }
        if (iterator->getKey() > key) {
            if (!iterator->hasLeft())
                break;
            iterator = iterator->getLeft();
        }
    }
    if (iterator->getKey() > key)
        iterator->setLeft(node);
    else
        iterator->setRight(node);
    node->setParent(iterator);
    node->setHeight(0);
    iterator = node;
    //updating ranks:
    updateRanksIteration(node);
    //balancing:
    iterator = node;
    while (iterator != root) {
        NodePtr p = iterator->getParent();
        int it_height = iterator->getHeight();
        int p_height = p->getHeight();
        if (p_height >= it_height + 1)
        {
            return 1;
        }

        p->setHeight(it_height + 1);
        if (p->getBF() >= 2 || p->getBF() <= -2) {
            roll(p, p->getBF());
            return 1;
        }
        iterator = p;
    }
    return 1;
}
template<class T, class C>
void Avltree<T, C>::updateRanksIteration(Node<T, C>* node){
    Node<T, C>* iterator = node;
    while(iterator!=nullptr)
    {
        updateRanks(iterator);
        iterator = iterator->getParent();
    }

}
template<class T, class C>
void Avltree<T, C>::updateRanks(Node<T, C>* node)
{
    node->setLevelSum(getLevelSum(node->getLeft()) + getLevelSum(node->getRight()) + (node->getData()*node->getKey()));
    node->setSum(getSum(node->getLeft()) + getSum(node->getRight()) + node->getData());

}


template<class T, class C>
void Avltree<T, C>::roll(NodePtr node, int bf) {
    if (bf == 2 && node->hasLeft()) {
        if (node->getLeft()->getBF() >= 0) {
            llRoll(node);
            return;
        }
        if (node->getLeft()->getBF() == -1) {
            lrRoll(node);
            return;
        }
    }
    if (bf == -2 && node->hasRight()) {
        if (node->getRight()->getBF() <= 0) {
            rrRoll(node);
            return;
        }
        if (node->getRight()->getBF() == 1) {
            rlRoll(node);
            return;
        }
    }
}

template<class T, class C>
void Avltree<T, C>::llRoll(NodePtr node) {
    NodePtr temp = node->getLeft();
    node->setLeft(temp->getRight());
    if(temp->getRight()!= nullptr)
    {
        temp->getRight()->setParent(node);
    }
    temp->setRight(node);
    if (node->hasParent()) {
        if (node->isLeft())
            node->getParent()->setLeft(temp);
        if (node->isRight())
            node->getParent()->setRight(temp);
    } else
        root = temp;
    temp->setParent(node->getParent());
    node->setParent(temp);
    //updating heights:
    setNodeHeight(node);
    setNodeHeight(temp);
    updateRanks(node);
    updateRanks(temp);
}

template<class T, class C>
void Avltree<T, C>::lrRoll(NodePtr node) {
    NodePtr temp1 = node->getLeft();
    NodePtr temp2 = node->getLeft()->getRight();
    node->setLeft(temp2->getRight());
    if (temp2->getRight() != nullptr)
        temp2->getRight()->setParent(node);
    temp1->setRight(temp2->getLeft());
    if (temp2->getLeft() != nullptr)
        temp2->getLeft()->setParent(temp1);
    temp2->setLeft(temp1);
    temp1->setParent(temp2);
    temp2->setRight(node);
    if (node->getKey() == root->getKey()) {
        root = temp2;
        temp2->setParent(nullptr);
    } else {
        temp2->setParent(node->getParent());
        if (node->isRight())
            node->getParent()->setRight(temp2);
        else
            node->getParent()->setLeft(temp2);
    }
    node->setParent(temp2);
    //updating heights:
    setNodeHeight(node);
    setNodeHeight(temp1);
    setNodeHeight(temp2);
    updateRanks(node);
    updateRanks(temp1);
    updateRanks(temp2);

}

template<class T, class C>
void Avltree<T, C>::rrRoll(NodePtr node) {
    NodePtr temp = node->getRight();
    node->setRight(temp->getLeft());
    if(temp->getLeft()!= nullptr)
    {
        temp->getLeft()->setParent(node);
    }
    if (node->hasParent()) {
        if (node->isLeft())
            node->getParent()->setLeft(temp);
        if (node->isRight())
            node->getParent()->setRight(temp);
    } else
        root = temp;
    temp->setLeft(node);
    temp->setParent(node->getParent());
    node->setParent(temp);
    //updating heights:
    if (node->isLeaf())
        node->setHeight(0);
    else
        node->setHeight(1 + max(getNodeHeight(node->getLeft()), getNodeHeight(node->getLeft())));
    temp->setHeight(1 + max(getNodeHeight(temp->getLeft()), getNodeHeight(temp->getRight())));
    updateRanks(node);
    updateRanks(temp);
}

template<class T, class C>
void Avltree<T, C>::rlRoll(NodePtr node) {
    NodePtr temp1 = node->getRight();
    NodePtr temp2 = node->getRight()->getLeft();
    node->setRight(temp2->getLeft());
    if (temp2->getLeft() != nullptr)
        temp2->getLeft()->setParent(node);
    temp1->setLeft(temp2->getRight());
    if (temp2->getRight() != nullptr)
        temp2->getRight()->setParent(temp1);
    temp2->setRight(temp1);
    temp1->setParent(temp2);
    temp2->setLeft(node);
    if (node->getKey() == root->getKey()) {
        root = temp2;
        temp2->setParent(nullptr);
    } else {
        temp2->setParent(node->getParent());
        if (node->isRight())
            node->getParent()->setRight(temp2);
        else
            node->getParent()->setLeft(temp2);
    }
    node->setParent(temp2);

    //updating heights:
    setNodeHeight(node);
    setNodeHeight(temp1);
    setNodeHeight(temp2);
    updateRanks(node);
    updateRanks(temp1);
    updateRanks(temp2);
}

template<class T, class C>
int Avltree<T, C>::inorder(NodePtr root,NodePtr order [] , int count, int n) {
    if (!root || count==n) {
        return 0;
    }
    int tmp;
    tmp = this->inorder(root->getLeft(), order, count,n);
    if (tmp != 0)
        count = tmp;
    if(count!=n){
        order[count] = root;
        count++;
        if(count!= n){
            tmp = this->inorder(root->getRight(), order, count,n);
            if (tmp != 0)
                count = tmp;
        }
    }
    return count;
}

template<class T, class C>
int Avltree<T, C>::preorder(NodePtr root, NodePtr *order, int count) {
    if (!root) {
        return 0;
    }
    int tmp;
    tmp = this->preorder(root->getLeft(), order, count);
    if (tmp != 0)
        count = tmp;
    tmp = this->preorder(root->getRight(), order, count);
    if (tmp != 0)
        count = tmp;
    order[count] = root;
    count++;
    return count;
}

template<class T, class C>
int Avltree<T, C>::inorderKeys(NodePtr root, C** order, int count) {
    if (!root) {
        return 0;
    }
    int tmp;
    tmp = this->inorderKeys(root->getLeft(), order, count);
    if (tmp != 0)
        count = tmp;
    order[count] = root->getKeyPtr();
    count++;
    tmp = this->inorderKeys(root->getRight(), order, count);
    if (tmp != 0)
        count = tmp;
    return count;
}

template<class T, class C>
Node<T, C>* Avltree<T, C>::removebinary(NodePtr node) {
    if(node== nullptr){
        return nullptr;
    }
    if (node->isLeaf()) {
        if (root->getKey() == node->getKey()) {
            node->removeTies();
            delete root;
            root = nullptr;
            return nullptr;
        }
        if (node->isRight()) {
            node->getParent()->setRight(nullptr);
        } else {
            node->getParent()->setLeft(nullptr);
        }
        NodePtr parent = node->getParent();
        node->removeTies();

        setNodeHeight(node);
        setNodeHeight(parent);
        delete node;
        updateRanksIteration(parent);
        return parent;
    }
    if (node->HasOneSon() != nullptr) {
        if (root->getKey() == node->getKey()) {
            root = node->HasOneSon();
            node->HasOneSon()->setParent(nullptr);
            node->removeTies();
            setNodeHeight(node);
            delete node;
            return nullptr;
        }
        if (node->isLeft()) {
            node->getParent()->setLeft(node->HasOneSon());
            node->HasOneSon()->setParent(node->getParent());
        } else{
            node->getParent()->setRight(node->HasOneSon());
            node->HasOneSon()->setParent(node->getParent());
        }
        NodePtr parent = node->getParent();
        node->removeTies();
        setNodeHeight(node);
        setNodeHeight(parent);
        delete node;
        updateRanksIteration(parent);
        return parent;
    }
    NodePtr new_root = getNextLeft(node);
    NodePtr new_right_son;
    NodePtr new_parent = node->getParent();
    NodePtr new_grandson = new_root->getRight();
    NodePtr old_parent = new_root->getParent();

    if (!(new_root->getParent()->getKey() == node->getKey())) {
        new_right_son = node->getRight();
    } else {
        new_right_son = new_root->getRight();
    }
    if (new_right_son != nullptr){
        if(new_grandson!= nullptr &&(!(new_right_son->getKey()==new_grandson->getKey()))) {
            new_right_son->setParent(new_root);
            if(old_parent->getKey()==new_right_son->getKey()){
                new_right_son->setLeft(new_grandson);
                new_grandson->setParent(new_right_son);
            }
            else{
                old_parent->setLeft(new_grandson);
                new_grandson->setParent(old_parent);
            }
        }
        if(new_grandson== nullptr)
        {
            new_right_son->setParent(new_root);
            if(old_parent->getKey()==new_right_son->getKey()){
                new_right_son->setLeft(new_grandson);
            }
            else
                old_parent->setLeft(new_grandson);
        } else
        {
            new_right_son->setParent(new_root);
        }
    }
    new_root->setParent(new_parent);
    new_root->setLeft(node->getLeft());
    new_root->setRight(new_right_son);
    node->getLeft()->setParent(new_root);

    if (new_parent != nullptr) {
        if (node->isRight())
            new_parent->setRight(new_root);
        else
            new_parent->setLeft(new_root);
    }
    if(node->getKey()== root->getKey())
    {
        root=new_root;
    }
    node->removeTies();
    setNodeHeight(new_grandson);
    setNodeHeight(old_parent);
    setNodeHeight(new_right_son);
    setNodeHeight(new_root);
    setNodeHeight(new_parent);
    updateRanksIteration(new_grandson);
    updateRanksIteration(new_right_son);
    if(!(old_parent->getKey()== node->getKey()))
    {
        updateRanksIteration(old_parent);
    }
    else
    {
        updateRanksIteration(new_root);
    }
    delete node;
    if (new_right_son != nullptr) {
        return new_right_son;
    }
    return new_root;
}

template<class T, class C>
void Avltree<T, C>::remove(C key) {

    NodePtr node_to_remove = this->findKey(key);
    if (node_to_remove== nullptr)
        return;
    if (node_to_remove->getData()>1){
        node_to_remove->setData(node_to_remove->getData()-1);
        updateRanksIteration(node_to_remove);
        return;
    }
    NodePtr node = removebinary(node_to_remove);
    if (node != nullptr) {
        roll(node, node->getBF());
        while (node->getParent() != nullptr) {
            node = node->getParent();
            roll(node, node->getBF());
        }
    }
    size--;
}

template<class T, class C>
Node<T, C>* Avltree<T, C>::getNextLeft(NodePtr node) {
    NodePtr node_next = node->getRight();
    while (node_next->hasLeft()) {
        node_next = node_next->getLeft();
    }
    return node_next;
}

template<class T, class C>
void Avltree<T, C>::makeATree(NodePtr *datas, int start, int end)  {
    root= buildATree(datas,start,end);
    setNodeHeight(root);
}
template<class T,class C>
Node<T, C>* Avltree<T, C>::buildATree(NodePtr *datas, int start, int end) {
    if(start>end)
        return nullptr;
    int mid=(end+start)/2;
    NodePtr Node_r = new Node<T,C> (datas[mid]->getData(), datas[mid]->getKey());
    Node_r->setLeft(buildATree(datas,start, mid-1));
    Node_r->setRight(buildATree(datas,mid+1,end));
    if(Node_r->getRight()!= nullptr)
        Node_r->getRight()->setParent(Node_r);
    if(Node_r->getLeft()!= nullptr)
        Node_r->getLeft()->setParent(Node_r);
    setNodeHeight(Node_r);
    return Node_r;
}
template<class T, class C>
void Avltree<T,C>::Merge(Avltree<T,C>* other)
{
    int size1 = size;
    int size2 = other->getSize();
    int final_size = 0;
    if(size2 ==0)
        return;
    if(size1==0 && size2 ==1)
    {
       this->root =  other->root;
       this->size = 1;
       other->root = nullptr;
       other->size = 0;
       return;
    }
    Node<T,C>** tree_nodes = new Node<T,C>*[size1];
    Node<T,C>** other_nodes = new Node<T,C>*[size2];
    Node<T,C>** new_tree_arr = new Node<T,C>*[size1+size2];

    inorder(this->root,tree_nodes,0,size1);
    inorder(other->root ,other_nodes,0,size2);
    int c1 = 0, c2 = 0, double_counter = 0;

    while(c1 != size1 && c2 != size2)
    {
        if (tree_nodes[c1]->getKey() > other_nodes[c2]->getKey()) {
            new_tree_arr[c1 + c2 - double_counter] = new Node<T,C>(other_nodes[c2]->getData(), other_nodes[c2]->getKey());
            c2++;
            final_size++;
        } else if (tree_nodes[c1]->getKey() < other_nodes[c2]->getKey()){
            new_tree_arr[c1 + c2- double_counter] = new Node<T,C> (tree_nodes[c1]->getData(), tree_nodes[c1]->getKey());
            c1++;
            final_size++;
        }
        else
        {
            new_tree_arr[c1+c2-double_counter] = new Node<T,C>(tree_nodes[c1]->getData(), tree_nodes[c1]->getKey());
            new_tree_arr[c1+c2-double_counter]->setData(new_tree_arr[c1+c2-double_counter]->getData()+other_nodes[c2]->getData());
            c1++;
            c2++;
            double_counter++;
            final_size++;
        }
    }
    while (c1!=size1)
    {
        new_tree_arr[c1 + c2 - double_counter] = new Node<T,C>(tree_nodes[c1]->getData(), tree_nodes[c1]->getKey());
        c1++;
        final_size++;
    }
    while (c2 != size2) {
        new_tree_arr[c1 + c2-double_counter] = new Node<T,C>(other_nodes[c2]->getData(), other_nodes[c2]->getKey());
        c2++;
        final_size++;
    }
    for(int i=0; i<final_size;i++)
    {
        new_tree_arr[i]->removeTies();
    }
    this->destroy();
    makeATree(new_tree_arr,0,final_size-1);
    other->destroy();
    size=final_size;
    this->updateTreeRanks();
    delete [] tree_nodes;
    delete [] other_nodes;
    for(int i=0; i<final_size;i++)
    {
        delete new_tree_arr[i];
    }
    delete []new_tree_arr;
}

template<class T, class C>
void Avltree<T,C>::updateTreeRanks() {
    updateTreeRanksAux(root);
}

template<class T, class C>
void Avltree<T,C>::updateTreeRanksAux(Node<T,C>* node) {
    if (node == nullptr)
        return;
    updateTreeRanksAux(node->getLeft());
    updateTreeRanksAux(node->getRight());
    updateRanks(node);
}

template<class T, class C>
T Avltree<T,C>::getSumInBorder(C key1, C key2) {
    T sum2 = 0;
    T sum1 = 0;
    Node<T,C>* iterator = root;
    while(iterator!=nullptr)
    {
        if (iterator->getKey()<=key2)
        {
            sum2 = sum2 + iterator->getData();
            if (iterator->getLeft()!=nullptr)
                sum2 = sum2 + iterator->getLeft()->getSum();
            if(iterator->getKey()==key2)
                break;
            iterator=iterator->getRight();
        }
        else
            iterator=iterator->getLeft();
    }
    iterator = root;
    while(iterator!=nullptr)
    {
        if (iterator->getKey()<key1)
        {
            sum1 = sum1 + iterator->getData();
            if (iterator->getLeft()!=nullptr)
                sum1 = sum1 + iterator->getLeft()->getSum();
            iterator=iterator->getRight();
        }
        else
            iterator=iterator->getLeft();
    }
    return sum2-sum1;

}

template<class T, class C>
T Avltree<T, C>::getHighestSumLevel(C m) {
    Node<T,C>* iterator = root;
    T sum=0;
    while (iterator!= nullptr &&  m >0 )
    {
        if(iterator->getRight()!= nullptr)
        {
                if(iterator->getRight()->getSum()>m)
                {
                    iterator=iterator->getRight();
                    continue;
                }
                sum+=iterator->getRight()->getLevelSum();
                m-=iterator->getRight()->getSum();
        }
        if(iterator->getData()>m)
        {
            sum+=m*iterator->getKey();
            return sum;
        }
        sum+=iterator->getKey()*iterator->getData();
        m-=iterator->getData();
        iterator=iterator->getLeft();
    }
    return sum;
}

template<class T, class C>
C Avltree<T, C>::findLowestLevelOutOfM(T m)
{
    Node<T,C>* iterator = root;
    if(root == nullptr)
        return 0;
    while(iterator!=nullptr && m > 0)
    {
        if(iterator->getRight()!=nullptr)
        {
            if(iterator->getRight()->getSum()>=m)
            {
                iterator=iterator->getRight();
                continue;
            }
            m-=iterator->getRight()->getSum();
        }
        if(iterator->getData()>=m)
        {
            return iterator->getKey();
        }
        m-=iterator->getData();
        iterator=iterator->getLeft();
    }
    return 0;
}

template<class T, class C>
T Avltree<T, C>::countDataAboveKey(C min_key)
{
    Node<T,C>* iterator = root;
    if(root== nullptr)
        return 0;
    int sum=0;
    while (iterator!=nullptr)
    {
        if(iterator->getKey()<min_key)
        {
            iterator=iterator->getRight();
            continue;
        }

        if(iterator->getRight()!=nullptr)
            sum += iterator->getRight()->getSum();
        sum+=iterator->getData();
        iterator = iterator->getLeft();
    }
    return sum;
}
#endif