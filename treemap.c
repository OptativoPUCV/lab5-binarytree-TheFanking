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
                            
}
TreeNode * minimum(TreeNode * x)
{
    if (x == NULL)
    {
        return NULL;
    }
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


void removeNode(TreeMap * tree, TreeNode* node) 
{
    TreeNode *aux = tree->root;
    if (node->left == NULL && node->right == NULL)
    {
        if (node->parent != tree->root)
        {
            if (aux->parent->right == node)
            {
                node->parent->right = NULL;
            }
            else
            {
                node->parent->left = NULL;
            }
        }
        else
        {
            tree->root = NULL;
        }
    }
    else if (node->left == NULL || node->right == NULL)
    {
        TreeNode *hijo;
        if (node->parent->left != NULL)
        {
            hijo = node->left;
        }
        else
        {
            hijo = node->right;
        }
        if (node != tree->root)
        {
            if (node->parent->left == node)
            {
                node->parent->left = hijo;
            }
            else
            {
                node->parent->right = hijo;
            }
        }
    }
 
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
    TreeNode *aux = tree->root;
    TreeNode *auxUb = NULL;
    while (aux != NULL)
        {
            if (is_equal(tree,key,aux->pair->key) == 1)
            {
                return aux->pair;
            }
            else if (tree->lower_than(key,aux->pair->key) == 1)
            {
                auxUb = aux;
                aux = aux->left;
            }
            else
            {
                aux = aux->right;
            }
        }
    if (auxUb == NULL)
    {
        return NULL;
    }
    return auxUb->pair;
}

Pair * firstTreeMap(TreeMap * tree) 
{
    TreeNode *aux = tree->root;
    TreeNode *valor = minimum(aux->left);
    tree->current = valor;
    return valor->pair;
}

Pair * nextTreeMap(TreeMap * tree) 
{
    if (tree == NULL || tree->current == NULL)
    {
        return NULL;
    }
    TreeNode *aux = tree->current;
    
    if (aux->right != NULL)
    {
        TreeNode *valor  = minimum(aux->right);
        tree->current = valor;
        return valor->pair;
    }
    else
    {
        while (aux->parent != NULL && aux->parent->right == aux) 
            {
                aux = aux->parent;
            } 
        tree->current = aux->parent;
        if (aux->parent != NULL)
        {
            return aux->parent->pair;
        }
    }
    return NULL;
}
