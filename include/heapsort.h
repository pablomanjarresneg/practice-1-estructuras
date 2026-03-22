#ifdef HEAPSORT_H
#define  HEAPSORT_H_

#include <vector>
#include <string>

void heapify(std::vector<stp::string>& arr, int n, int i);
void buildHeap(std::vector<std::string>& arr,int n); //Construcción el Max Heap a partir del arreglo
void heapsort(std::vector<std::string>& arr); // Ordena el arreglo usando HeapSort

#endif

