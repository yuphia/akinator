#ifndef AKINATOR_HPP
#define AKINATOR_HPP 1

#include "../binaryTreeLib/drawTree.hpp"
#include "../binaryTreeLib/tree.hpp"
#include "../errDetect/err.h"
#include "string.h"

enum GameMod
{
    PLAY = 1,
    FINISH = 5
};

Errors gameStartup (BinaryTree *tree);
Errors gameFinish (BinaryTree *tree);

Errors gameShell();
Errors gamePlay (BinaryTree *tree, BinaryTreeNode *node);

Errors onSuccessFind ();
Errors onFailFind (BinaryTree *tree, BinaryTreeNode *node);

char askYN();
Errors readData (char **data, FILE *stream);

Errors readTree_ (BinaryTree *tree);
Errors writeTree_ (BinaryTree *tree);
Errors readTree (BinaryTree *tree, BinaryTreeNode **node, 
               char **dbBuff, BinaryTreeNode *parent);
Errors writeTree (BinaryTree *tree, BinaryTreeNode *node, FILE *db);

Errors printTabs (FILE *db, size_t amount);
Errors readFileToBuffer (FILE *file, char **buffer);
Errors skipTabsSpaces (char **buffer);

Errors copyData (data_t* buff, data_t *readBuff, size_t amount);

#endif