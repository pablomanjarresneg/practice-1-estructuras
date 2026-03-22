# Practice I - Sorting Large Dataset (C++)

**ST0245 - Data Structures and Algorithms**
EAFIT University - School of Applied Sciences and Engineering

## Description

This project sorts a dataset of 100,000 English words using three different algorithmic strategies:

1. **QuickSort** - Implemented over a dynamic array (`std::vector<string>`)
2. **HeapSort** - Implemented using a Binary Heap structure
3. **AVL Tree** - Words are inserted into a balanced BST; sorted order is obtained via inorder traversal

## Project Structure

```
.
├── main.cpp                    # Main program: runs all 3 sorting strategies with timing
├── src/
│   ├── quicksort.cpp           # QuickSort implementation (Lomuto partition)
│   ├── heapsort.cpp            # HeapSort implementation (max-heap)
│   ├── balancedtree.cpp        # AVL Tree implementation
│   └── dataset_generator.cpp   # Generates dataset.txt (100,000 random words)
├── include/
│   ├── quicksort.h
│   ├── heapsort.h
│   └── balancedtree.h
├── data/
│   ├── words_alpha.txt         # Source word list
│   └── dataset.txt             # Generated randomized dataset (100,000 words)
├── docs/
│   └── Practice_I_Structs_v1_Narváez.pdf
└── CMakeLists.txt
```

## How to Build and Run

### With CMake

```bash
mkdir build && cd build
cmake ..
make
```

### Without CMake

```bash
# Compile dataset generator
clang++ -std=c++17 -O2 -o dataset_generator src/dataset_generator.cpp

# Compile main program
clang++ -std=c++17 -O2 -o practice_1_estructuras main.cpp src/quicksort.cpp src/heapsort.cpp src/balancedtree.cpp
```

### Running

```bash
# Step 1: Generate the randomized dataset (100,000 words)
./dataset_generator

# Step 2: Run the sorting program
./practice_1_estructuras
```

## Implementation Details

### A) QuickSort

- Uses **Lomuto partition scheme** with the last element as pivot.
- Operates in-place on a `std::vector<string>`.
- No built-in sorting functions used.

### B) HeapSort

- Builds a **max-heap** from the array using bottom-up heap construction.
- Repeatedly extracts the maximum and places it at the end.
- Operates in-place on a `std::vector<string>`.

### C) AVL Tree

- Full AVL tree with **single and double rotations** (LL, RR, LR, RL cases).
- All 100,000 words are inserted maintaining balance at every step.
- Sorted output is obtained via **inorder traversal**.
- Duplicate words are ignored during insertion.

## Performance Analysis

### Execution Times (100,000 words)

| Algorithm  | Time  |
|------------|-------|
| QuickSort  | ~12 ms |
| HeapSort   | ~30 ms |
| AVL Tree   | ~28 ms |

### Algorithmic Complexity

| Algorithm  | Best Case  | Average    | Worst Case  | Space     |
|------------|------------|------------|-------------|-----------|
| QuickSort  | O(n log n) | O(n log n) | O(n^2)      | O(log n)  |
| HeapSort   | O(n log n) | O(n log n) | O(n log n)  | O(1)      |
| AVL Tree   | O(n log n) | O(n log n) | O(n log n)  | O(n)      |

### Memory Estimation

| Algorithm  | Estimated Memory |
|------------|-----------------|
| QuickSort  | ~3.1 MB (vector of strings) |
| HeapSort   | ~3.1 MB (vector of strings, in-place) |
| AVL Tree   | ~8.6 MB (tree nodes + output vector) |

## Comparative Analysis

### Which algorithm performed better?

**QuickSort** achieved the fastest execution time (~12 ms), followed by AVL Tree (~28 ms) and HeapSort (~30 ms). QuickSort benefits from excellent cache locality since it operates on a contiguous array, and the Lomuto partition has low overhead for string comparisons.

### Why does theoretical complexity sometimes differ from practical results?

Although all three algorithms share O(n log n) average complexity, real-world performance depends on:

- **Cache locality**: QuickSort and HeapSort operate on contiguous memory (vector), but QuickSort's access pattern is more sequential. HeapSort jumps between parent/child indices, causing more cache misses.
- **Constant factors**: AVL Tree requires memory allocation for every insertion (`new` for each node), pointer dereferencing for traversal, and rotation overhead to maintain balance. These hidden constant factors add up.
- **String comparisons**: Strings with common prefixes require more character-by-character comparisons, affecting all algorithms equally but amplifying time differences.

### Advantages and disadvantages of each data structure

| | Advantages | Disadvantages |
|---|---|---|
| **QuickSort (vector)** | Fastest in practice; cache-friendly; in-place; simple implementation | O(n^2) worst case with poor pivot choices |
| **HeapSort (binary heap)** | O(n log n) guaranteed; in-place; no extra memory | Poor cache locality; slower constant factors |
| **AVL Tree** | O(n log n) guaranteed; supports dynamic insertions/deletions; naturally ordered | High memory overhead (pointers per node); allocation cost; more complex implementation |

### Conclusion

For a one-time sort of a static dataset, **QuickSort** is the most appropriate choice due to its speed and low memory usage. **HeapSort** is a solid alternative when worst-case guarantees matter and extra memory is not available. The **AVL Tree** is best suited for scenarios requiring frequent insertions, deletions, and lookups while maintaining sorted order — its overhead makes it less ideal for a pure sorting task.
