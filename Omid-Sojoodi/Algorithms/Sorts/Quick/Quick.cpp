# ifndef ALGORITHMS_QUICK_SORT
    # include "Quick.hpp"
    //-- Constructor
    Quick::Quick() {
        std::cout << LOG "Quick Sort Algorithm Loaded Successfully!" << std::endl;
    }
    //-- Set Data
    void Quick::setData(cv::Mat _window, std::vector<double> _theta, std::vector<int> _x, std::vector<int> _y) {
        _window.copyTo(window);
        sorted.theta = _theta;
        sorted.x = _x;
        sorted.y = _y;
    }
    //-- Sort
    sortedPoints5 Quick::getSorted(bool graphical) {
        quickSort(sorted, 0, sorted.theta.size() - 1, graphical);
        return sorted;
    }
    //-- Quick Sort
    void Quick::quickSort(
        sortedPoints5 &points,
        int left,
        int right,
        bool graphical
    ) {
        if (left < right) {
            int pivot = partition(points, left, right, graphical);
            quickSort(points, left, pivot - 1, graphical);
            quickSort(points, pivot + 1, right, graphical);
        }
    }
    //-- Partition
    int Quick::partition(
        sortedPoints5 &points,
        int left,
        int right,
        bool graphical
    ) {
        double pivot = points.theta[right];
        int i = left - 1;
        for (int j = left; j <= right - 1; j++) {
            if (points.theta[j] < pivot) {
                i++;
                std::swap(points.theta[i], points.theta[j]);
                std::swap(points.x[i], points.x[j]);
                std::swap(points.y[i], points.y[j]);
            }
        }
        std::swap(points.theta[i + 1], points.theta[right]);
        std::swap(points.x[i + 1], points.x[right]);
        std::swap(points.y[i + 1], points.y[right]);
        if (graphical) {
            cv::Mat tmp, tmp1;
            window.copyTo(tmp);
            cv::circle(
                tmp,
                cv::Point(points.x[i + 1], points.y[i + 1]),
                7,
                cv::Scalar(0, 0, 255),
                cv::FILLED
            );
            cv::circle(
                tmp,
                cv::Point(points.x[right], points.y[right]),
                7,
                cv::Scalar(0, 0, 255),
                cv::FILLED
            );
            cv::line(
                tmp,
                cv::Point(points.x[i + 1], points.y[i + 1]),
                cv::Point(points.x[right], points.y[right]),
                cv::Scalar(0, 120, 120),
                1,
                cv::LINE_4
            );
            cv::imshow(WINDOW_NAME, tmp);
            cv::waitKey(1);
        }
        return i + 1;
    }
# endif // ALGORITHMS_QUICK_SORT