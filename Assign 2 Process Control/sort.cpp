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
