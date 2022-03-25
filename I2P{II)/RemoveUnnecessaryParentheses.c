#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode
{
    char data;
    struct treeNode *left;
    struct treeNode *right;
} BTNode;

int pos;
char expr[256];
char sym[6] = "ABCD|&";

BTNode *makeNode(char c);
BTNode *EXPR();
BTNode *FACTOR();
void printTree(BTNode *root);

BTNode *makeNode(char c)
{
    int i;
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    for (i = 0; i < 6; i++)
    {
        if (c == sym[i])
        {
            node->data = sym[i];
            break;
        }
    }
    node->left = NULL;
    node->right = NULL;
    return node;
}

BTNode *EXPR()
{
    char c;
    BTNode *node = NULL, *right = NULL;

    if (pos >= 0)
    {
        right = FACTOR();
        if (pos > 0)
        {
            c = expr[pos];
            if (c == '&' || c == '|')
            {
                node = makeNode(c);
                node->right = right;
                pos--;
                node->left = EXPR();
            }
            else
            {
                node = right;
            }
        }
        else
        {
            node = right;
        }
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
                return NULL;
            }
        }
    }
    return node;
}

void printTree(BTNode *root)
{
    if (root->left != NULL)
    {
        printTree(root->left);
    }
    printf("%c", root->data);
    if (root->right != NULL)
    {
        if (root->right->data == '|' || root->right->data == '&')
        {
            printf("(");
        }
        printTree(root->right);
        if (root->right->data == '|' || root->right->data == '&')
        {
            printf(")");
        }
    }
}

int main()
{
    scanf("%s", expr);
    pos = strlen(expr) - 1;
    BTNode *root = EXPR();
    printTree(root);
    return 0;
}