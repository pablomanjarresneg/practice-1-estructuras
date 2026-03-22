#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <filesystem>

#include "include/quicksort.h"
#include "include/heapsort.h"
#include "include/balancedtree.h"

using namespace std;
using namespace std::chrono;

static const int DATASET_SIZE = 100000;

vector<string> loadDataset(const string& path) {
    ifstream in(path);
    if (!in.is_open()) {
        cerr << "Error opening file: " << path << endl;
        return {};
    }

    vector<string> words;
    string word;
    while (getline(in, word)) {
        if (!word.empty()) {
            words.push_back(word);
        }
    }
    return words;
}

bool isSorted(const vector<string>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] < v[i - 1]) return false;
    }
    return true;
}

void printSample(const vector<string>& v, const string& label, int n = 10) {
    cout << "  First " << n << " words (" << label << "): ";
    for (int i = 0; i < n && i < static_cast<int>(v.size()); i++) {
        cout << v[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "\n";
}

int main() {
    // --- Locate dataset ---
    string datasetPath;
    if (filesystem::exists("data/dataset.txt"))
        datasetPath = "data/dataset.txt";
    else if (filesystem::exists("../data/dataset.txt"))
        datasetPath = "../data/dataset.txt";
    else {
        cerr << "dataset.txt not found. Run dataset_generator first.\n";
        return 1;
    }

    vector<string> original = loadDataset(datasetPath);
    cout << "Loaded " << original.size() << " words from dataset.\n\n";

    // =========================================================
    //  1) QuickSort on std::vector
    // =========================================================
    {
        cout << "========== QuickSort (std::vector) ==========\n";
        vector<string> data = original;

        auto start = high_resolution_clock::now();
        quicksort::sort(data);
        auto end = high_resolution_clock::now();

        auto ms = duration_cast<milliseconds>(end - start).count();
        cout << "  Time: " << ms << " ms\n";
        cout << "  Sorted correctly: " << (isSorted(data) ? "YES" : "NO") << "\n";
        printSample(data, "sorted");

        // Memory estimation
        size_t avgLen = 0;
        for (auto& w : original) avgLen += w.size();
        avgLen = avgLen / original.size();

        size_t memVector = sizeof(vector<string>)
            + original.size() * (sizeof(string) + avgLen);
        cout << "  Estimated memory: ~" << memVector / 1024 << " KB\n";
        cout << "  Complexity: O(n log n) average, O(n^2) worst case\n\n";
    }

    // =========================================================
    //  2) HeapSort using Binary Heap
    // =========================================================
    {
        cout << "========== HeapSort (Binary Heap) ==========\n";
        vector<string> data = original;

        auto start = high_resolution_clock::now();
        heapsort::sort(data);
        auto end = high_resolution_clock::now();

        auto ms = duration_cast<milliseconds>(end - start).count();
        cout << "  Time: " << ms << " ms\n";
        cout << "  Sorted correctly: " << (isSorted(data) ? "YES" : "NO") << "\n";
        printSample(data, "sorted");

        size_t avgLen = 0;
        for (auto& w : original) avgLen += w.size();
        avgLen = avgLen / original.size();

        size_t memHeap = sizeof(vector<string>)
            + original.size() * (sizeof(string) + avgLen);
        cout << "  Estimated memory: ~" << memHeap / 1024 << " KB\n";
        cout << "  Complexity: O(n log n) guaranteed\n\n";
    }

    // =========================================================
    //  3) AVL Tree (insert + inorder traversal)
    // =========================================================
    {
        cout << "========== AVL Tree (Balanced BST) ==========\n";

        auto start = high_resolution_clock::now();

        AVLTree tree;
        for (const auto& w : original) {
            tree.insert(w);
        }

        vector<string> sorted;
        sorted.reserve(original.size());
        tree.inorder(sorted);

        auto end = high_resolution_clock::now();

        auto ms = duration_cast<milliseconds>(end - start).count();
        cout << "  Time: " << ms << " ms\n";
        cout << "  Sorted correctly: " << (isSorted(sorted) ? "YES" : "NO") << "\n";
        cout << "  Elements after inorder: " << sorted.size() << "\n";
        printSample(sorted, "sorted");

        size_t avgLen = 0;
        for (auto& w : original) avgLen += w.size();
        avgLen = avgLen / original.size();

        // Each AVL node: string + 2 pointers + int height
        size_t nodeSize = sizeof(AVLNode) + avgLen;
        size_t memAVL = sorted.size() * nodeSize
            + sizeof(vector<string>) + sorted.size() * (sizeof(string) + avgLen);
        cout << "  Estimated memory: ~" << memAVL / 1024 << " KB\n";
        cout << "  Complexity: O(n log n) for n insertions, O(n) inorder traversal\n\n";
    }

    // =========================================================
    //  Comparative Summary
    // =========================================================
    cout << "========== Comparative Summary ==========\n";
    cout << "  Algorithm     | Best Case   | Average     | Worst Case  | Space\n";
    cout << "  --------------|-------------|-------------|-------------|----------\n";
    cout << "  QuickSort     | O(n log n)  | O(n log n)  | O(n^2)      | O(log n)\n";
    cout << "  HeapSort      | O(n log n)  | O(n log n)  | O(n log n)  | O(1)\n";
    cout << "  AVL Tree      | O(n log n)  | O(n log n)  | O(n log n)  | O(n)\n";
    cout << endl;

    return 0;
}
