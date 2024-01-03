# ifndef ALGORITHMS_MERGE_SORT
    # include "Merge.hpp"
    //-- Constructor
    Merge::Merge() {
        std::cout << LOG "Merge Sort Algorithm Loaded Successfully!" << std::endl;
    }
    //-- Set Data
    void Merge::setData(cv::Mat _window, std::vector<double> _theta, std::vector<int> _x, std::vector<int> _y) {
        _window.copyTo(window);
        sorted.theta = _theta;
        sorted.x = _x;
        sorted.y = _y;
    }
    //-- Merge
    void Merge::merge(std::vector<sortedPoints4>& points, int left, int middle, int right, bool graphical) {
        // if (graphical) {
            int n1 = middle - left + 1;
            int n2 = right - middle;
            std::vector<sortedPoints4> leftArray(n1), rightArray(n2);
            for (int i = 0; i < n1; i++)
                leftArray[i] = points[left + i];
            for (int j = 0; j < n2; j++)
                rightArray[j] = points[middle + 1 + j];
            int i = 0; // Initial index of first subarray
            int j = 0; // Initial index of second subarray
            int k = left; // Initial index of merged subarray
            cv::circle(
                window,
                cv::Point(leftArray[i].x[0], leftArray[i].y[0]),
                7,
                cv::Scalar(0, 100, 255),
                1,
                cv::LINE_AA
            );
            cv::circle(
                window,
                cv::Point(rightArray[j].x[0], rightArray[j].y[0]),
                7,
                cv::Scalar(0, 100, 255),
                1,
                cv::LINE_AA
            );
            cv::imshow(WINDOW_NAME, window);
            cv::waitKey(1);
            while (i < n1 && j < n2) {
                k++;
            }
            while (i < n1) {
                points[k] = leftArray[i];
                i++;
                k++;
            }
            while (j < n2) {
                points[k] = rightArray[j];
                j++;
                k++;
            }
            cv::line(
                window,
                cv::Point(leftArray[i].x[0], leftArray[i].y[0]),
                cv::Point(rightArray[j].x[0], rightArray[j].y[0]),
                cv::Scalar(0, 120, 120),
                1,
                cv::LINE_4
            );
            cv::imshow(WINDOW_NAME, window);
            cv::waitKey(1);
        // } else {
        //     int n1 = middle - left + 1;
        //     int n2 = right - middle;
        //     std::vector<sortedPoints4> leftArray(n1), rightArray(n2);
        //     for (int i = 0; i < n1; i++)
        //         leftArray[i] = points[left + i];
        //     for (int j = 0; j < n2; j++)
        //         rightArray[j] = points[middle + 1 + j];
        //     int i = 0; // Initial index of first subarray
        //     int j = 0; // Initial index of second subarray
        //     int k = left; // Initial index of merged subarray
        //     cv::imshow(WINDOW_NAME, window);
        //     cv::waitKey(1);
        //     while (i < n1 && j < n2) {
        //         k++;
        //     }
        //     while (i < n1) {
        //         points[k] = leftArray[i];
        //         i++;
        //         k++;
        //     }
        //     while (j < n2) {
        //         points[k] = rightArray[j];
        //         j++;
        //         k++;
        //     }
        // }
    }
    // Merge sort function
    void Merge::mergeSort(std::vector<sortedPoints4>& points, int left, int right, bool graphical) {
        if (left < right) {
            int middle = left + (right - left) / 2;
            mergeSort(points, left, middle, graphical);
            cv::circle(
                window,
                cv::Point(points[middle].x[0], points[middle].y[0]),
                7,
                cv::Scalar(0, 100, 255),
                1,
                cv::LINE_AA
            );
            cv::imshow(WINDOW_NAME, window);
            cv::waitKey(1);
            mergeSort(points, middle + 1, right, graphical);
            cv::circle(
                window,
                cv::Point(points[middle + 1].x[0], points[middle + 1].y[0]),
                7,
                cv::Scalar(0, 100, 255),
                1,
                cv::LINE_AA
            );
            cv::imshow(WINDOW_NAME, window);
            cv::waitKey(1);
            merge(points, left, middle, right, graphical);
            cv::line(
                window,
                cv::Point(points[middle].x[0], points[middle].y[0]),
                cv::Point(points[middle + 1].x[0], points[middle + 1].y[0]),
                cv::Scalar(0, 120, 0),
                1,
                cv::LINE_4
            );
            cv::imshow(WINDOW_NAME, window);
            cv::waitKey(0);
        }
    }
    //-- Sort
    sortedPoints4 Merge::getSorted(bool graphical) {
        std::vector<sortedPoints4> points;
        std::cout << "bool L " << graphical << std::endl;
        points.push_back(sorted);
        mergeSort(points, 0, points.size() - 1, graphical);
        return points[0];
    }
# endif // ALGORITHMS_MERGE_SORT