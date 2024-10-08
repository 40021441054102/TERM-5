# ifndef ALGORITHMS_OMID_SOJOODI_SORTS
    /**
     * @file Sorts.hpp
     * @author Ramtin Kosari (ramtinkosari@gmail.com)
     * @brief Sort Algorithms
     * @version 0.1
     * @date 2024-01-03
     */
    # define ALGORITHMS_OMID_SOJOODI_SORTS
    //-- Bubble Sort
    # ifndef ALGORITHMS_BUBBLE_SORT
        # include "Bubble/Bubble.hpp"
    # endif // ALGORITHMS_BUBBLE_SORT
    //-- Insertion Sort
    # ifndef ALGORITHMS_INSERTION_SORT
        # include "Insertion/Insertion.hpp"
    # endif // ALGORITHMS_INSERTION_SORT
    //-- Selection Sort
    # ifndef ALGORITHMS_SELECTION_SORT
        # include "Selection/Selection.hpp"
    # endif // ALGORITHMS_SELECTION_SORT
    //-- Merge Sort
    # ifndef ALGORITHMS_MERGE_SORT
        # include "Merge/Merge.hpp"
    # endif // ALGORITHMS_MERGE_SORT
    //-- Quick Sort
    # ifndef ALGORITHMS_QUICK_SORT
        # include "Quick/Quick.hpp"
    # endif // ALGORITHMS_QUICK_SORT
    //-- Heap Sort
    # ifndef ALGORITHMS_HEAP_SORT
        # include "Heap/Heap.hpp"
    # endif // ALGORITHMS_HEAP_SORT
    //-- Include Needed Libraries
    # include <iostream>
    //-- Define Log Messages
    # define LOG "\033[38;2;0;255;0m[LOG]\033[0m "
    # define INFO "\033[38;2;0;255;255m[INFO]\033[0m "
    # define ERROR "\033[38;2;255;0;0m[ERROR]\033[0m "
    # define SUCCESS "\033[38;2;0;255;0m[SUCCESS]\033[0m "
    # define WARNING "\033[38;2;255;255;0m[WARNING]\033[0m "
    # define RESET "\033[0m"
    //-- Class Definition
    class Sorts {
        public:
            //-- Constructor
            Sorts();
            //-- Bubble Sort
            Bubble bubble;
            //-- Insertion Sort
            Insertion insertion;
            //-- Selection Sort
            Selection selection;
            //-- Merge Sort
            Merge merge;
            //-- Quick Sort
            Quick quick;
            //-- Heap Sort
            Heap heap;
    };
# endif // ALGORITHMS_OMID_SOJOODI_SORTS