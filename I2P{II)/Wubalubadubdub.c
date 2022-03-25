#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode
{
    int key;
    struct TreeNode *left, *right;
} Node;

int postOrder[200000];
Node *origin;

Node *makeNode(int key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int binarySearch(int start, int end, int find)
{
    int m;
    while (1)
    {
        if ((end - start) == 1)
            return start;
        m = start + (end - start) / 2;
        if (postOrder[m] > find)
        {
            if (postOrder[m - 1] < find)
                return m;
            else
                end = m;
        }
        else
            start = m;
    }
}

Node *constructTree(int start, int end)
{
    // Base Case
    if (end <= start)
    {
        return NULL;
    }

    Node *node = makeNode(postOrder[end - 1]);

    int split = binarySearch(start, end, node->key);

    node->right = constructTree(split, end - 1);
    node->left = constructTree(start, split);

    return node;
}

void printPreOrder(Node *root)
{
    if (root == NULL)
        return;
    if (root != origin)
        printf(" ");
    printf("%d", root->key);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

int main()
{
    int k = 0;
    int input = 0;

    while (~scanf("%d", &input))
    {
        postOrder[k++] = input;
    }
    Node *root = constructTree(0, k);
    origin = root;
    printPreOrder(root);
    printf("\n");
    return 0;
}