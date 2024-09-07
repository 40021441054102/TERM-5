# ifndef ALGORITHMS_HEAP_SORT
    # include "Heap.hpp"
    //-- Constructor
    Heap::Heap() {
        std::cout << LOG "Heap Sort Algorithm Loaded Successfully!" << std::endl;
    }
    //-- Set Data
    void Heap::setData(cv::Mat _window, std::vector<double> _theta, std::vector<int> _x, std::vector<int> _y) {
        _window.copyTo(window);
        sorted.theta = _theta;
        sorted.x = _x;
        sorted.y = _y;
    }
    //-- Sort
    sortedPoints6 Heap::getSorted(bool graphical) {
        heapSort(sorted, 0, sorted.theta.size() - 1, graphical);
        return sorted;
    }
    //-- Heap Sort
    void Heap::heapSort(
        sortedPoints6 &points,
        int left,
        int right,
        bool graphical
    ) {
        for (int i = right / 2 - 1; i >= 0; i--) {
            heapify(points, right, i, graphical);
        }
        for (int i = right - 1; i >= 0; i--) {
            std::swap(points.theta[0], points.theta[i]);
            std::swap(points.x[0], points.x[i]);
            std::swap(points.y[0], points.y[i]);
            heapify(points, i, 0, graphical);
        }
    }
    //-- Heapify
    void Heap::heapify(
        sortedPoints6 &points,
        int n,
        int i,
        bool graphical
    ) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && points.theta[l] > points.theta[largest]) {
            largest = l;
        }
        if (r < n && points.theta[r] > points.theta[largest]) {
            largest = r;
        }
        if (largest != i) {
            std::swap(points.theta[i], points.theta[largest]);
            std::swap(points.x[i], points.x[largest]);
            std::swap(points.y[i], points.y[largest]);
            if (graphical) {
                cv::Mat tmp, tmp1;
                window.copyTo(tmp);
                cv::circle(
                    tmp,
                    cv::Point(points.x[i], points.y[i]),
                    7,
                    cv::Scalar(0, 0, 255),
                    cv::FILLED
                );
                cv::circle(
                    tmp,
                    cv::Point(points.x[largest], points.y[largest]),
                    7,
                    cv::Scalar(0, 0, 255),
                    cv::FILLED
                );
                cv::line(
                    tmp,
                    cv::Point(points.x[i], points.y[i]),
                    cv::Point(points.x[largest], points.y[largest]),
                    cv::Scalar(0, 0, 255),
                    2
                );
                cv::imshow(WINDOW_NAME, tmp);
                cv::waitKey(1);
            }
            heapify(points, n, largest, graphical);
        }
    }
# endif // ALGORITHMS_HEAP_SORT