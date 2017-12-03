#include "splayTree.h"

template <class T>
SplayTree<T>::node::node(int key, const T& data, node* rightSon, node* leftSon)
        : key(key), data(data),
          rightSon(rightSon), leftSon(leftSon), parent(nullptr){}

template <class T>
int SplayTree<T>::node::operator<(const node& other){
    return (key < other.key);
}

template <class T>
int SplayTree<T>::node::operator==(const node& other){
    return (key == other.key);
}
template <class T>
SplayTree<T>::SplayTree(node* root) : root (root){}


template <class T>
SplayTree<T>::~SplayTree<T>(){
    destroyTree();
};

template <class T>
void SplayTree<T>::remove(int key){
    find(key);
    join(root->rightSon, root->leftSon);
}

template <class T>
T& SplayTree<T>::find(int key){
//    node *result;
    splay(find(key, root));
    return root->data;
}

template <class T>
void SplayTree<T>::addToDataVec(std::vector<T> allData, node *father){
    if (!father) return;
    addToDataVec(allData, father->leftSon);
    allData.insert(father->data);
    addToDataVec(allData, father->rightSon);
}

//template <class T>
//SplayTree<T>::node* SplayTree<T>::find(int key, SplayTree<T>::node* father){
//    if (!father) return nullptr;
//    if (father->key == key) return father;
//    if (father->key < key) return find(key, father->rightSon);
//    return find(key, father->leftSon);
//}

template <class T>
void SplayTree<T>::destroyTree(){
    destroyTree(root);
}

//template <class T>
//void SplayTree<T>::insert(int key, const T& data) {
//    node *right, *left;
//    split(right, left, key);
//    root = new node(key, data, right, left);
//}

template <class T>
void SplayTree<T>::splay(node *x){
    while( x->parent ) {
        if( !x->parent->parent ) {
            if( x->parent->leftSon == x ) rightRotate( x->parent );
            else leftRotate( x->parent );
        } else if( x->parent->leftSon == x && x->parent->parent->leftSon == x->parent ) {
            rightRotate( x->parent->parent );
            rightRotate( x->parent );
        } else if( x->parent->rightSon == x && x->parent->parent->rightSon == x->parent ) {
            leftRotate( x->parent->parent );
            leftRotate( x->parent );
        } else if( x->parent->leftSon == x && x->parent->parent->rightSon == x->parent ) {
            rightRotate( x->parent );
            leftRotate( x->parent );
        } else {
            leftRotate( x->parent );
            rightRotate( x->parent );
        }
    }
}
template <class T>
void SplayTree<T>::join(SplayTree T1, SplayTree T2){
    T1.findMax();
    root = T1.root;
    root->rootSetup();
    root->rightSon = T2.root;
    root->rightSon->parent = root;
}

template <class T>
void SplayTree<T>::findMax(){
    node * max = root;
    while (max->rightSon){
        max = max->rightSon;
    }
    splay(max);
}

template <class T>
void SplayTree<T>::split(node* right, node* left, int key){
    find(key);
    right =  root->rightSon;
    left = root->leftSon;
}

template <class T>
void SplayTree<T>::leftRotate(node *x) {
    node *y = x->rightSon;
    if(y) {
        x->rightSon = y->leftSon;
        if( y->leftSon ) y->leftSon->parent = x;
        y->parent = x->parent;
    }

    if (!x->parent) root = y;
    else if( x == x->parent->leftSon) x->parent->leftSon = y;
    else x->parent->rightSon = y;
    if(y) y->leftSon = x;
    x->parent = y;
}
template <class T>
void SplayTree<T>::rightRotate(node *x) {
    node *y = x->leftSon;
    if (y) {
        x->leftSon = y->rightSon;
        if (y->rightSon) y->rightSon->parent = x;
        y->parent = x->parent;
    }
    if( !x->parent ) root = y;
    else if( x == x->parent->leftSon ) x->parent->leftSon = y;
    else x->parent->rightSon = y;
    if(y) y->rightSon = x;
    x->parent = y;
}
template <class T>
void SplayTree<T>::destroyTree(node *father){
    if (!father) return;
    destroyTree(father->rightSon);
    destroyTree(father->leftSon);
    delete father;
}
