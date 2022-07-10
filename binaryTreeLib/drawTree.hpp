#ifndef DRAWTREE_HPP
#define DRAWTREE_HPP 1

#include "tree.hpp"
#include "../errDetect/err.h"

FILE *setupDot();
void closeDot (FILE *dotFile);

void drawRoot (const BinaryTree *tree);
void drawNode (FILE *dotFile, const BinaryTreeNode *node);

#endif