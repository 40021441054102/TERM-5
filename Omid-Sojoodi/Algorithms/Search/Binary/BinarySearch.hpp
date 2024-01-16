# ifndef ALGORITHMS_OMID_SOJOODI_SEARCH_BINARY
    /**
     * @file BinarySearch.hpp
     * @author Ramtin Kosari
     * @brief Binary Search Algorithm
     * @version 0.1
     * @date 2024-01-16
     */
    # define ALGORITHMS_OMID_SOJOODI_SEARCH_BINARY
    //-- Used for std::vector
    # ifndef _GLIBCXX_VECTOR
        # include <vector>
    # endif // _GLIBCXX_VECTOR
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
    //-- Box Structure
    struct box {
        cv::Point topLeft;
        cv::Point bottomRight;
    };
    //-- Binary Search Class Definition
    class BinarySearch {
        private:
            //-- Target
            int target;
            //-- Array
            std::vector<int> data;
            //-- Window
            cv::Mat window;
        public:
            //-- Boxes
            std::vector<box> boxes;
            //-- Constructor
            BinarySearch();
            //-- Set Data
            void setData(
                std::vector<box> _boxes,
                std::vector<int> array,
                cv::Mat window,
                int target
            );
            //-- Search
            int getFound(bool graphical);
    };
# endif // ALGORITHMS_OMID_SOJOODI_SEARCH_BINARY