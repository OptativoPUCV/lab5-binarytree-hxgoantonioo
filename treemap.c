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
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    if (tree == NULL || key == NULL || value == NULL) return;
    if (tree->root == NULL)
    {
        tree->root = createTreeNode(key ,value);
    }
    else
    {
        TreeNode * aux = tree->root;
        while (aux != NULL)
            {
                if (is_equal(tree, key, aux->pair->key))
                {
                    return;
                }
                else
                {
                    if (tree->lower_than(key, aux->pair->key) == 1)
                    {
                        if (aux->left == NULL)
                        {
                            aux->left = createTreeNode(key, value);
                            aux->left->parent = aux;
                            tree->current = aux->left;
                        }
                        aux = aux->left;
                    }
                    else
                    {
                        if (aux->right == NULL)
                        {
                            aux->right = createTreeNode(key, value);
                            aux->right->parent = aux;
                            tree->current = aux->right;
                        }
                        aux = aux->right;
                    }
                }
            }
    }
}

TreeNode * minimum(TreeNode * x)
{
    while (x->left != NULL)
    {
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap* tree, TreeNode* node)
{
    
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
    TreeNode * aux = tree->root;
    while(aux!=NULL)
        {
            if(is_equal(tree, key, aux->pair->key))
            {
                tree->current = aux;
                return aux->pair;
            }
            else
            {
                if(tree->lower_than(key, aux->pair->key))
                {
                    aux = aux->left;
                }
                else
                {
                    aux = aux->right;
                }
            }
        }
    return NULL;
}


Pair* upperBound(TreeMap* tree, void* key) {
    TreeNode* current = tree->root;
    TreeNode* result = NULL;

    while (current != NULL) {
        if (tree->lower_than(key, current->pair->key) || is_equal(tree, key, current->pair->key)) {
            result = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (result == NULL) {
        return NULL;
    }

    tree->current = result;
    return result->pair;
}

Pair * firstTreeMap(TreeMap * tree)
{
    TreeNode * aux = tree->root;
    while(aux->left!=NULL)
        {
            aux = aux->left;
        }
    tree->current = aux;
    return aux->pair;
}

Pair * nextTreeMap(TreeMap * tree)
{
    TreeNode * aux = tree->current;
    if(aux->right!=NULL)
    {
        aux = aux->right;
        while(aux->left!=NULL)
            {
                aux = aux->left;
            }
        tree->current = aux;
        return aux->pair;
    }
    else
    {
        TreeNode * p = aux->parent;
        while(p!=NULL && aux==p->right)
            {
                aux = p;
                p = p->parent;
            }
        tree->current = p;
        if(p!=NULL)
        {
            return p->pair;
        }
        else
        {
            return NULL;
        }
    }
}
