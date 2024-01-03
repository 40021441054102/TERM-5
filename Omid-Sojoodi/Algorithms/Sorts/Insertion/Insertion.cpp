# ifndef ALGORITHMS_INSERTION_SORT
    # include "Insertion.hpp"
    //-- Constructor
    Insertion::Insertion() {
        std::cout << LOG "Insertion Sort Algorithm Loaded Successfully!" << std::endl;
    }
    //-- Set Data
    void Insertion::setData(cv::Mat _window, std::vector<double> _theta, std::vector<int> _x, std::vector<int> _y) {
        _window.copyTo(window);
        sorted.theta = _theta;
        sorted.x = _x;
        sorted.y = _y;
    }
    //-- Sort
    sortedPoints2 Insertion::getSorted() {
        std::vector<double> theta = sorted.theta;
        std::vector<int> x = sorted.x;
        std::vector<int> y = sorted.y;
        cv::Mat tmp, tmp1;
        window.copyTo(tmp);
        for (int i = 1; i < theta.size(); i++) {
            double key = theta[i];
            int keyX = x[i];
            int keyY = y[i];
            int j = i - 1;
            while (j >= 0 && theta[j] > key) {
                tmp.copyTo(tmp1);
                cv::circle(
                    tmp1,
                    cv::Point(x[j], y[j]),
                    7,
                    cv::Scalar(0, 100, 255),
                    1,
                    cv::LINE_AA
                );
                theta[j + 1] = theta[j];
                x[j + 1] = x[j];
                y[j + 1] = y[j];
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
                j--;
            }
            theta[j + 1] = key;
            x[j + 1] = keyX;
            y[j + 1] = keyY;
            cv::imshow(WINDOW_NAME, tmp);
            cv::waitKey(1);
            window.copyTo(tmp);
        }
        sortedPoints2 output;
        output.theta = theta;
        output.x = x;
        output.y = y;
        return output;
    }
# endif // ALGORITHMS_INSERTION_SORT