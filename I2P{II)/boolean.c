// Prefix Boolean expression
#include <stdio.h>
#include <stdlib.h>

char expr[256];

typedef struct TreeNode
{
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} Node;

Node *makeNode(char c)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = c;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *build()
{
    static int pos = 0;
    Node *node;
    if (expr[pos] == '|' || expr[pos] == '&')
    {
        node = makeNode(expr[pos++]);
        node->left = build();
        node->right = build();
    }
    else
    {
        node = makeNode(expr[pos++]);
    }
    return node;
}

int solve(Node *node, int num)
{
    // if node->data == OP: ans = node->left OP node->right.
    // if node->data == ID: ans = the value of the ID
    if (node->data == '&')
        return solve(node->left, num) & solve(node->right, num);
    if (node->data == '|')
        return solve(node->left, num) | solve(node->right, num);
    else
        return (num >> (3 - (node->data - 'A'))) & 1;
}

int main()
{
    gets(expr);
    Node *root = build();
    for (int i = 0; i < 16; i++)
    {
        printf("%d %d %d %d ", (i >> 3) & 1, (i >> 2) & 1, (i >> 1) & 1, i & 1);
        printf("%d\n", solve(root, i));
    }
    return 0;
}