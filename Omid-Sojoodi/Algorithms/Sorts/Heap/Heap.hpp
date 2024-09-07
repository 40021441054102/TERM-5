# ifndef ALGORITHMS_HEAP_SORT
    /**
     * @file Heap.hpp
     * @author Ramtin Kosari
     * @brief Heap Sort Algorithm
     * @version 0.1
     * @date 2024-01-16
     */
    # define ALGORITHMS_HEAP_SORT
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
    # include <opencv4/opencv2/highgui.hpp>
    # include <opencv4/opencv2/imgproc.hpp>
    //-- Define Log Messages
    # define LOG "\033[38;2;0;255;0m[LOG]\033[0m "
    # define INFO "\033[38;2;0;255;255m[INFO]\033[0m "
    # define ERROR "\033[38;2;255;0;0m[ERROR]\033[0m "
    # define SUCCESS "\033[38;2;0;255;0m[SUCCESS]\033[0m "
    # define WARNING "\033[38;2;255;255;0m[WARNING]\033[0m "
    # define RESET "\033[0m"
    //-- Define Configurations
    # define WINDOW_NAME "Graphical View"
    //-- Define Point Structure
    struct sortedPoints6 {
        std::vector<double> theta;
        std::vector<int> x;
        std::vector<int> y;
    };
    //-- Class Definition
    class Heap {
        private:
            sortedPoints6 sorted;
            cv::Mat window;
            std::vector<double> tmpTheta;
            std::vector<int> tmpX;
            std::vector<int> tmpY;
        public:
            //-- Constructor
            Heap();
            //-- Set Data
            void setData(cv::Mat _window, std::vector<double> _theta, std::vector<int> _x, std::vector<int> _y);
            //-- Sort
            sortedPoints6 getSorted(bool graphical);
            //-- Heap Sort
            void heapSort(
                sortedPoints6 &points,
                int left,
                int right,
                bool graphical
            );
            //-- Heapify
            void heapify(
                sortedPoints6 &points,
                int n,
                int i,
                bool graphical
            );
    };
# endif // ALGORITHMS_HEAP_SORT