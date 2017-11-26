#include "splayTree.h"
#include<stdio.h>
#include<stdlib.h>

SplayTree::SplayTree(){};
~SplayTree(){};

void SplayTree::insert(int key){
    
}

void SplayTree::remove(int key);

node* SplayTree::find(int key){
    return find(key, root);
}

void SplayTree::destroy_tree(){
    destroy_tree(root);
};

void SplayTree::destroy_tree(node *father){

}
void SplayTree::find(int key, node *father);
node* SplayTree::search(int key, node *father);