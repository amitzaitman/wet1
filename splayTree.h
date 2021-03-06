#ifndef WET1_SPLAYTREE_H
#define WET1_SPLAYTREE_H

#include <vector>
#include <assert.h>
#include <stdexcept>
#include <new>


class alreadyIn : public std::exception{};
class ElementNotFound : public std::exception{};


template <class T, class K = int>
class SplayTree{
    struct node {
        node(T data, K key, node* rightSon, node* leftSon)
                : data(data), key(key), rightSon(rightSon), leftSon(leftSon), parent(NULL){}
        T data;
        K key;
        node *rightSon;
        node *leftSon;
        node *parent;
        int operator<(const node& other){
            return key < other.key;
        }
        bool operator==(const node& other){
            return key == other.key;
        }
    } * root;
    int size;

public:
    SplayTree() : root (NULL), size(0){}

    SplayTree(node* root) : root (root), size(0){
        if (root) root->parent = NULL;
    }

    ~SplayTree(){
        destroyTree();
    }

    void remove(K key){
        find(key);
        node *right = root->rightSon, *left = root->leftSon;
        delete root;
        size--;
        if(size == 0) root = NULL;
        else join(right, left);
    }

    void insert(K key, const T& data) {
        node * newNode = new node(data, key, NULL, NULL);
        if (!root) {
            root = newNode;
            size++;
            return;
        }
        try {
            find(key);
        }
        catch (...){};
        if(root->key == key) throw (alreadyIn());
        size++;
        if (root->key < key) {
            newNode->rightSon = root->rightSon;
            newNode->leftSon = root;
            root = newNode;
            root->leftSon->parent = root;
            root->leftSon->rightSon = NULL;
            if (root->rightSon) root->rightSon->parent = root;
            return;
        }
        newNode->rightSon = root;
        newNode->leftSon = root->leftSon;
        root = newNode;
        root->rightSon->parent = root;
        root->rightSon->leftSon = NULL;
        if (root->leftSon) root->leftSon->parent = root;
    }

    T& findData(K key){
        return find(key)->data;
    }

    node* find(K key){
        if (!root) throw ElementNotFound();
        splay(find(key, root));
        if (!(root->key == key)) throw ElementNotFound();
        return root;
    }

    void splayMax(){
            if (!root) return;
            node * max = root;
            while (max->rightSon){
                max = max->rightSon;
            }
            splay(max);
    }

    void splayMin(){
        if (!root) return;
        node * min = root;
        while (min->leftSon){
            min = min->leftSon;
        }
        splay(min);
    }

    T& findMax(){
        if (!root) throw ElementNotFound();
        node * max = root;
        while (max->rightSon){
            max = max->rightSon;
        }
        return max->data;
    }


    T& findMin(){
        if (!root) throw ElementNotFound();
        node * min = root;
        while (min->leftSon){
            min = min->leftSon;
        }
        return min->data;
    }

    void join(SplayTree T1, SplayTree T2){
        T2.splayMax();
        if (!T2.root){
            T1.splayMin();
            root = T1.root;
            T1.root = NULL;
            return;
        }
        root = T2.root;
        root->rightSon = T1.root;
        if (root->rightSon){
            root->rightSon->parent = root;
        }
        T1.root = NULL;
        T2.root = NULL;
    }

    template <class Pred>
    T* getDataByPred(Pred pred, int* count){
        if(!size) return NULL;
        T* allData = new T[size * sizeof(*allData)];
        *count = 0;
        addToDataVec(allData, pred, count, root);
        return allData;
    }

    int getSize(){
            return size;
    }

    void destroyTree(){
        destroyTree(root);
    }

private:
    void destroyTree(node *father){
        if (!father) return;
        if (father->leftSon) destroyTree(father->leftSon);
        if (father->rightSon) destroyTree(father->rightSon);
        delete father;
        size--;
    }

    void splay(node *x) {
        assert(x);
        while (x->parent) {
            if (!x->parent->parent) {
                if (x->parent->leftSon == x) rightRotate(x->parent);
                else leftRotate(x->parent);
            } else if (x->parent->leftSon == x &&
                       x->parent->parent->leftSon == x->parent) {
                rightRotate(x->parent->parent);
                rightRotate(x->parent);
            } else if (x->parent->rightSon == x &&
                       x->parent->parent->rightSon == x->parent) {
                leftRotate(x->parent->parent);
                leftRotate(x->parent);
            } else if (x->parent->leftSon == x &&
                       x->parent->parent->rightSon == x->parent) {
                rightRotate(x->parent);
                leftRotate(x->parent);
            } else {
                leftRotate(x->parent);
                rightRotate(x->parent);
            }
        }
    }

    node* find(K key, node* father){
        assert(father);
        if (father && father->key == key) return father;
        if (father->key < key) {
            if (father->rightSon) return find(key, father->rightSon);
            return father;
        }
        if (father->leftSon) return find(key, father->leftSon);
        return father;
    }

    void leftRotate(node *x) {
        assert(x);
        node *y = x->rightSon;
        if (y) {
            x->rightSon = y->leftSon;
            if (y->leftSon) y->leftSon->parent = x;
            y->parent = x->parent;
        }

        if (!x->parent) root = y;
        else if( x == x->parent->leftSon) x->parent->leftSon = y;
        else x->parent->rightSon = y;
        if(y) y->leftSon = x;
        x->parent = y;
    }

    void rightRotate(node *x) {
        assert(x);
        node *y = x->leftSon;
        if (y) {
            x->leftSon = y->rightSon;
            if (y->rightSon) y->rightSon->parent = x;
            y->parent = x->parent;
        }
        if (!x->parent) root = y;
        else if (x == x->parent->leftSon) x->parent->leftSon = y;
        else x->parent->rightSon = y;
        if (y) y->rightSon = x;
        x->parent = y;
    }

    template <class Pred>
    void addToDataVec(T* DataByPred, Pred pred,  int *place, node *father){
        if (!father) return;
        addToDataVec(DataByPred,pred, place, father->leftSon);
        if (pred(father->data)) DataByPred[(*place)++] = father->data;
        addToDataVec(DataByPred, pred, place, father->rightSon);
    }
};

#endif //WET1_SPLAYTREE_H

