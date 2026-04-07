
#include "../include/quicksort.h"

#include <utility> //swap
using namespace std;

void quicksort::sort(vector<string>& arr)
{
    // Guard clause: nothing to sort.
    if (arr.empty()) { return; }

    // Sort the full range: [0, size - 1].
    quickSort(arr, 0, static_cast<int>(arr.size() - 1));
}

void quicksort::quickSort(vector<string>& arr, int low, int high)
{
    // Base case: range with 0 or 1 element is already sorted.
    if (low >= high) { return; }

    // Partition the range and get the final pivot position.
    int pivotIndex = partition(arr, low, high);

    // Recursively sort elements smaller than pivot.
    quickSort(arr, low, pivotIndex - 1);

    // Recursively sort elements greater than pivot.
    quickSort(arr, pivotIndex + 1, high);
}

int quicksort::partition(vector<string>& arr, int low, int high)
{
    // Lomuto partition scheme: use the last element as pivot.
    const string& pivot = arr[high];

    // Boundary index for values <= pivot.
    int i = low - 1;

    // Move all values <= pivot to the left side.
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    // Place pivot in its final sorted position.
    swap(arr[i + 1], arr[high]);
    return i + 1;
}


