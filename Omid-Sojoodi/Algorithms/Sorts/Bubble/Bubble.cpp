# ifndef ALGORITHMS_BUBBLE_SORT
    # include "Bubble.hpp"
    //-- Constructor
    Bubble::Bubble() {
        std::cout << LOG "Bubble Sort Algorithm Loaded Successfully!" << std::endl;
    }
    //-- Set Data
    void Bubble::setData(cv::Mat _window, std::vector<double> _theta, std::vector<int> _x, std::vector<int> _y) {
        _window.copyTo(window);
        sorted.theta = _theta;
        sorted.x = _x;
        sorted.y = _y;
    }
    //-- Sort
    sortedPoints Bubble::getSorted() {
        std::vector<double> theta = sorted.theta;
        std::vector<int> x = sorted.x;
        std::vector<int> y = sorted.y;
        cv::Mat tmp, tmp1;
        window.copyTo(tmp);
        for (int i = 0; i < theta.size(); i++) {
            for (int j = 0; j < theta.size() - i - 1; j++) {
                tmp.copyTo(tmp1);
                cv::circle(
                    tmp1,
                    cv::Point(x[j], y[j]),
                    7,
                    cv::Scalar(0, 100, 255),
                    1,
                    cv::LINE_AA
                );
                if (theta[j] > theta[j + 1]) {
                    std::swap(theta[j], theta[j + 1]);
                    std::swap(x[j], x[j + 1]);
                    std::swap(y[j], y[j + 1]);
                    cv::line(
                        tmp1,
                        cv::Point(x[j], y[j]),
                        cv::Point(x[j + 1], y[j + 1]),
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
            }
            cv::imshow(WINDOW_NAME, tmp);
            cv::waitKey(1);
            window.copyTo(tmp);
        }
        sortedPoints output;
        output.theta = theta;
        output.x = x;
        output.y = y;
        return output;
    }
# endif // ALGORITHMS_BUBBLE_SORT