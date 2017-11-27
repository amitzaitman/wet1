
#ifndef WET1_SPLAYTREE_H
#define WET1_SPLAYTREE_H

template <class T>


template <class T>
class SplayTree{
public:
    SplayTree();
    ~SplayTree();
    void insert(int key, T* data);
    void remove(int key);
    node* find(int key);
    void destroy_tree();
private:
    class node {
        T* data;
    public:
        node(int key, T* data, node* rightSon, node* leftSon);
        int key;
        node *leftSon;
        node *rightSon;
        node *parent;
        void swap(node other);
        int operator<(const node& other);
        int operator==(const node& other);
    };
    void destroy_tree(node *father);
    void insert(int key, T* data, node *father);
    node *find(int key, node *father);
    void splay(int key, node *x);
    void split(node* root, node* right, node* left);cc
    void leftRotate(node *x);
    void rightRotate(node *x);
    node *root;
};

#endif //WET1_SPLAYTREE_H
