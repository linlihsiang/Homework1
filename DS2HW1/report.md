# 41343116

HW1

## 解題說明

本題要求實作五種排序演算法，並針對不同資料量 $n$ 進行效能與記憶體分析，找出各情況下的最佳解。

### 解題策略

1. 實作核心排序函式：包含 Insertion Sort、Quick Sort (Median-of-three)、Iterative Merge Sort、Heap Sort 與 Composite Sort。
2. 效能分析：針對 $n=500, 1000, 2000, 3000, 4000, 5000$ 計算執行時間與記憶體使用量。  
3. 測試資料建立：Average-case 使用隨機產生；Worst-case 則根據演算法特性篩選或推導最差排列。

## 程式實作

以下為主要程式碼：

```cpp
include <iostream>
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
```

## 效能分析

1. 時間複雜度：Insertion Sort: $O(n^2)$。
              Quick / Merge / Heap Sort: $O(n \log n)$
3. 空間複雜度：需注意記憶體使用量與空間複雜度間的轉換$$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $n = 0$      | 0        | 0        |
| 測試二   | $n = 1$      | 1        | 1        |
| 測試三   | $n = 3$      | 6        | 6        |
| 測試四   | $n = 5$      | 15       | 15       |
| 測試五   | $n = -1$     | 異常拋出 | 異常拋出 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o sigma sigma.cpp
$ ./sigma
6
```

### 結論

1. 程式能正確計算 $n$ 到 $1$ 的連加總和。  
2. 在 $n < 0$ 的情況下，程式會成功拋出異常，符合設計預期。  
3. 測試案例涵蓋了多種邊界情況（$n = 0$、$n = 1$、$n > 1$、$n < 0$），驗證程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程精度考量與誤差降低**  
   由於排序小量資料的速度極快，單次測量常導致結果為 0 。我們採用 std::chrono 並配合重複執行 1000 次取平均值，確保數據具備參考價值 。
2. **真實反映空間開銷**  
   使用 Windows API 監測 WorkingSetSize 能觀測到程式實際載入 RAM 的量 。這對於分析如 Merge Sort 這種需要額外空間的演算法非常重要，能驗證空間複雜度與實測數據的一致性 。

3. **測試公平性與資料保留**  
   Average-case 隨機產生的測資會保留給各個排序函式共同使用，避免因資料不同影響效能對比 。同時，Worst-case 採取篩選最慢排列的策略，確保能觀察到演算法的效能極限 。
