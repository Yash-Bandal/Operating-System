#include <iostream>
#include <cstdlib>

using namespace std;

int binarySearch(int arr[], int n, int item) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == item) {
            return mid;
        }
        if (arr[mid] < item) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Not found
}

int main(int argc, char* argv[]) {
    int n = argc - 2; // Number of elements passed
    int* arr = new int[n];
    
    for (int i = 1; i <= n; i++) {
        arr[i - 1] = atoi(argv[i]); // Convert to integers
    }
    
    int item = atoi(argv[argc - 1]); // The item to search
    int result = binarySearch(arr, n, item);

    if (result != -1) {
        cout << "Element " << item << " found at index " << result << endl;
    } else {
        cout << "Element " << item << " not found" << endl;
    }

    delete[] arr;
    return 0;
}

----------
    C
    #include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid; // target found
        }
        if (arr[mid] < target) {
            left = mid + 1; // Search in the right half
        } else {
            right = mid - 1; // Search in the left half
        }
    }
    return -1; // Not found
}
//no scanf all pass in cmd
int main(int argc, char* argv[]) {
    int n = argc - 2; // Number of elements passed
    int* arr = (int*)malloc(n * sizeof(int)); // Dynamic array allocation

    // Convert command-line arguments to integers
    for (int i = 1; i <= n; i++) {
        arr[i - 1] = atoi(argv[i]);
    }

    int target = atoi(argv[argc - 1]); // The target to search
    int result = binarySearch(arr, n, target);

    if (result != -1) {
        printf("Element %d found at index %d\n", target, result);
    } else {
        printf("Element %d not found\n", target);
    }

    free(arr); // Free dynamically allocated memory
    return 0;
}
