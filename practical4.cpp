#include <iostream>
#include <chrono>
#include <array>

// -------------------------------------------------------------
// 1. Compile-Time Optimization (O(1) Runtime)
// -------------------------------------------------------------
constexpr size_t MAX_N = 20;

// Generates factorial table at COMPILE TIME using constexpr
constexpr auto generateFactorialTable() {
    std::array<unsigned long long, MAX_N + 1> table{};
    table[0] = 1;
    for (size_t i = 1; i <= MAX_N; ++i) {
        table[i] = table[i - 1] * i;
    }
    return table;
}

// Precomputed table baked directly into the executable binary
constexpr auto FACTORIAL_TABLE = generateFactorialTable();

// O(1) Time, O(1) Space via direct array lookup
inline unsigned long long factorialOptimizedIterative(int n) {
    return FACTORIAL_TABLE[n];
}

// -------------------------------------------------------------
// 2. Tail-Recursive Optimization (O(1) Stack Space via TCO)
// -------------------------------------------------------------
constexpr unsigned long long factorialTailRecursive(int n, unsigned long long acc = 1) {
    if (n <= 1) return acc;
    return factorialTailRecursive(n - 1, n * acc); // Tail call allows compiler loop conversion
}

// -------------------------------------------------------------
// Main Execution & Accurate Benchmarking
// -------------------------------------------------------------
int main() {
    int n;
    std::cout << "Enter a non-negative integer (0 to 20): ";
    
    // Check for valid range to prevent unsigned long long overflow
    if (!(std::cin >> n) || n < 0 || n > 20) {
        std::cerr << "Invalid input! Please enter an integer between 0 and 20." << std::endl;
        return 1;
    }

    constexpr int BENCHMARK_RUNS = 10'000'000;

    // --- Benchmark Iterative (Lookup Table) ---
    auto startIter = std::chrono::high_resolution_clock::now();
    volatile unsigned long long resIter = 0; // Prevent compiler from skipping execution
    for (int i = 0; i < BENCHMARK_RUNS; ++i) {
        resIter = factorialOptimizedIterative(n);
    }
    auto endIter = std::chrono::high_resolution_clock::now();
    
    double durationIter = std::chrono::duration<double, std::nano>(endIter - startIter).count() / BENCHMARK_RUNS;

    // --- Benchmark Tail-Recursive ---
    auto startRec = std::chrono::high_resolution_clock::now();
    volatile unsigned long long resRec = 0;
    for (int i = 0; i < BENCHMARK_RUNS; ++i) {
        resRec = factorialTailRecursive(n);
    }
    auto endRec = std::chrono::high_resolution_clock::now();
    
    double durationRec = std::chrono::duration<double, std::nano>(endRec - startRec).count() / BENCHMARK_RUNS;

    // Output Results
    std::cout << "\n--- Results for " << n << "! ---" << std::endl;
    std::cout << "Iterative Result : " << resIter << std::endl;
    std::cout << "Iterative Avg Time: " << durationIter << " ns" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Recursive Result : " << resRec << std::endl;
    std::cout << "Recursive Avg Time: " << durationRec << " ns" << std::endl;

    return 0;
}
