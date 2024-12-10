#include <stdio.h>
#include <string.h>

typedef struct {
    int lcsLength;
    char lcsString[100];
} LCSResult;

LCSResult lcs(char *X, char *Y) {
    int m = strlen(X);
    int n = strlen(Y);
    int dp[m + 1][n + 1];
    char lcsResult[100];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
        }
    }

    int index = dp[m][n];
    lcsResult[index] = '\0'; 
    int i = m, j = n;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcsResult[--index] = X[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    LCSResult result;
    result.lcsLength = dp[m][n];
    strcpy(result.lcsString, lcsResult);
    return result;
}

void recommendWord(char *baseWord, char compareWords[][100], int compareCount) {
    char bestMatch[100];
    int maxLcsLength = 0;

    printf("기본 단어: %s\n", baseWord);
    printf("비교 결과:\n");

    for (int i = 0; i < compareCount; i++) {
        LCSResult result = lcs(baseWord, compareWords[i]);
        printf("단어: %s, LCS 길이: %d, LCS: %s\n", compareWords[i], result.lcsLength, result.lcsString);

        if (result.lcsLength > maxLcsLength) {
            maxLcsLength = result.lcsLength;
            strcpy(bestMatch, compareWords[i]);
        }
    }

    printf("\n추천: %s\n", bestMatch);
}

int main() {
    char samples[][3][100] = {
        {"intellagence", "intelligence", "intelligentsia"},
        {"accomodation", "accommodation", "accommodative"},
        {"enviroment", "environment", "environ"},
        {"managament", "management", "managing"},
        {"proffessor", "professor", "profession"}
    };

    int sampleCount = sizeof(samples) / sizeof(samples[0]);

    for (int i = 0; i < sampleCount; i++) {
        char *base = samples[i][0];
        char compareWords[2][100];
        strcpy(compareWords[0], samples[i][1]);
        strcpy(compareWords[1], samples[i][2]);

        printf("\n");
        recommendWord(base, compareWords, 2);
    }

    return 0;
}
