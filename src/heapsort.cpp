#include <vector>
#include <string>
#include "../include/heapsort.h"
using namespace std;

void heapify(vector<string>& arr,int n,int i) {
    int largest =i; //raiz
    int left= 2*i+1; //hijo izquierdo
    int right= 2*i+2; //hijo derecho

    //Hijo izquierdo es mayor
    if (left<n && arr [left]>arr[largest]) {
        largest=left;
    }

    //Hijo derecho es mayor
    if (right<n && arr[right]>arr[largest]) {
        largest=right;
    }

    //La raiz no es la mayor
    if (largest !=1) {
        swap(arr[i], arr [largest]);
        //Reorganizar
        heapify (arr,n,largest);

    }
}

void buildheap(vector<string>& arr, int n) {
    for (int i =n/2 -1; i >=0; i--) {
        heapify(arr,n,i);
    }
}


//head Sort: El vector de Strings es odenado alfabeticamente
void heapsort(vector<string>& arr) {
    int n = arr.size();

    buildHeap(arr,n); // construcción del heap

    for (int i= n-1; i >0; i--) {
        swap(arr[0], arr[i]); //El mayor se mueve al final
        heapify(arr,i,0); // Se reorganiza el heap
    }
}