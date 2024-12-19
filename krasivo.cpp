#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <random>

bool is_sorted(const std::vector<int>& arr) {
    return std::is_sorted(arr.begin(), arr.end());
}

// ---------------------- Bubble Sort ----------------------
std::vector<int> bubble_sort(std::vector<int> input_array) {
    int n = input_array.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (input_array[j] > input_array[j + 1]) {
                std::swap(input_array[j], input_array[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break; // Оптимизация: если не было перестановок, массив отсортирован
        }
    }
    return input_array;
}

// ---------------------- Heap Sort ----------------------
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

std::vector<int> heap_sort(std::vector<int> input_array) {
    int n = input_array.size();

    // Построение max-кучи
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(input_array, n, i);
    }

    for (int i = n - 1; i > 0; --i) {
        std::swap(input_array[0], input_array[i]);
        heapify(input_array, i, 0);
    }
    return input_array;
}

// ---------------------- Bucket Sort ----------------------
std::vector<int> bucket_sort(std::vector<int> input_array) {
    int bucket_size = 5;
    if (input_array.empty()) {
        return input_array;
    }

    auto [min_it, max_it] = std::minmax_element(input_array.begin(), input_array.end());
    int min_value = *min_it;
    int max_value = *max_it;

    int bucket_count = (max_value - min_value) / bucket_size + 1;
    std::vector<std::vector<int>> buckets(bucket_count);

    for (int num : input_array) {
        int bucket_index = (num - min_value) / bucket_size;
        buckets[bucket_index].push_back(num);
    }

    std::vector<int> sorted_array;
    for (auto& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end());
        sorted_array.insert(sorted_array.end(), bucket.begin(), bucket.end());
    }
    return sorted_array;
}

// ---------------------- Unit tests ----------------------
void test_sorting_algorithm(const std::string& name,
                             std::function<std::vector<int>(std::vector<int>)> sort_func,
                             const std::vector<int>& best_case,
                             const std::vector<int>& average_case,
                             const std::vector<int>& worst_case) {
    std::cout << "Running tests for " << name << ":" << std::endl;

    std::cout << "  Best Case: ";
    assert(is_sorted(sort_func(best_case)));
    std::cout << "PASSED" << std::endl;

    std::cout << "  Average Case: ";
    assert(is_sorted(sort_func(average_case)));
    std::cout << "PASSED" << std::endl;

    std::cout << "  Worst Case: ";
    assert(is_sorted(sort_func(worst_case)));
    std::cout << "PASSED" << std::endl;

    std::cout << "All tests for " << name << " PASSED" << std::endl << std::endl;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 100);
    auto generate_random_vector = [&](int size) {
        std::vector<int> random_vec(size);
        for (int i = 0; i < size; ++i) {
            random_vec[i] = distrib(gen);
        }
        return random_vec;
    };

    // Тестовые случаи
    std::vector<int> best_case = {1, 2, 3, 4, 5};
    std::vector<int> average_case = generate_random_vector(10);
    std::vector<int> worst_case_bubble = {5, 4, 3, 2, 1};
    std::vector<int> worst_case_heap = {5, 1, 4, 2, 3}; 
    std::vector<int> worst_case_bucket = {1, 1, 1, 1, 1}; 

    // Запуск тестов
    test_sorting_algorithm("Bubble Sort", bubble_sort, best_case, average_case, worst_case_bubble);
    test_sorting_algorithm("Heap Sort", heap_sort, best_case, average_case, worst_case_heap);
    test_sorting_algorithm("Bucket Sort", bucket_sort, best_case, average_case, worst_case_bucket);

    return 0;
}