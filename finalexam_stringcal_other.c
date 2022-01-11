#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char arr1[1001];
char arr2[100001];
char operator;
int k;
int h;
int l;
int flag;
int temp;

typedef struct
{
    char list_form[20];
    int length_arr;
} listed;

listed store[100001];

int cmp(const void *a, const void *b)
{
    listed as = *(listed *)a;
    listed bs = *(listed *)b;
    if (as.length_arr != bs.length_arr)
    {
        return (as.length_arr - bs.length_arr) * -1;
    }
    else
    {
        return strcmp(as.list_form, bs.list_form);
    }
}

void plus(char *a, char *b)
{
    strcat(a, b);
}

void minus(char *a, char *b)
{
    char *pos = strstr(a, b);
    if (pos != NULL)
    {
        char *ans = (char *)malloc(sizeof(char) * (strlen(a) + 1));
        ans[0] = '\0';
        int posn = strlen(pos);
        for (int i = 0; i < strlen(a) - posn; i++)
        {
            ans[i] = a[i];
        }
        ans[strlen(a) - posn] = '\0';
        strcat(ans, pos + strlen(b));
        printf("%s\n", ans);
        free(ans);
    }
    else
        printf("error\n");
}

void divide(char *a, char *b)
{
    int cnt = 0;
    char *pointer = strstr(a, b);
    int length = strlen(b);
    while (pointer != NULL)
    {
        cnt++;
        pointer = strstr(pointer + length, b);
    }
    printf("%d\n", cnt);
}

void list(char *a, char *b)
{
    char *pointer = strtok(b, "_");
    while (pointer != NULL)
    {
        if (strstr(pointer, a) != NULL)
        {
            strcpy(store[h].list_form, pointer);
            store[h].length_arr = strlen(pointer);
            h++;
        }
        pointer = strtok(NULL, "_");
    }
    qsort(store, h, sizeof(listed), cmp);
    int flag = 0;
    for (int i = 0; i < h; i++)
    {
        if (flag == 0)
        {
            printf("%s", store[i].list_form);
            flag = 1;
            continue;
        }
        if (flag == 1)
        {
            printf(" %s", store[i].list_form);
        }
    }
    printf("\n");
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", arr1);
        scanf(" %c", &operator);
        scanf("%s", arr2);
        switch (operator)
        {
        case '+':
            plus(arr1, arr2);
            printf("%s\n", arr1);
            break;
        case '-':
            minus(arr1, arr2);
            break;
        case '/':
            divide(arr1, arr2);
            break;
        case '@':
            list(arr1, arr2);
            break;
        default:
            break;
        }
    }
}
