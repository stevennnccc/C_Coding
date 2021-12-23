#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3010

char t_string[MAX];
char s_string[MAX];
char every_substring[MAX][MAX];
char N_length_substring[MAX][MAX];
int correct_substring_alpha[MAX][27];
char ans[MAX][MAX];
int every_length;
int cnt;
int correct;
int print;
int flag;
int freq = 1;

int compare_char(const void *, const void *);

int main()
{
    int t_alpha[27] = {0};
    int s_alpha[27] = {0};
    int N;

    scanf("%s %d", t_string, &N);
    scanf("%s", s_string);

    int t_length = strlen(t_string);
    int s_length = strlen(s_string);

    for (int i = 'a'; i <= 'z'; i++)
        for (int j = 0; j < t_length; j++)
            if (i == t_string[j])
                t_alpha[i - 97]++; 

    for (int i = 'a'; i <= 'z'; i++)
        for (int j = 0; j < s_length; j++)
            if (i == s_string[j])
                s_alpha[i - 97]++; // 找出pattern的字母數量

    for (int i = 0; i < t_length; i++)
        for (int j = 0; j < N; j++)
            every_substring[i][j] = t_string[i + j]; // 把substrings找出來

    for (int i = 0; i < t_length; i++) {
        every_length = strlen(every_substring[i]); // 把長度為N的substrings找出來
        if (every_length == N) {
            strcpy(N_length_substring[i], every_substring[i]);
            cnt++;
        }
    }

    for (int j = 0; j < cnt; j++) // 找出長度為N的substrings的字母數量
        for (int k = 0; k < 3; k++)
            for (int i = 'a'; i <= 'z'; i++)
                if (i == N_length_substring[j][k]) {
                    correct_substring_alpha[j][i - 97]++;
                }

    for (int i = 0; i < cnt; i++) { // 比對pattern
        for (int j = 0; j < 26; j++)
        {
            if (correct_substring_alpha[i][j] == s_alpha[i])
            {
                correct++;
            }
            else
                break;
            if (correct == N)
            {
                strcpy(ans[i], N_length_substring[i]);
                correct = 0;
                print++;
                break;
            }
        }
    }

    printf("%d\n", print);
    
    for (int i = 0; i<print; i++) {
        printf("%s %d\n", ans[i], freq);
    }

}
