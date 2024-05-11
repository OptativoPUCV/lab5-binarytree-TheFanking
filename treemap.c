#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
    TreeMap *nuevo = malloc(sizeof(TreeMap));
    if (nuevo == NULL) return NULL;
    nuevo->lower_than = lower_than;
    nuevo->root = NULL;
    nuevo->current = NULL;
    return nuevo;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
   TreeNode *newNode = createTreeNode(key,value);
   TreeNode *aux = tree->root;
   TreeNode *parent = NULL;
   while (aux != NULL)
       {
           parent = aux;
           if (is_equal(tree,aux->pair->key,key) == 1)
           {
               return;
           }
           else if (tree->lower_than(key,aux->pair->key))
           {
               aux = aux->left;
           }
           else
           {
               aux = aux->right;
           }
       }
    if (parent == NULL)
    {
        tree->current = newNode;
    }
    else if (tree->lower_than(key,parent->pair->key))
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }
}

TreeNode * minimum(TreeNode * x)
{
    if (x->left == NULL)
    {
        return x;
    }
    while (x->left != NULL)
        {
            x = x->left;
        }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{    
    TreeNode *aux = tree->root;
    while (aux != NULL)
        {
            if (is_equal(tree,key,aux->pair->key) == 1)
            {
                tree->current = aux;
                return aux->pair;
            }
            if (tree->lower_than(key,aux->pair->key) == 1)
            {
                aux = aux->left;
            }
            else
            {
                aux = aux->right;    
            }
            
        }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) 
{
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) 
{
    TreeNode *aux = tree->root;
    while (aux->left != NULL)
        {
            aux = aux->left;
        }
    tree->current = aux;
    return aux->pair;
}

Pair * nextTreeMap(TreeMap * tree) 
{
    
    return NULL;
}
