// Qsort is crazy!!!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int V_order[26];

int compare_char(const void *, const void *);

int compare_char_V(const void *, const void *);

int compare_char(const void *a, const void *b) {
    return strcmp(a, b);
}

int compare_char_V(const void *a, const void *b)
{
    const char *ca = (const char *) a;
    const char *cb = (const char *) b;

    if (V_order[*ca - 97] > V_order[*cb - 97])
        return 1;
    else if (V_order[*ca - 97] == V_order[*cb - 97])
        return 0;
    else
        return -1;

}

int main()
{
    int N;
    char S[101][7] = {0};
    char V[26];

    scanf("%d", &N);
    scanf("%s", V);

    for (int i = 'a'; i <= 'z'; i++)
        for (int j = 0; j < 26; j++)
            if (i == V[j])
                V_order[i - 97] = j;

    for (int i = 0; i < N; i++)
    {
        scanf("%s", S[i]);
        qsort(S[i], 6, sizeof(char), compare_char_V);
    }

    qsort(S, N, 7 * sizeof(char), compare_char);

    for (int i = 0; i < N; i++)
    {
        if (i == N - 1)
            printf("%s\n", S[i]);
        else
            printf("%s ", S[i]);
    }
}
