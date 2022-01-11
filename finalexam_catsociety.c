#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[50];
    int occu;
    int age;
} cat;

int cat_cmp(const void *a, const void *b);

int main()
{
    int N, M;

    cat cats[10010];

    while (~scanf("%d%d", &N, &M))
    {
        for (int i = 0; i < N; i++)
        {
            char tmp[20];
            scanf("%s%s%d", cats[i].name, tmp, &cats[i].age);
            switch (tmp[0])
            {
            case 'e':
                cats[i].occu = 1;
                break;
            case 'k':
                cats[i].occu = 2;
                break;
            case 'a':
                cats[i].occu = 3;
                break;
            }
        }
        qsort(cats, N, sizeof(cat), cat_cmp);
        if (M > N)
        {
            for (int i = 0; i < N; i++)
            {
                printf("%s\n", cats[i].name);
            }
        }
        else
        {
            for (int i = 0; i < M; i++)
            {
                printf("%s\n", cats[i].name);
            }
        }
    }
}

int cat_cmp(const void *a, const void *b)
{
    cat *ca = (cat *)a;
    cat *cb = (cat *)b;

    if (ca->occu != cb->occu)
    {
        return ca->occu - cb->occu;
    }
    else
    {
        if (ca->age == cb->age)
        {
            return strcmp(ca->name, cb->name);
        }
        if (ca->occu == 3)
        {
            if (ca->age > cb->age)
            {
                return 1;
            }
            else if (ca->age < cb->age)
            {
                return -1;
            }
        }
        if (ca->occu != 3)
        {
            if (ca->age > cb->age)
            {
                return 1;
            }
            else if (ca->age < cb->age)
            {
                return -1;
            }
        }
    }
}
