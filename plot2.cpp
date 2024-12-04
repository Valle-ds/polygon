#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

std::vector<int> bubble_sort_optimized(std::vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return arr;
}

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

std::vector<int> heap_sort(std::vector<int> arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
    return arr;
}

std::vector<int> bucket_sort(std::vector<int> arr, int bucket_size = 5) {
    if (arr.empty()) return arr;

    auto [min_it, max_it] = std::minmax_element(arr.begin(), arr.end());
    int min_value = *min_it;
    int max_value = *max_it;
    
    int bucket_count = (max_value - min_value) / bucket_size + 1;
    std::vector<std::vector<int>> buckets(bucket_count);

    for (int num : arr) {
        buckets[(num - min_value) / bucket_size].push_back(num);
    }

    std::vector<int> sorted_array;
    for (auto& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end());
        sorted_array.insert(sorted_array.end(), bucket.begin(), bucket.end());
    }
    return sorted_array;
}

int main() {
    std::vector<std::string> algorithms;
    std::vector<double> times;
    
    // Random number generation setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99999);

    // Run 50 iterations
    for (int iter = 0; iter < 50; ++iter) {
        // Generate random array of size 10^4
        std::vector<int> array(10000);
        for (int& num : array) {
            num = dis(gen);
        }

        // Bubble sort timing
        auto start = std::chrono::high_resolution_clock::now();
        bubble_sort_optimized(array);
        auto end = std::chrono::high_resolution_clock::now();
        algorithms.push_back("Bubble Sort");
        times.push_back(std::chrono::duration<double>(end - start).count());

        // Heap sort timing
        start = std::chrono::high_resolution_clock::now();
        heap_sort(array);
        end = std::chrono::high_resolution_clock::now();
        algorithms.push_back("Heap Sort");
        times.push_back(std::chrono::duration<double>(end - start).count());

        // Bucket sort timing
        start = std::chrono::high_resolution_clock::now();
        bucket_sort(array);
        end = std::chrono::high_resolution_clock::now();
        algorithms.push_back("Bucket Sort");
        times.push_back(std::chrono::duration<double>(end - start).count());
    }

    // Create boxplot using matplotlib-cpp
    plt::boxplot(times, algorithms);
    plt::title("Performance for Arrays of Size 10^4");
    plt::ylabel("Time (s)");
    plt::save("boxplot.png");
    plt::show();

    return 0;
}
