# ifndef ALGORITHMS_RADIX_SORT
    # include "Radix.hpp"
    //-- Constructor
    Radix::Radix() {
        std::cout << LOG "Radix Sort Algorithm Loaded Successfully!" << std::endl;
    }
    //-- Set Data
    void Radix::setData(cv::Mat _window, std::vector<double> _theta, std::vector<int> _x, std::vector<int> _y) {
        _window.copyTo(window);
        sorted.theta = _theta;
        sorted.x = _x;
        sorted.y = _y;
    }
    //-- Sort
    sortedPoints7 Radix::getSorted(bool graphical) {
        radixSort(sorted, 0, sorted.theta.size() - 1, graphical);
        return sorted;
    }
    //-- Radix Sort
    void Radix::radixSort(
        sortedPoints7 &points,
        int left,
        int right,
        bool graphical
    ) {
        int m = getMax(points, right);
        for (int exp = 1; m / exp > 0; exp *= 10) {
            countingSort(points, exp, graphical);
        }
    }
    //-- Counting Sort
    void Radix::countingSort(sortedPoints7& points, int exp, bool graphical) {
        int n = points.theta.size();
        std::vector<int> output(n);
        std::vector<int> count(10, 0);

        // Count occurrences
        for (int i = 0; i < n; i++) {
            count[(int)(points.theta[i] / exp) % 10]++;
        }

        // Update count to store the position of each element in the output array
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // Build the output array
        for (int i = n - 1; i >= 0; i--) {
            output[count[(int)(points.theta[i] / exp) % 10] - 1] = points.theta[i];
            points.x[count[(int)(points.theta[i] / exp) % 10] - 1] = sorted.x[i];
            points.y[count[(int)(points.theta[i] / exp) % 10] - 1] = sorted.y[i];
            count[(int)(points.theta[i] / exp) % 10]--;
        }

        // Copy the output array back to points
        for (int i = 0; i < n; i++) {
            points.theta[i] = output[i];
        }
        if (graphical) {
            cv::Mat tmp, tmp1;
            window.copyTo(tmp);
            for (int i = 0; i < n; i++) {
                tmp.copyTo(tmp1);
                cv::circle(
                    tmp1,
                    cv::Point(points.x[i], points.y[i]),
                    7,
                    cv::Scalar(0, 100, 255),
                    1,
                    cv::LINE_AA
                );
                cv::line(
                    tmp1,
                    cv::Point(points.x[i], points.y[i]),
                    cv::Point(points.x[i], points.y[i]),
                    cv::Scalar(0, 120, 120),
                    1,
                    cv::LINE_4
                );
                cv::imshow(WINDOW_NAME, tmp1);
                cv::waitKey(1);
            }
        }
    }
    //-- Get Max
    int Radix::getMax(sortedPoints7& points, int n) {
        int max = points.theta[0];
        for (int i = 1; i < n; i++) {
            if (points.theta[i] > max) {
                max = points.theta[i];
            }
        }
        return max;
    }
# endif // ALGORITHMS_RADIX_SORT