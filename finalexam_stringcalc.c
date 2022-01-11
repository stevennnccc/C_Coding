#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int N;
    int len1, len2;
    int len;
    char *ans;
    char *tmp;
    char op;
    char str1[11] = {0};
    char str2[11] = {0};
    char *pos;

    scanf("%d", &N);

    while (N--)
    {
        scanf("%s %c %s", str1, &op, str2);
        len1 = strlen(str1);
        len2 = strlen(str2);
        if (op == '+')
        {
            len = len1 + len2;
            ans = (char *)malloc(sizeof(char) * (len + 1));
            strcpy(ans, str1);
            strcat(ans, str2);
            printf("%s\n", ans);
            free(ans);
        }
        if (op == '-')
        {
            pos = strstr(str1, str2);
            if (pos != NULL)
            {
                ans = (char *)malloc(sizeof(char) * (len1 + 1));
                ans[0] = '\0';
                int posn = strlen(pos);
                for (int i = 0; i < len1 - posn; i++)
                {
                    ans[i] = str1[i];
                }
                ans[len1 - posn] = '\0';
                strcat(ans, pos + len2);
                printf("%s\n", ans);
                free(ans);
            }
            else
                printf("error\n");
        }
        if (op == '/')
        {
            int correct = 0;
            int cnt = 0;
            for (int i = 0; i < len1; i++)
            {
                for (int j = 0; j < len2; j++)
                {
                    if (str1[i] == str2[j])
                    {
                        correct++;
                        if (correct == len2-1)
                            cnt++;
                            correct = 0;
                    }
                }
            }
            printf("%d\n", cnt);
        }
    }
}
