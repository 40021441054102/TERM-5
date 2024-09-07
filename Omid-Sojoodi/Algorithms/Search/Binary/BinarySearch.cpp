# ifndef ALGORITHMS_OMID_SOJOODI_SEARCH_BINARY
    # include "BinarySearch.hpp"
    //-- Constructor
    BinarySearch::BinarySearch() {
        std::cout << LOG << "Binary Search Algorithm has been initialized." << std::endl;
    }
    //-- Set Data
    void BinarySearch::setData(
        std::vector<box> _boxes,
        std::vector<int> array,
        cv::Mat _window,
        int _target
    ) {
        _window.copyTo(window);
        target = _target;
        boxes = _boxes;
        data = array;
    }
    //-- Search
    int BinarySearch::getFound(bool graphical = true) {
        int left = 0;
        int right = data.size() - 1;
        int middle = 0;
        cv::Mat tmp, tmp1;
        cv::rectangle(
            tmp,
            cv::Point(
                boxes[middle].topLeft.x,
                boxes[middle].topLeft.y
            ),
            cv::Point(
                boxes[middle].bottomRight.x,
                boxes[middle].bottomRight.y
            ),
            cv::Scalar(0, 100, 200),
            cv::FILLED,
            cv::LINE_AA
        );
        cv::Point last;
        if (graphical) {
            window.copyTo(tmp);
            while(left <= right) {
                middle = (left + right) / 2;
                if (data[middle] == target) {
                    tmp.copyTo(tmp1);
                    cv::rectangle(
                        tmp1,
                        cv::Point(
                            boxes[middle].topLeft.x,
                            boxes[middle].topLeft.y
                        ),
                        cv::Point(
                            boxes[middle].bottomRight.x,
                            boxes[middle].bottomRight.y
                        ),
                        cv::Scalar(0, 100, 255),
                        cv::FILLED,
                        cv::LINE_AA
                    );
                    cv::rectangle(
                        tmp,
                        cv::Point(
                            boxes[middle].topLeft.x,
                            boxes[middle].topLeft.y
                        ),
                        cv::Point(
                            boxes[middle].bottomRight.x,
                            boxes[middle].bottomRight.y
                        ),
                        cv::Scalar(0, 100, 200),
                        cv::FILLED,
                        cv::LINE_AA
                    );
                    cv::line(
                        tmp,
                        last,
                        cv::Point(
                            (boxes[middle].topLeft.x + boxes[middle].bottomRight.x) / 2,
                            (boxes[middle].topLeft.y + boxes[middle].bottomRight.y) / 2
                        ),
                        cv::Scalar(0, 100, 150),
                        3,
                        cv::LINE_AA
                    );
                    cv::imshow(WINDOW_NAME, tmp1);
                    cv::waitKey(0);
                    return middle;
                } else if (data[middle] > target) {
                    tmp.copyTo(tmp1);
                    cv::rectangle(
                        tmp1,
                        cv::Point(
                            boxes[middle].topLeft.x,
                            boxes[middle].topLeft.y
                        ),
                        cv::Point(
                            boxes[middle].bottomRight.x,
                            boxes[middle].bottomRight.y
                        ),
                        cv::Scalar(0, 100, 255),
                        cv::FILLED,
                        cv::LINE_AA
                    );
                    cv::rectangle(
                        tmp,
                        cv::Point(
                            boxes[middle].topLeft.x,
                            boxes[middle].topLeft.y
                        ),
                        cv::Point(
                            boxes[middle].bottomRight.x,
                            boxes[middle].bottomRight.y
                        ),
                        cv::Scalar(0, 100, 200),
                        cv::FILLED,
                        cv::LINE_AA
                    );
                    cv::line(
                        tmp,
                        last,
                        cv::Point(
                            (boxes[middle].topLeft.x + boxes[middle].bottomRight.x) / 2,
                            (boxes[middle].topLeft.y + boxes[middle].bottomRight.y) / 2
                        ),
                        cv::Scalar(0, 100, 150),
                        3,
                        cv::LINE_AA
                    );
                    cv::imshow(WINDOW_NAME, tmp1);
                    cv::waitKey(100);
                    right = middle - 1;
                } else {
                    tmp.copyTo(tmp1);
                    cv::rectangle(
                        tmp1,
                        cv::Point(
                            boxes[middle].topLeft.x,
                            boxes[middle].topLeft.y
                        ),
                        cv::Point(
                            boxes[middle].bottomRight.x,
                            boxes[middle].bottomRight.y
                        ),
                        cv::Scalar(0, 100, 255),
                        cv::FILLED,
                        cv::LINE_AA
                    );
                    cv::rectangle(
                        tmp,
                        cv::Point(
                            boxes[middle].topLeft.x,
                            boxes[middle].topLeft.y
                        ),
                        cv::Point(
                            boxes[middle].bottomRight.x,
                            boxes[middle].bottomRight.y
                        ),
                        cv::Scalar(0, 100, 200),
                        cv::FILLED,
                        cv::LINE_AA
                    );
                    cv::line(
                        tmp,
                        last,
                        cv::Point(
                            (boxes[middle].topLeft.x + boxes[middle].bottomRight.x) / 2,
                            (boxes[middle].topLeft.y + boxes[middle].bottomRight.y) / 2
                        ),
                        cv::Scalar(0, 100, 150),
                        3,
                        cv::LINE_AA
                    );
                    cv::imshow(WINDOW_NAME, tmp1);
                    cv::waitKey(100);
                    left = middle + 1;
                }
                last = cv::Point(
                    (boxes[middle].topLeft.x + boxes[middle].bottomRight.x) / 2,
                    (boxes[middle].topLeft.y + boxes[middle].bottomRight.y) / 2
                );
            }
            return -1;
        } else {
            while(left <= right) {
                middle = (left + right) / 2;
                if (data[middle] == target) {
                    return middle;
                }
                else if (data[middle] > target) {
                    right = middle - 1;
                }
                else {
                    left = middle + 1;
                }
            }
            return -1;
        }
    }
# endif // ALGORITHMS_OMID_SOJOODI_SEARCH_BINARY