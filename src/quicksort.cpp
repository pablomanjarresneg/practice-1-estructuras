//
// Created by Pablo Manjarres on 21/03/26.
//

#include "../include/quicksort.h"

#include <utility> //swap
using namespace std;

void quickSort::quickSort(vector<string>& arr, int low, int high)
{
    if (arr.empty()){ return; }

    quickSort(arr, 0, static_cast<int>(arr.size()-1));
}

void quickSort::quickSort(vector<string>& arr, int low, int high)
{
    if (low >= high) { return; }

    int pivotIndex = partition(arr, low, high);
    quickSort(arr, low, pivotIndex-1);
    quickSort(arr, pivotIndex+1, high);

}

int quicksort::partition(vector<string>& arr, int low, int high)
{
    //Lomuto partition: choose last element as pivot
    const string& pivot = arr[high];
    int i = low - 1; //Index of smaller element
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot)
        {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}


