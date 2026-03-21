//
// Created by Pablo Manjarres on 21/03/26.
//

#ifndef PRACTICE_1_ESTRUCTURAS_QUICKSORT_H
#define PRACTICE_1_ESTRUCTURAS_QUICKSORT_H

#include <string>
#include <vector>
using namespace std;

class quicksort
{
public:
    static void sort(vector<string>& arr);
private:
    static void quickSort(vector<string>& arr, int low, int high);
    static int partition(vector<string>& arr, int low, int high);
};


#endif //PRACTICE_1_ESTRUCTURAS_QUICKSORT_H