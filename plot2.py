import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
import time


def bucket_sort(arr, bucket_size=5):
    if len(arr) == 0:
        return arr

    min_value, max_value = min(arr), max(arr)
    bucket_count = (max_value - min_value) // bucket_size + 1
    buckets = [[] for _ in range(bucket_count)]

    for num in arr:
        buckets[(num - min_value) // bucket_size].append(num)

    sorted_array = []
    for bucket in buckets:
        sorted_array.extend(sorted(bucket))
    return sorted_array


def heapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2

    if l < n and arr[l] > arr[largest]:
        largest = l
    if r < n and arr[r] > arr[largest]:
        largest = r
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)


def heap_sort(arr):
    n = len(arr)

    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    for i in range(n-1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)
    return arr


def bubble_sort_optimized(arr):
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
                swapped = True
        if not swapped:
            break
    return arr


# Сбор данных
data = {"Algorithm": [], "Time": []}
for _ in range(10):
    array = np.random.randint(0, 100000, 10000)  # массив размером 10^4
    print('a')
    start = time.time()
    bubble_sort_optimized(array.copy())
    data["Algorithm"].append("Bubble Sort")
    data["Time"].append(time.time() - start)

    start = time.time()
    heap_sort(array.copy())
    data["Algorithm"].append("Heap Sort")
    data["Time"].append(time.time() - start)

    start = time.time()
    bucket_sort(array.copy())
    data["Algorithm"].append("Bucket Sort")
    data["Time"].append(time.time() - start)

# Построение графика
sns.boxplot(x="Algorithm", y="Time", data=data)
plt.title("Performance for Arrays of Size 10^4")
plt.savefig("boxplot.png")
plt.show()
