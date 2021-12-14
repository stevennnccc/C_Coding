#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void solver(char **ptr, int *n, int P, char *M)
{
#define maxn 1000
#define maxl 1000

    int length[maxn];
    int moded[maxn];
    int g = 0;
    int k = 0;
    int temp;
    int acum = 0;
    int flag;
    memset(moded, -1, maxn);

    for (int i = 0; i < maxn; i++)
    {
        if (isdigit(M[i]))
        {
            temp = M[i] - '0';
        }
        if (isalpha(M[i]))
        {
            length[temp] += 1;
        }
        if (M[i] == '\0')
        {
            break;
        }
    }
    for (int i = 0; i < maxn; i++)
    {
        flag = 1;
        if (isdigit(M[i]))
        {
            for (int j = 0; j < k + 1; j++)
            {
                if (moded[j] == M[i] % P)
                {
                    strncat(ptr[moded[j]], M + acum + 1, length[(M[i] - '0')]);
                    /*begin[(M[i] - '0') % P] += (length[moded[j]] + 1);
                    for (int k = begin[(M[i] - '0') % P]; k < length[(M[i] - '0')] + begin; k++)
                    {
                        ptr[(M[i] - '0') % P][k] = M[acum + 1];
                    }*/
                    acum += length[(M[i] - '0')] + 1;
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
            {
                strncat(ptr[(M[i] - '0') % P], M + acum + 1, length[(M[i] - '0')]);
                /*int t = 0;
                for (int g = acum; g < length[(M[i] - '0')] + acum; g++)
                {
                    ptr[(M[i] - '0') % P][t] = M[g + 1];
                    t++;
                }*/
                *n += 1;
                acum += length[(M[i] - '0')] + 1;
            }

            moded[k] = (M[i] - '0') % P;
            k++;
        }

        if (M[i] == '\0')
        {
            break;
        }
    }
}
