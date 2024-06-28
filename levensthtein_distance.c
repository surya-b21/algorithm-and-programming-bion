#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    char word1[100];
    char word2[100];

    printf("Please insert word 1 : ");
    scanf("%s", &word1);

    printf("Please insert word 2 : ");
    scanf("%s", &word2);

    printf("Levenshtein Distance : %d", LevenshteinDistance(&word1, &word2));
}

int LevenshteinDistance(char * s, char * t)
{
    int m = strlen(s);
    int n = strlen(t);

    int *d[m + 1];
    for (int i = 0; i <= m; i++) {
        d[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i <= m; i++) {
        d[i][0] = i;
    }

    for (int j = 0; j <= n; j++) {
        d[0][j] = j;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int substitutionCost = (s[i-1] == t[j-1]) ? 0 : 1;
            d[i][j] = fmin(d[i-1][j] + 1 < d[i][j-1] + 1 ? d[i-1][j] + 1 : d[i][j - 1] + 1, d[i-1][j - 1] + substitutionCost);
        }
    }

    for (int i = 0; i <= m; i++)
        free(d[i]);

    return d[m][n];
}