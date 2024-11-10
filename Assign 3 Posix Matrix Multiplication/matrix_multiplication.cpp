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
    for (int i = 0; i < SIZE; i++) {
        C[r][i] = 0; // Initialize the result cell
        for (int j = 0; j < SIZE; j++) {
            C[r][i] += A[r][j] * B[j][i]; // Perform multiplication
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

---------------------------
    #include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 100 // Define maximum size for the matrix

struct MatrixData {
    int (*a)[MAX_SIZE]; // Pointer to first matrix
    int (*b)[MAX_SIZE]; // Pointer to second matrix
    int (*result)[MAX_SIZE]; // Pointer to result matrix
    int row; // Row index for the thread
    int n; // Size of the matrix
};

// Thread function for matrix multiplication
void* multiply(void* arg) {
    struct MatrixData* data = (struct MatrixData*)arg;
    int row = data->row;
    int n = data->n;

    for (int j = 0; j < n; j++) {
        data->result[row][j] = 0; // Initialize result cell
        for (int k = 0; k < n; k++) {
            data->result[row][j] += data->a[row][k] * data->b[k][j];
        }
    }

    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Enter the size of the matrices (n x n): ");
    scanf("%d", &n);

    if (n > MAX_SIZE) {
        printf("Error: Maximum matrix size exceeded.\n");
        return 1;
    }

    int a[MAX_SIZE][MAX_SIZE];
    int b[MAX_SIZE][MAX_SIZE];
    int result[MAX_SIZE][MAX_SIZE] = {0};

    // Read matrix A
    printf("Enter matrix A (row-wise):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // Read matrix B
    printf("Enter matrix B (row-wise):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    pthread_t threads[n];
    struct MatrixData matrixData[n];

    // Create threads for each row of the result matrix
    for (int i = 0; i < n; i++) {
        matrixData[i].a = a;
        matrixData[i].b = b;
        matrixData[i].result = result;
        matrixData[i].row = i;
        matrixData[i].n = n;
        pthread_create(&threads[i], NULL, multiply, (void*)&matrixData[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    // Display the result
    printf("Result matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}

// To compile: g++ -o matrix_multiplication matrix_multiplication.c -pthread
// To run: ./matrix_multiplication
