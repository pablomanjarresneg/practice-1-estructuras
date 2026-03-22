#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <string>

class heapsort {
public:
    static void sort(std::vector<std::string>& arr);
private:
    static void heapify(std::vector<std::string>& arr, int n, int i);
    static void buildHeap(std::vector<std::string>& arr, int n);
};

#endif
