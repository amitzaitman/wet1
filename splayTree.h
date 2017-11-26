
#ifndef WET1_SPLAYTREE_H
#define WET1_SPLAYTREE_H

struct node
{
    int key_value;
    node *left;
    node *right;
};

class SplayTree{
public:
    SplayTree();
    ~SplayTree();
    void insert(int key);
    void remove(int key);
    node* find(int key);
    void destroy_tree();
private:
    void destroy_tree(node *leaf);
    void insert(int key, node *leaf);
    node *find(int key, node *leaf);

    node *root;
};

#endif //WET1_SPLAYTREE_H
