#include "function.h"
#include <stdlib.h>

BTNode *EXPR()
{
    char c;
    BTNode *node = NULL, *right = NULL;

    if (pos >= 0)
    {
        right = FACTOR();
        if (pos > 0)
        { // 1. the EXPR OP ID case
            c = expr[pos];
            if (c == '&' || c == '|')
            {
                node = makeNode(c);
                node->right = right;
                pos--;
                node->left = EXPR();
            }
            else
                node = right; // 2. EXPR = ID
        }
        else
            node = right; // 2. EXPR = ID
    }
    return node;
}

BTNode *FACTOR()
{
    char c;
    BTNode *node = NULL;

    if (pos >= 0)
    {
        c = expr[pos--];
        if (c >= 'A' && c <= 'D')
        {
            node = makeNode(c);
        }
        else if (c == ')')
        {
            node = EXPR();
            if (expr[pos--] != '(')
            {
                printf("Error!\n");
                freeTree(node);
            }
        }
    }
    return node;
}

BTNode *makeNode(char c)
{
    int i;
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    for (i = 0; i < NUMSYM; i++)
        if (c == sym[i])
        {
            node->data = i;
            break;
        }
    node->left = NULL;
    node->right = NULL;
    return node;
}
