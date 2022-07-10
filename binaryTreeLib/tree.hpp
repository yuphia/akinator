#ifndef TREE_H

#define TREE_H 1

#include "stdlib.h"
#include "stdio.h"
#include <assert.h>
#include "../errDetect/err.h"
#include <errno.h>

typedef char data_t;

enum LR
{
    LEFT,
    RIGHT
};

struct BinaryTreeNode
{
    data_t* data;

    BinaryTreeNode *lChild;
    BinaryTreeNode *rChild;

    size_t depth;

    BinaryTreeNode *parent;
};

struct BinaryTree
{
    BinaryTreeNode* root;    

    size_t amountOfElements;
};

Errors treeCtor (BinaryTree *tree, data_t *rootData);
Errors treeAppendElement (BinaryTree *tree, BinaryTreeNode *parent, 
                        data_t *data, LR side);
Errors treeDeleteElement (BinaryTree *tree, BinaryTreeNode *node);
Errors treeDtor (BinaryTree *tree);

Errors allocNode (BinaryTreeNode **node, data_t *data);
Errors allocData (data_t **value, size_t amount);

Errors treeInsertInPlace (BinaryTree *tree, BinaryTreeNode *node,
                        data_t *data);

#endif
