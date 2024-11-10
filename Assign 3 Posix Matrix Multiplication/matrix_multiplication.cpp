#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 4 // Size of the matrices

int A[SIZE][SIZE] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
};

int B[SIZE][SIZE] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
};

int C[SIZE][SIZE]; // Result matrix

// Function to multiply a specific row
void* multiply_row(void* row) {
    int r = *((int*)row); // Get the row index
    for (int j = 0; j < SIZE; j++) {
        C[r][j] = 0; // Initialize the result cell
        for (int k = 0; k < SIZE; k++) {
            C[r][j] += A[r][k] * B[k][j]; // Perform multiplication
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[SIZE];
    int row_indices[SIZE]; // Array to hold row indices

    // Create threads for each row
    for (int i = 0; i < SIZE; i++) {
        row_indices[i] = i; // Assign row index
        pthread_create(&threads[i], NULL, multiply_row, &row_indices[i]); // Create thread
    }

    // Wait for all threads to complete
    for (int i = 0; i < SIZE; i++) {
        pthread_join(threads[i], NULL); // Wait for thread completion
    }

    // Print the result matrix
    printf("Result Matrix C:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}



//gedit matrix_multiplication.cpp
//g++ -o matrix_multiplication matrix_multiplication.cpp -pthread
//./matrix_multiplication

