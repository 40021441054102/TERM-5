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
    void Merge::merge(
        sortedPoints4 &points,
        int left,
        int middle,
        int right,
        bool graphical
    ) {
        int i, j, k;
        int n1 = middle - left + 1;
        int n2 = right - middle;
        std::vector<double> theta1(n1), theta2(n2);
        std::vector<int> x1(n1), x2(n2), y1(n1), y2(n2);
        for (i = 0; i < n1; i++) {
            theta1[i] = points.theta[left + i];
            x1[i] = points.x[left + i];
            y1[i] = points.y[left + i];
        }
        for (j = 0; j < n2; j++) {
            theta2[j] = points.theta[middle + 1 + j];
            x2[j] = points.x[middle + 1 + j];
            y2[j] = points.y[middle + 1 + j];
        }
        i = 0;
        j = 0;
        k = left;
        while (i < n1 && j < n2) {
            if (theta1[i] <= theta2[j]) {
                // If equal, use <= to maintain stability
                points.theta[k] = theta1[i];
                points.x[k] = x1[i];
                points.y[k] = y1[i];
                i++;
            } else {
                points.theta[k] = theta2[j];
                points.x[k] = x2[j];
                points.y[k] = y2[j];
                j++;
            }
            k++;
            if (graphical) {
                cv::Mat tmp, tmp1;
                window.copyTo(tmp);
                cv::circle(
                    tmp,
                    cv::Point(points.x[k], points.y[k]),
                    7,
                    cv::Scalar(0, 100, 255),
                    1,
                    cv::LINE_AA
                );
                cv::line(
                    tmp,
                    cv::Point(points.x[k], points.y[k]),
                    cv::Point(points.x[k - 1], points.y[k - 1]),
                    cv::Scalar(0, 120, 120),
                    1,
                    cv::LINE_4
                );
                cv::imshow(WINDOW_NAME, tmp);
                cv::waitKey(1);
            }
        }
        while (i < n1) {
            points.theta[k] = theta1[i];
            points.x[k] = x1[i];
            points.y[k] = y1[i];
            i++;
            k++;
            if (graphical) {
                cv::Mat tmp, tmp1;
                window.copyTo(tmp);
                cv::circle(
                    tmp,
                    cv::Point(points.x[k], points.y[k]),
                    7,
                    cv::Scalar(0, 100, 255),
                    1,
                    cv::LINE_AA
                );
                cv::line(
                    tmp,
                    cv::Point(points.x[k], points.y[k]),
                    cv::Point(points.x[k - 1], points.y[k - 1]),
                    cv::Scalar(0, 120, 120),
                    1,
                    cv::LINE_4
                );
                cv::imshow(WINDOW_NAME, tmp);
                cv::waitKey(1);
            }
        }
        while (j < n2) {
            points.theta[k] = theta2[j];
            points.x[k] = x2[j];
            points.y[k] = y2[j];
            j++;
            k++;
            if (graphical) {
                cv::Mat tmp, tmp1;
                window.copyTo(tmp);
                cv::circle(
                    tmp,
                    cv::Point(points.x[k], points.y[k]),
                    7,
                    cv::Scalar(0, 100, 255),
                    1,
                    cv::LINE_AA
                );
                cv::line(
                    tmp,
                    cv::Point(points.x[k], points.y[k]),
                    cv::Point(points.x[k - 1], points.y[k - 1]),
                    cv::Scalar(0, 120, 120),
                    1,
                    cv::LINE_4
                );
                cv::imshow(WINDOW_NAME, tmp);
                cv::waitKey(1);
            }
        }
    }
    //-- Merge Sort
    void Merge::mergeSort(
        sortedPoints4 &points,
        int left,
        int right,
        bool graphical
    ) {
        if (left < right) {
            int middle = left + (right - left) / 2;
            mergeSort(points, left, middle, graphical);
            mergeSort(points, middle + 1, right, graphical);
            merge(points, left, middle, right, graphical);
        }
    }
    //-- Sort
    sortedPoints4 Merge::getSorted(bool graphical) {
        sortedPoints4 points;
        points.x = sorted.x;
        points.y = sorted.y;
        points.theta = sorted.theta;
        mergeSort(points, 0, points.theta.size() - 1, graphical);
        return points;
    }
# endif // ALGORITHMS_MERGE_SORT