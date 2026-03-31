#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <Windows.h>
#include <Psapi.h>
#include <ctime>

using namespace std;

void printMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memInfo;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
        cout << memInfo.WorkingSetSize / 1024 << " KB" << endl;
    }
}

void insertionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void quickSort(vector<int> arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[left] > arr[mid]) swap(arr[left], arr[mid]);
        if (arr[left] > arr[right]) swap(arr[left], arr[right]);
        if (arr[mid] > arr[right]) swap(arr[mid], arr[right]);

        int pivot = arr[mid];
        int i = left;
        int j = right;

        while (i <= j) {
            while (arr[i] < pivot) i++;
            while (arr[j] > pivot) j--;
            if (i <= j) {
                swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }
        if (left < j) quickSort(arr, left, j);
        if (i < right) quickSort(arr, i, right);
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void iterativeMergeSort(vector<int> arr) {
    int n = arr.size();
    for (int curr_size = 1; curr_size < n; curr_size = 2 * curr_size) {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = min(left_start + curr_size - 1, n - 1);
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);
            merge(arr, left_start, mid, right_end);
        }
    }
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int> arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void compositeSort(vector<int> arr) {
    if (arr.size() < 16) {
        insertionSort(arr);
    }
    else {
        quickSort(arr, 0, arr.size() - 1);
    }
}

int main() {
    srand((unsigned)time(NULL));
    int test_sizes[] = { 500, 1000, 2000, 3000, 4000, 5000 };

    for (int n : test_sizes) {
        vector<int> data;
        for (int i = 0; i < n; i++) {
            data.push_back(rand() % 10000);
        }

        cout << "N = " << n << endl;
        cout << "Memory Before: ";
        printMemoryUsage();

        auto start_time = chrono::high_resolution_clock::now();
        heapSort(data);
        auto end_time = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

        cout << "Time: " << duration.count() << " us" << endl;
        cout << "Memory After: ";
        printMemoryUsage();
        cout << "--------------------------------" << endl;
    }

    return 0;
}
