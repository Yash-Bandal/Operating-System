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

