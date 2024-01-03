# ifndef ALGORITHMS_SELECTION_SORT
    # include "Selection.hpp"
    //-- Constructor
    Selection::Selection() {
        std::cout << LOG "Selection Sort Algorithm Loaded Successfully!" << std::endl;
    }
    //-- Set Data
    void Selection::setData(cv::Mat _window, std::vector<double> _theta, std::vector<int> _x, std::vector<int> _y) {
        _window.copyTo(window);
        sorted.theta = _theta;
        sorted.x = _x;
        sorted.y = _y;
    }
    //-- Sort
    sortedPoints3 Selection::getSorted(bool graphical) {
        std::vector<double> theta = sorted.theta;
        std::vector<int> x = sorted.x;
        std::vector<int> y = sorted.y;
        if (graphical) {
            cv::Mat tmp, tmp1;
            window.copyTo(tmp);
            for (int i = 0; i < theta.size() - 1; i++) {
                int minIndex = i;
                for (int j = i + 1; j < theta.size(); j++) {
                    tmp.copyTo(tmp1);
                    cv::circle(
                        tmp1,
                        cv::Point(x[j], y[j]),
                        7,
                        cv::Scalar(0, 100, 255),
                        1,
                        cv::LINE_AA
                    );
                    if (theta[j] < theta[minIndex]) {
                        minIndex = j;
                    }
                    cv::line(
                        tmp1,
                        cv::Point(x[j], y[j]),
                        cv::Point(x[minIndex], y[minIndex]),
                        cv::Scalar(0, 120, 120),
                        1,
                        cv::LINE_4
                    );
                    cv::line(
                        tmp,
                        cv::Point(x[j], y[j]),
                        cv::Point(x[i], y[i]),
                        cv::Scalar(0, 120, 0),
                        1,
                        cv::LINE_4
                    );
                    cv::imshow(WINDOW_NAME, tmp1);
                    cv::waitKey(1);
                }
                std::swap(theta[minIndex], theta[i]);
                std::swap(x[minIndex], x[i]);
                std::swap(y[minIndex], y[i]);
                cv::imshow(WINDOW_NAME, tmp);
                cv::waitKey(1);
                window.copyTo(tmp);
            }
        } else {
            for (int i = 0; i < theta.size() - 1; i++) {
                int minIndex = i;
                for (int j = i + 1; j < theta.size(); j++) {
                    if (theta[j] < theta[minIndex]) {
                        minIndex = j;
                    }
                }
                std::swap(theta[minIndex], theta[i]);
                std::swap(x[minIndex], x[i]);
                std::swap(y[minIndex], y[i]);
            }
        
        }
        sorted.theta = theta;
        sorted.x = x;
        sorted.y = y;
        return sorted;
    }
# endif // ALGORITHMS_SELECTION_SORT