#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

struct MatrixData {
    const vector<vector<int>>* a; // Pointer to first matrix
    const vector<vector<int>>* b; // Pointer to second matrix
    vector<vector<int>>* result;   // Pointer to result matrix
    int row;                        // Row index for the thread
    int n;                          // Size of the matrix
};

void* multiply(void* arg) {
    MatrixData* data = (MatrixData*)arg;
    int row = data->row;
    int n = data->n;

    for (int j = 0; j < n; j++) {
        (*data->result)[row][j] = 0; // Initialize result cell
        for (int k = 0; k < n; k++) {
            (*data->result)[row][j] += (*data->a)[row][k] * (*data->b)[k][j];
        }
    }

    pthread_exit(nullptr);
}

int main() {
    int n;

    cout << "Enter the size of the matrices (n x n): ";
    cin >> n;

    // Initialize matrices
    vector<vector<int>> a(n, vector<int>(n));
    vector<vector<int>> b(n, vector<int>(n));
    vector<vector<int>> result(n, vector<int>(n, 0));

    cout << "Enter matrix A (row-wise):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    cout << "Enter matrix B (row-wise):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> b[i][j];
        }
    }

    // Create threads
    pthread_t threads[n];
    MatrixData matrixData[n];

    for (int i = 0; i < n; i++) {
        // Assign data to the struct
        matrixData[i] = {&a, &b, &result, i, n};
        pthread_create(&threads[i], nullptr, multiply, (void*)&matrixData[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], nullptr);
    }

    // Display the result
    cout << "Result matrix:\n";
    for (const auto& row : result) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }

    return 0;
}

//gedit matrix_multiplication.cpp
//g++ -o matrix_multiplication matrix_multiplication.cpp -pthread
//./matrix_multiplication

