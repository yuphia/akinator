#ifndef DRAWTREE_CPP
#define DRAWTREE_CPP 1

#include "drawTree.hpp"

FILE *setupDot()
{
    FILE *dotFile = fopen ("dotDraw/tree.dot", "w");

    fprintf (dotFile, "digraph G{\n");
    fprintf (dotFile, "rankdir=HR;\n");
    fprintf (dotFile, "node [shape=\"record\", fontsize=14, style=\"filled\", fillcolor=\"#ffff94\"];\n");
    fprintf (dotFile, "edge [color=\"black\", fontcolor=\"black\", fontsize=12];\n\n\n");

    return dotFile;
}

void closeDot (FILE *dotFile)
{
    fclose (dotFile);
}

void drawRoot (const BinaryTree *tree)
{
    assert (tree);
    FILE* dotFile = setupDot();

    fprintf(dotFile, "root [shape=\"octagon\", fontsize=20, fontcolor=\"black\", style=\"filled\", fillcolor=\"#ffb0aa\", label=\"Tree\"];\n NumberOfElements = %zu\n", 
                   tree->amountOfElements);

    fprintf(dotFile, "root->elem%p:<d>;\n", tree->root);
    drawNode (dotFile, tree->root);

    fprintf (dotFile, "\n}\n");

    closeDot (dotFile);
}

void drawNode (FILE *dotFile, const BinaryTreeNode *node)
{
    assert (dotFile);
    assert (node);

    if (node->lChild == nullptr && node->rChild == nullptr)
    {
        fprintf(dotFile, "elem%p [label=\"<d> %s\"];\n", node, node->data);
        return;   
    }

    if (node->lChild != nullptr && node->rChild == nullptr)
    {
        fprintf(dotFile, "elem%p [label=\"<YES> YES | <d> %s | <NO> NO \"];\n", node, node->data);
      
        fprintf(dotFile, "elem%p:<YES>-> elem%p:<d>;\n", node, node->lChild);
        drawNode (dotFile, node->lChild);
    }

    if (node->lChild == nullptr && node->rChild != nullptr)
    {
        fprintf(dotFile, "elem%p [label=\"<YES> YES | <d> %s | <NO> NO \"];\n", node, node->data);
        fprintf(dotFile, "elem%p:<NO>-> elem%p:<d>;\n", node, node->rChild);
        drawNode (dotFile, node->rChild);
    }

    if (node->lChild != nullptr && node->rChild != nullptr)
    {
        fprintf(dotFile, "elem%p [label=\"<YES> YES | <d> %s | <NO> NO \"];\n", node, node->data);
        fprintf(dotFile, "elem%p:<YES>->elem%p:<d>;\n", node, node->lChild);
        fprintf(dotFile, "elem%p:<NO>->elem%p:<d>;\n", node, node->rChild);
        drawNode (dotFile, node->lChild);
        drawNode (dotFile, node->rChild);
    }
}


#endif