#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

//------------------ MAX HEAP ------------------//
// Optimized: Iterative instead of recursive to avoid stack overhead
void maxHeapify(vector<int> &arr, int n, int i)
{
    while (true)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest == i)
            break;

        swap(arr[i], arr[largest]);
        i = largest; // Move down the tree
    }
}

void maxHeapSort(vector<int> &arr)
{
    int n = arr.size();

    // Build Max Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);

    // Heap Sort
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

//------------------ MIN HEAP ------------------//
// Optimized: Iterative instead of recursive to avoid stack overhead
void minHeapify(vector<int> &arr, int n, int i)
{
    while (true)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] < arr[smallest])
            smallest = left;

        if (right < n && arr[right] < arr[smallest])
            smallest = right;

        if (smallest == i)
            break;

        swap(arr[i], arr[smallest]);
        i = smallest; // Move down the tree
    }
}

void minHeapSort(vector<int> &arr)
{
    int n = arr.size();

    // Build Min Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);

    // Heap Sort
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        minHeapify(arr, i, 0);
    }

    // Reverse to get ascending order
    reverse(arr.begin(), arr.end());
}

//------------------ MAIN ------------------//
int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> original(n);
    srand(time(0));

    for (int i = 0; i < n; i++)
        original[i] = rand() % 100000;

    vector<int> maxHeapArray = original;
    vector<int> minHeapArray = original;

    //---------------- MAX HEAP SORT ----------------//
    auto startMax = high_resolution_clock::now();
    maxHeapSort(maxHeapArray);
    auto endMax = high_resolution_clock::now();

    //---------------- MIN HEAP SORT ----------------//
    auto startMin = high_resolution_clock::now();
    minHeapSort(minHeapArray);
    auto endMin = high_resolution_clock::now();

    //---------------- DISPLAY TIME ----------------//
    // Simplified variable assignments for cleaner code
    long long nanoMax = duration_cast<nanoseconds>(endMax - startMax).count();
    long long microMax = duration_cast<microseconds>(endMax - startMax).count();

    long long nanoMin = duration_cast<nanoseconds>(endMin - startMin).count();
    long long microMin = duration_cast<microseconds>(endMin - startMin).count();

    cout << "\n========== MAX HEAP SORT ==========\n";
    cout << "Nanoseconds  : " << nanoMax << " ns\n";
    cout << "Microseconds : " << microMax << " us\n";

    cout << "\n========== MIN HEAP SORT ==========\n";
    cout << "Nanoseconds  : " << nanoMin << " ns\n";
    cout << "Microseconds : " << microMin << " us\n";

    return 0;
}
