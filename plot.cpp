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
    std::vector<int> sizes;
    std::vector<double> bubble_times, heap_times, bucket_times;
    
    // Generate sizes from 1000 to 100000 with step 1000
    for (int i = 1000; i <= 100000; i += 1000) {
        sizes.push_back(i);
    }

    // Random number generation setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99999);

    for (int size : sizes) {
        // Generate random array
        std::vector<int> array(size);
        for (int& num : array) {
            num = dis(gen);
        }

        std::cout << "Testing size: " << size << std::endl;

        // Bubble sort timing
        auto start = std::chrono::high_resolution_clock::now();
        bubble_sort_optimized(array);
        auto end = std::chrono::high_resolution_clock::now();
        bubble_times.push_back(std::chrono::duration<double>(end - start).count());

        // Heap sort timing
        start = std::chrono::high_resolution_clock::now();
        heap_sort(array);
        end = std::chrono::high_resolution_clock::now();
        heap_times.push_back(std::chrono::duration<double>(end - start).count());

        // Bucket sort timing
        start = std::chrono::high_resolution_clock::now();
        bucket_sort(array);
        end = std::chrono::high_resolution_clock::now();
        bucket_times.push_back(std::chrono::duration<double>(end - start).count());
    }

    // Plotting
    plt::plot(std::vector<double>(sizes.begin(), sizes.end()), bubble_times, "b-");
    plt::plot(std::vector<double>(sizes.begin(), sizes.end()), heap_times, "r-");
    plt::plot(std::vector<double>(sizes.begin(), sizes.end()), bucket_times, "g-");
    
    plt::named_plot("Bubble Sort", std::vector<double>(sizes.begin(), sizes.end()), bubble_times, "b-");
    plt::named_plot("Heap Sort", std::vector<double>(sizes.begin(), sizes.end()), heap_times, "r-");
    plt::named_plot("Bucket Sort", std::vector<double>(sizes.begin(), sizes.end()), bucket_times, "g-");
    
    plt::xlabel("Array Size");
    plt::ylabel("Time (s)");
    plt::legend();
    plt::save("sorting_algorithms_comparison.png");
    plt::show();

    return 0;
}