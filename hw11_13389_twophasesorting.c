// Using Qsort is really crazy!!!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_char(const void *, const void *);
int compare_2dchar(const void *, const void *);

int compare_char(const void *a, const void *b)
{
    const char *ca = (const char *)a;
    const char *cb = (const char *)b;
    return *ca - *cb;
}

int compare_2dchar(const void *a, const void *b)
{
    return strcmp(a, b);
}

int main()
{
    int N;
    char S[101][7] = {0};

    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%s", S[i]);
        qsort(S[i], 6, sizeof(char), compare_char); // Sorting internal strings
    }

    qsort(S, N, 7 * sizeof(char), compare_2dchar); // Sorting strings in different arrays

    for (int i = 0; i < N; i++)
    {

        if (i == N - 1)
        {
            printf("%s\n", S[i]);
        }
        else
            printf("%s ", S[i]);
    }
}
