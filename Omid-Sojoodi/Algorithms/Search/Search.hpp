# ifndef ALGORITHMS_OMID_SOJOODI_SEARCH
    /**
     * @file Search.hpp
     * @author Ramtin Kosari
     * @brief Search Algorithms
     * @version 0.1
     * @date 2024-01-16
     */
    # define ALGORITHMS_OMID_SOJOODI_SEARCH
    //-- Binary Search
    # ifndef ALGORITHMS_BINARY_SEARCH
        # include "Binary/BinarySearch.hpp"
    # endif // ALGORITHMS_BINARY_SEARCH
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
    class Search {
        public:
            //-- Constructor
            Search();
            //-- Binary Search
            BinarySearch binary;
    };
# endif // ALGORITHMS_OMID_SOJOODI_SEARCH
