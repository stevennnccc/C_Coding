#include <stdio.h>
#include <stdbool.h>

int N, Q;
int left, right;
int start, end;
int tree[3000][3];
bool gone[3000];
bool is_root[3000];
bool arrive;
char path[3000];
int length;

void traverse(int now)
{
    if (arrive)
    {
        return;
    }
    if (now == end)
    {
        for (int i = 0; i < length; i++)
        {
            printf("%c", path[i]);
        }
        printf("\n");
        arrive = true;
        return;
    }
    gone[now - 1] = true;

    if (tree[now - 1][0] != 0 && gone[tree[now - 1][0] - 1] == false)
    {
        length++;
        path[length - 1] = 'P';
        traverse(tree[now - 1][0]);
        length--;
    }
    if (tree[now - 1][1] != 0 && gone[tree[now - 1][1] - 1] == false)
    {
        length++;
        path[length - 1] = 'L';
        traverse(tree[now - 1][1]);
        length--;
    }
    if (tree[now - 1][2] != 0 && gone[tree[now - 1][2] - 1] == false)
    {
        length++;
        path[length - 1] = 'R';
        traverse(tree[now - 1][2]);
        length--;
    }
}

int main()
{
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        gone[i] = false;
        is_root[i] = true;
    }

    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &left, &right);
        tree[right - 1][0] = tree[left - 1][0] = i + 1;
        tree[i][1] = left;
        tree[i][2] = right;
        is_root[left - 1] = is_root[right - 1] = false;
    }

    for (int i = 0; i < N; i++)
    {
        if (is_root[i] == true)
        {
            tree[i][0] = 0;
            break;
        }
    }

    scanf("%d", &Q);

    for (int i = 0; i < Q; i++)
    {
        scanf("%d %d", &start, &end);
        length = 0;
        arrive = false;
        traverse(start);
        for (int j = 0; j < N; j++)
        {
            gone[j] = false;
        }
    }
}