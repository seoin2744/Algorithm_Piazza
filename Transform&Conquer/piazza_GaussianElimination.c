#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 4 

void gaussianElimination(double matrix[N][N], double vector[N], double result[N]) {
    double augmented[N][N + 1]; 

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            augmented[i][j] = matrix[i][j];
        }
        augmented[i][N] = vector[i];
    }

    for (int i = 0; i < N; i++) {
        int maxRow = i;
        for (int k = i + 1; k < N; k++) {
            if (fabs(augmented[k][i]) > fabs(augmented[maxRow][i])) {
                maxRow = k;
            }
        }

        for (int k = 0; k <= N; k++) {
            double temp = augmented[i][k];
            augmented[i][k] = augmented[maxRow][k];
            augmented[maxRow][k] = temp;
        }

        for (int j = i + 1; j < N; j++) {
            double factor = augmented[j][i] / augmented[i][i];
            for (int k = i; k <= N; k++) {
                augmented[j][k] -= factor * augmented[i][k];
            }
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        result[i] = augmented[i][N];
        for (int j = i + 1; j < N; j++) {
            result[i] -= augmented[i][j] * result[j];
        }
        result[i] /= augmented[i][i];
    }
}

void print(double matrix[N][N + 1]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N; j++) {
            printf("%8.3f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printSolution(double result[N]) {
    printf("Solution:\n");
    for (int i = 0; i < N; i++) {
        printf("x%d = %.2f\n", i + 1, result[i]);
    }
}

int main() {
    double matrix[N][N] = {
        {2, -2, -4, 2},
        {-3, 5, 8, 3},
        {2, -1, -5, 5},
        {1, 1, 1, 3}
    };

    double vector[N] = {-2, 7, 4, 2};
    double result[N];

    gaussianElimination(matrix, vector, result);

    print(result);
    return 0;
}
