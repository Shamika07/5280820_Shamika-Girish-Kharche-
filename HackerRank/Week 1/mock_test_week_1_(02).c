#include <stdio.h>
#include <stdlib.h> // For malloc and free
#include <math.h>   // For fmax

// Function to find the maximum of four integers
int findMax(int a, int b, int c, int d) {
    return fmax(fmax(a, b), fmax(c, d));
}

// Function to calculate the maximum sum of the upper-left quadrant
long long flippingMatrix(int** matrix, int n) {
    long long maxSum = 0;
    int size = 2 * n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Consider the four symmetric positions
            int val1 = matrix[i][j];
            int val2 = matrix[i][size - 1 - j];
            int val3 = matrix[size - 1 - i][j];
            int val4 = matrix[size - 1 - i][size - 1 - j];

            // Add the maximum of these four to the sum
            maxSum += findMax(val1, val2, val3, val4);
        }
    }
    return maxSum;
}

int main() {
    // Example usage with a 2x2 matrix (n=1, so size=2)
    int n = 1;
    int size = 2 * n;

    // Dynamically allocate a 2D array for the matrix
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }

    // Initialize the example matrix: [[1, 2], [3, 4]]
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[1][0] = 3;
    matrix[1][1] = 4;

    long long result = flippingMatrix(matrix, n);
    printf("Maximum sum of the upper-left quadrant: %lld\n", result); // Expected: 4

    // Free the dynamically allocated memory
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);

    // Another example with n=2 (4x4 matrix)
    n = 2;
    size = 2 * n;
    int** matrix2 = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix2[i] = (int*)malloc(size * sizeof(int));
    }

    // Example 4x4 matrix (replace with your test data)
    matrix2[0][0] = 1; matrix2[0][1] = 2; matrix2[0][2] = 3; matrix2[0][3] = 4;
    matrix2[1][0] = 5; matrix2[1][1] = 6; matrix2[1][2] = 7; matrix2[1][3] = 8;
    matrix2[2][0] = 9; matrix2[2][1] = 10; matrix2[2][2] = 11; matrix2[2][3] = 12;
    matrix2[3][0] = 13; matrix2[3][1] = 14; matrix2[3][2] = 15; matrix2[3][3] = 16;

    long long result2 = flippingMatrix(matrix2, n);
    printf("Maximum sum of the upper-left quadrant (for n=2): %lld\n", result2); // Example value

    // Free memory for the second matrix
    for (int i = 0; i < size; i++) {
        free(matrix2[i]);
    }
    free(matrix2);

    return 0;
}