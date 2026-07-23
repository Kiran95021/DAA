#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>

using namespace std;
using namespace std::chrono;

// Linear Search Implementation
int performLinearSearch(const vector<int>& data, int targetVal) {
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] == targetVal) {
            return i;
        }
    }
    return -1;
}

// Binary Search Implementation
int performBinarySearch(const vector<int>& data, int targetVal) {
    int startIdx = 0;
    int endIdx = data.size() - 1;

    while (startIdx <= endIdx) {
        int midIdx = startIdx + (endIdx - startIdx) / 2;

        if (data[midIdx] == targetVal) {
            return midIdx;
        } else if (data[midIdx] < targetVal) {
            startIdx = midIdx + 1;
        } else {
            endIdx = midIdx - 1;
        }
    }
    return -1;
}

int main() {
    int totalElements = 100000;
    vector<int> sortedData(totalElements);

    // Using iota to fill the array with 1, 2, 3... up to totalElements
    iota(sortedData.begin(), sortedData.end(), 1);

    int target;
    cout << "Enter element to search: ";
    cin >> target;

    int resultIndex;

    // Timing for Linear Search
    auto beginTime = high_resolution_clock::now();
    resultIndex = performLinearSearch(sortedData, target);
    auto endTime = high_resolution_clock::now();

    cout << "\nLinear Search\n";
    if (resultIndex != -1)
        cout << "Element found at index " << resultIndex << "\n";
    else
        cout << "Element not found\n";

    cout << "Time Taken : " 
         << duration_cast<microseconds>(endTime - beginTime).count() 
         << " microseconds\n";

    // Timing for Binary Search
    beginTime = high_resolution_clock::now();
    resultIndex = performBinarySearch(sortedData, target);
    endTime = high_resolution_clock::now();

    cout << "\nBinary Search\n";
    if (resultIndex != -1)
        cout << "Element found at index " << resultIndex << "\n";
    else
        cout << "Element not found\n";

    cout << "Time Taken : " 
         << duration_cast<microseconds>(endTime - beginTime).count() 
         << " microseconds\n";

    return 0;
}
