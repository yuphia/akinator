#ifndef TREE_CPP
#define TREE_CPP 1

#include "tree.hpp"

Errors treeCtor (BinaryTree *tree, data_t *rootData)
{
    checkNullptr (tree);
    checkNullptr (rootData);

    tree->root = (BinaryTreeNode*) calloc (1, sizeof(BinaryTreeNode));
    if (tree->root == NULL)
        return ALLOC_ERROR;

    tree->root->lChild = nullptr;
    tree->root->rChild = nullptr;
    tree->root->parent = nullptr;
    tree->root->depth = 0;

    tree->root->data = rootData;

    return NO_ERROR;
}

Errors treeDtor (BinaryTree *tree)
{
    checkNullptr (tree);

    Errors tempErr = treeDeleteElement (tree, tree->root); 
    passErr(); 

    free (tree->root);
    free (tree);

    return NO_ERROR;
}

Errors treeDeleteElement (BinaryTree *tree, BinaryTreeNode *node)
{
    checkNullptr (tree);
    checkNullptr (node);

    Errors tempErr = NO_ERROR;
    if (node->lChild != nullptr)
    {
        tempErr = treeDeleteElement (tree, node->lChild);
        passErr();
    }

    if (node->rChild != nullptr)
    {
        tempErr = treeDeleteElement (tree, node->rChild);
        passErr();
    }

    if (tree->root != node)
    {
        if (node->parent->lChild == node)
            node->parent->lChild = nullptr;
        if (node->parent->rChild == node)
            node->parent->rChild = nullptr;
    }

    tree->amountOfElements--;

    free (node->data);
    free (node);

    return NO_ERROR;
}

Errors treeAppendElement (BinaryTree *tree, BinaryTreeNode *parent, 
                    data_t *data, LR side)
{
    checkNullptr (tree);
    checkNullptr (data);

    Errors tempErr = NO_ERROR;

    data_t *nodeData = data;   
    BinaryTreeNode *appendant = nullptr;
    allocNode (&appendant, nodeData);

    passErr();

    if (parent != nullptr)
    {
        if (side == RIGHT)
            parent->rChild = appendant;
        else if (side == LEFT)
            parent->lChild = appendant;
    }

    appendant->parent = parent;
    appendant->depth = parent->depth + 1;

    tree->amountOfElements++;

    return NO_ERROR;
}

Errors treeInsertInPlace (BinaryTree *tree, BinaryTreeNode *node, data_t *data)
{
    checkNullptr (tree);
    checkNullptr (node);
    checkNullptr (data);

    if (node->parent != nullptr)
        node->depth = node->parent->depth + 1;
    else 
        node->depth = 0;


    node->data = data;

    return NO_ERROR;
}

Errors allocData (data_t **pointer, size_t amount)
{
    checkNullptr (pointer);

    *pointer = (data_t*) calloc (amount, sizeof(data_t));   
    checkNullptr (pointer);
    return NO_ERROR;
}

Errors allocNode (BinaryTreeNode **node, data_t *data)
{
    checkNullptr (data);
    checkNullptr (node);

    *node = (BinaryTreeNode*)calloc (1, sizeof(BinaryTreeNode));

    checkNullptr (*node);

    (*node)->data = data;

    (*node)->parent = nullptr;
    (*node)->lChild = nullptr;
    (*node)->rChild = nullptr;

    return NO_ERROR;
}

#endif