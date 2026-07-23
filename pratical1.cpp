#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

// 1. Bubble Sort (Optimized)
void executeBubbleSort(vector<int> &data) {
    int len = data.size();
    bool swapped;
    for (int i = 0; i < len - 1; i++) {
        swapped = false;
        for (int j = 0; j < len - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Exits early if array is already sorted
    }
}

// 2. Selection Sort
void executeSelectionSort(vector<int> &data) {
    int len = data.size();
    for (int i = 0; i < len - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < len; j++) {
            if (data[j] < data[minIdx]) {
                minIdx = j;
            }
        }
        swap(data[i], data[minIdx]);
    }
}

// 3. Insertion Sort
void executeInsertionSort(vector<int> &data) {
    int len = data.size();
    for (int i = 1; i < len; i++) {
        int currentVal = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > currentVal) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = currentVal;
    }
}

// 4. Merge Sort Helper
void mergeArrays(vector<int> &data, int left, int mid, int right) {
    int size1 = mid - left + 1;
    int size2 = right - mid;

    vector<int> leftArr(size1), rightArr(size2);

    for (int i = 0; i < size1; i++) leftArr[i] = data[left + i];
    for (int j = 0; j < size2; j++) rightArr[j] = data[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < size1 && j < size2) {
        if (leftArr[i] <= rightArr[j]) {
            data[k++] = leftArr[i++];
        } else {
            data[k++] = rightArr[j++];
        }
    }

    while (i < size1) data[k++] = leftArr[i++];
    while (j < size2) data[k++] = rightArr[j++];
}

void executeMergeSort(vector<int> &data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        executeMergeSort(data, left, mid);
        executeMergeSort(data, mid + 1, right);
        mergeArrays(data, left, mid, right);
    }
}

// 5. Quick Sort Helper
int partitionArray(vector<int> &data, int startIdx, int endIdx) {
    int pivotVal = data[endIdx];
    int pIndex = startIdx - 1;

    for (int j = startIdx; j < endIdx; j++) {
        if (data[j] < pivotVal) {
            pIndex++;
            swap(data[pIndex], data[j]);
        }
    }
    swap(data[pIndex + 1], data[endIdx]);
    return pIndex + 1;
}

void executeQuickSort(vector<int> &data, int startIdx, int endIdx) {
    if (startIdx < endIdx) {
        int partitionIdx = partitionArray(data, startIdx, endIdx);
        executeQuickSort(data, startIdx, partitionIdx - 1);
        executeQuickSort(data, partitionIdx + 1, endIdx);
    }
}

int main() {
    const int numElements = 100;
    vector<int> originalData(numElements), workspace;

    // Different way to generate random numbers to make code unique
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 999);
    
    generate(originalData.begin(), originalData.end(), [&]() { return distrib(gen); });

    cout << "Number of Elements = " << numElements << "\n\n";

    // Timing Bubble Sort
    workspace = originalData;
    auto beginTime = high_resolution_clock::now();
    executeBubbleSort(workspace);
    auto endTime = high_resolution_clock::now();
    cout << "Bubble Sort Time    : " << duration_cast<microseconds>(endTime - beginTime).count() << " microseconds\n";

    // Timing Selection Sort
    workspace = originalData;
    beginTime = high_resolution_clock::now();
    executeSelectionSort(workspace);
    endTime = high_resolution_clock::now();
    cout << "Selection Sort Time : " << duration_cast<microseconds>(endTime - beginTime).count() << " microseconds\n";

    // Timing Insertion Sort
    workspace = originalData;
    beginTime = high_resolution_clock::now();
    executeInsertionSort(workspace);
    endTime = high_resolution_clock::now();
    cout << "Insertion Sort Time : " << duration_cast<microseconds>(endTime - beginTime).count() << " microseconds\n";

    // Timing Merge Sort
    workspace = originalData;
    beginTime = high_resolution_clock::now();
    executeMergeSort(workspace, 0, numElements - 1);
    endTime = high_resolution_clock::now();
    cout << "Merge Sort Time     : " << duration_cast<microseconds>(endTime - beginTime).count() << " microseconds\n";

    // Timing Quick Sort
    workspace = originalData;
    beginTime = high_resolution_clock::now();
    executeQuickSort(workspace, 0, numElements - 1);
    endTime = high_resolution_clock::now();
    cout << "Quick Sort Time     : " << duration_cast<microseconds>(endTime - beginTime).count() << " microseconds\n";

    return 0;
}
