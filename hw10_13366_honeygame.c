#include <stdio.h>
#include <stdlib.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))

int T;
int N, A, B;
char name[7];
int step;
int total;

int main()
{
    scanf("%d", &T);

    while (T--)
    {
        scanf("%d %d %d %s", &N, &A, &B, name);

        step = max(A, B);

        total = 1 + step;

        if (name[2] == 'o')
        {
            if (A > N)
            {
                printf("Pooh\n");
            }
            else if (A != B)
            {
                if (A > B)
                {
                    printf("Pooh\n");
                }
                else
                {
                    printf("Piglet\n");
                }
            }
            else if (A == B)
            {
                if (N % (A+1) != 0)
                {
                    printf("Pooh\n");
                }
                else
                {
                    printf("Piglet\n");
                }
            }
        }
        else
        {
            if (B > N)
            {
                printf("Piglet\n");
            }
            else if (A != B)
            {
                if (A > B)
                {
                    printf("Pooh\n");
                }
                else
                {
                    printf("Piglet\n");
                }
            }
            else if (A == B)
            {
                if (N % (A+1) != 0)
                {
                    printf("Piglet\n");
                }
                else
                {
                    printf("Pooh\n");
                }
            }
        }
    }
}
