#include "splayTree.h"
#include<stdio.h>
#include<stdlib.h>

#define SWAP(type, a, b) \
    { \
        type __swap_temp; \
        __swap_temp = (b); \
        (b) = (a); \
        (a) = __swap_temp; \
    }

template <class T>
void node::swap(node other){
    SWAP(T, data, other.data);
    SWAP(int, key, other.key);
}

int SplayTree::node::operator<(const node& other){
    return (key < other.key);
}

int SplayTree::node::operator==(const node& other){
    return (key == other.key);
}

template <class T>
node::node(int key, T* data, node* rightSon, node* leftSon)
        : key(key), data(data), rightSon(rightSon), leftSon(leftSon){}

SplayTree::SplayTree(){};
~SplayTree(){};

template <class T>
void SplayTree::insert(int key, T* data){
    insert(key, data, root);
}

void SplayTree::remove(int key){
    splay(key, root);
}

node* SplayTree::find(int key){
    return find(key, root);
}

void SplayTree::destroy_tree(){
    destroy_tree(root);
};

template <class T>
void SplayTree::insert(int key, T* data, node* root) {
    node *right, *left;
    split(root, right, left);
    root = new node(key, data, right, left);
}

void SplayTree::splay(int key, node *x){
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

void split(node* root, node* right, node* left){

}

void SplayTree::leftRotate(node *x) {
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

void SplayTree::rightRotate( node *x ) {
    node *y = x->leftSon;
    if(y) {
        x->leftSon = y->rightSon;
        if( y->rightSon ) y->rightSon->parent = x;
        y->parent = x->parent;
    }
    if( !x->parent ) root = y;
    else if( x == x->parent->leftSon ) x->parent->leftSon = y;
    else x->parent->rightSon = y;
    if(y) y->rightSon = x;
    x->parent = y;
}


