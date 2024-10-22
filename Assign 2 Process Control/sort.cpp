#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <cstdlib>

using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    cout << "Enter number of integers: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter integers:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return EXIT_FAILURE;
    } else if (pid == 0) { // Child process
        cout << "Child process (Quick Sort):\n";
        quickSort(arr, 0, n - 1);
        cout << "Sorted by Quick Sort:\n";
        for (int num : arr) {
            cout << num << " ";
        }
        cout << "\n";
        exit(0); // Child exits after sorting
    } else { // Parent process
        cout << "Parent process (Merge Sort):\n";
        mergeSort(arr, 0, n - 1);
        cout << "Sorted by Merge Sort:\n";
        for (int num : arr) {
            cout << num << " ";
        }
        cout << "\n";

        // Wait for the child process to finish
        wait(nullptr);
        cout << "Child process has finished.\n";

        // To demonstrate zombie state, uncomment the next line
        // sleep(10);
    }

    return 0;
}

//g++ -o sort sort.cpp
//g++ -o search search.cpp
//./sort





C
#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    printf("Enter number of integers: ");
    scanf("%d", &n);
    int* arr = (int*)malloc(n * sizeof(int));
    printf("Enter integers:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Sorting using Quick Sort:\n");
    int* arrQuick = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arrQuick[i] = arr[i]; // Copy original array
    }
    quickSort(arrQuick, 0, n - 1);
    printf("Sorted by Quick Sort:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arrQuick[i]);
    }
    printf("\n");

    printf("Sorting using Merge Sort:\n");
    mergeSort(arr, 0, n - 1);
    printf("Sorted by Merge Sort:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    free(arrQuick);
    return 0;
}

