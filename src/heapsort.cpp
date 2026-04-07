#include "../include/heapsort.h"
#include <utility>

using namespace std;

void heapsort::heapify(vector<string>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;   // Left child index in array-based heap.
    int right = 2 * i + 2;  // Right child index in array-based heap.

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);   // Move larger child to parent.
        heapify(arr, n, largest);     // Fix affected subtree.
    }
}

void heapsort::buildHeap(vector<string>& arr, int n) {
    // Start from the last non-leaf node and heapify each parent up to the root.
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

void heapsort::sort(vector<string>& arr) {
    int n = static_cast<int>(arr.size());

    // Step 1: Convert the array into a max-heap.
    buildHeap(arr, n);

    // Step 2: Repeatedly move the max element root to the end,
    // then restore heap property on the reduced heap.
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}