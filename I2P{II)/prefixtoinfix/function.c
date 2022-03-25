#include "function.h"
#include <stdlib.h>
#include <stdio.h>

void printInfix(Node *root)
{
    if (root->left != NULL)
    {
        printInfix(root->left);
    }
    printf("%c", root->data);
    if (root->right != NULL)
    {
        if (root->right->data == '|' || root->right->data == '&')
        {
            printf("(");
        }
        printInfix(root->right);
        if (root->right->data == '|' || root->right->data == '&')
        {
            printf(")");
        }
    }
}