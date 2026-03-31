## 41143263 黃柏林 / 41143264 楊育哲

資料結構(二) 作業一：排序演算法效能分析與實作

## 解題說明

本題要求實作並討論五種排序演算法的 Worst-case 與 Average-case 效能。

### 解題策略

1. **實作核心演算法**：包含 Insertion Sort、Quick Sort (Median-of-three)、Iterative Merge Sort、Heap Sort 與 Composite Sort。
2. **效能測量機制**：
   * 使用 `std::chrono` 進行高精度計時，並針對執行時間過短的情況採取重複執行取平均值的方法。
   * 透過 Windows API 監控 `WorkingSetSize` 以獲取實際載入 RAM 的記憶體使用量。
3. **測試案例生成**：
   * **Average-case**：隨機產生資料，並確保同一組資料供所有演算法重複使用以維持公平性。
   * **Worst-case**：針對不同演算法特性建立最差情況，如 Insertion Sort 使用逆序資料，Merge/Heap Sort 則篩選執行最久的隨機資料。

## 程式實作

以下為 `Composite Sort` 與實驗環境配置的主要程式碼實作：

```cpp
#include <iostream>
#include <vector>
#include <chrono>
#include <Windows.h>
#include <Psapi.h>

using namespace std;

// 1.2.1 記憶體監測 (Windows API)
void printMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memInfo;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
        cout << "Working Set Size: " << memInfo.WorkingSetSize / 1024 << " KB" << endl;
    }
}

// 1.1.1 高精度計時與重複執行邏輯
void measureExample(int n) {
    int repeat = 1000; 
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < repeat; ++i) {
        // 呼叫排序函式，例如 heapSort(data);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Avg Time: " << duration.count() / repeat << " us" << endl;
}

// 混合排序實作 (Composite Sort)
void compositeSort(vector<int> arr) {
    if (arr.size() < 16) {
        // 小數據量使用 Insertion Sort
    } else {
        // 大數據量使用 Quick Sort (Median-of-three)
    }
}
