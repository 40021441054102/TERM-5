# ifndef ALGORITHMS_BUBBLE_SORT
    /**
     * @file Bubble.hpp
     * @author Ramtin Kosari
     * @brief Bubble Sort Algorithm
     * @version 0.1
     * @date 2024-01-03
     */
    # define ALGORITHMS_BUBBLE_SORT
    //-- Used for std::vector
    # ifndef _GLIBCXX_VECTOR
        # include <vector>
    # endif // _GLIBCXX_VECTOR
    //-- Used for std::swap
    # ifndef _GLIBCXX_ALGORITHM
        # include <algorithm>
    # endif // _GLIBCXX_ALGORITHM
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
    class Bubble {
        private:
            std::vector<double> data;
        public:
            //-- Constructor
            Bubble();
            //-- Set Data
            void setData(std::vector<double> _data);
            //-- Sort
            std::vector<double> getSorted();
    };
# endif // ALGORITHMS_BUBBLE_SORT