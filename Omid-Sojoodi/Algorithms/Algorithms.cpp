# ifndef ALGORITHMS_OMID_SOJOODI
    # include "Algorithms.hpp"
    //-- Define Colors Vector
    std::vector<cv::Scalar> height_colors = {
        cv::Scalar(2, 2, 43),
        cv::Scalar(2, 2, 89),
        cv::Scalar(2, 2, 136),
        cv::Scalar(2, 2, 181),
        cv::Scalar(2, 2, 192),
        cv::Scalar(2, 41, 192),
        cv::Scalar(2, 106, 192),
        cv::Scalar(2, 119, 192),
        cv::Scalar(2, 168, 192),
        cv::Scalar(2, 193, 174),
        cv::Scalar(2, 193, 137),
        cv::Scalar(2, 193, 143),
        cv::Scalar(2, 193, 94),
        cv::Scalar(2, 193, 42),
        cv::Scalar(93, 193, 1),
        cv::Scalar(152, 193, 1),
        cv::Scalar(193, 193, 1),
        cv::Scalar(193, 2, 1)
    };
    std::vector<double> heights = {
        5.5,
        5,
        4.7,
        4.3,
        3.9,
        3.5,
        3.2,
        2.8,
        2.5,
        2.2,
        1.9,
        1.6,
        1.3,
        1,
        0.8,
        0.6,
        0.4,
        0.2
    };
    bool isColorBetween(const cv::Scalar& color, const cv::Scalar& lowerBound, const cv::Scalar& upperBound) {
        // Create a result scalar with the same type as the input scalars
        cv::Scalar result(color[0], color[1], color[2], color[3]);

        // Use cv::inRange to check if the color is within the specified range
        cv::inRange(color, lowerBound, upperBound, result);

        // Check if all channels are within the specified range
        return cv::countNonZero(result) == 4;  // Assuming 4 channels (including alpha)
    }
    //-- Constructor
    Algorithms::Algorithms() {
        std::cout << LOG "Algorithms Module Loaded Successfully!" << std::endl;
        //-- Initialize Random Data
        generateRandomData(AMOUNT_OF_POINTS, WINDOW_WIDTH / 10, WINDOW_WIDTH - WINDOW_WIDTH / 10);
        start_selected = false;
        end_selected = false;
        p1_selected = false;
        p2_selected = false;
        ready = false;
    }
    //-- Generate Random Data
    void Algorithms::generateRandomData(
        int size,
        int min,
        int max
    ) {
        std::cout << LOG "Generating Random Data ..." << std::endl;
        std::random_device _random;
        std::default_random_engine eng(_random());
        std::uniform_int_distribution<int> distr(min, max);
        for (int i = 0; i < size; i++) {
            Point point;
            point.x = distr(eng);
            point.y = distr(eng);
            point.theta = 0;
            graphics.points.push_back(point);
        }
        std::cout << TAB SUCCESS "Random Data Generated Successfully!" << std::endl;
    }
    //-- Generate Chess Board
    void Algorithms::generateChessBoard(
        int size = 8,
        int graphic_mode = GRAPHICS_FOR_SORTS
    ) {
        std::random_device _random;
        std::default_random_engine eng(_random());
        std::uniform_int_distribution<int> _red(0, 100);
        std::uniform_int_distribution<int> _green(0, 255);
        std::uniform_int_distribution<int> _blue(100, 255);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                // std::uniform_int_distribution<int> _red(i * 255 / size, j * 255 / size);
                // std::uniform_int_distribution<int> _green(j * 255 / size, i * 255 / size);
                // std::uniform_int_distribution<int> _blue(i * 255 / size, j * 255 / size);
                // if (i >  j) {
                //     std::uniform_int_distribution<int> _red(j * 255 / size, i * 255 / size);
                //     std::uniform_int_distribution<int> _green(j * 255 / size, i * 255 / size);
                //     std::uniform_int_distribution<int> _blue(j * 255 / size, i * 255 / size);
                // } else {
                //     std::uniform_int_distribution<int> _red(i * 255 / size, j * 255 / size);
                //     std::uniform_int_distribution<int> _green(i * 255 / size, j * 255 / size);
                //     std::uniform_int_distribution<int> _blue(i * 255 / size, j * 255 / size);
                // }
                Box box;
                box.topLeft.x = i * WINDOW_WIDTH / size;
                box.topLeft.y = j * WINDOW_HEIGHT / size;
                box.bottomRight.x = (i + 1) * WINDOW_WIDTH / size;
                box.bottomRight.y = (j + 1) * WINDOW_HEIGHT / size;
                box.center.x = (box.topLeft.x + box.bottomRight.x) / 2;
                box.center.y = (box.topLeft.y + box.bottomRight.y) / 2;
                box.width = box.bottomRight.x - box.topLeft.x;
                box.height = box.bottomRight.y - box.topLeft.y;
                if (graphic_mode == GRAPHICS_FOR_SEARCHS) {
                    box.color = cv::Scalar(_blue(eng), _green(eng), 0);
                } else if (graphic_mode == GRAPHICS_FOR_CHESS) {
                    if ((i + j) % 2 == 0) {
                        box.color = cv::Scalar(46, 58, 87);
                    }
                    else {
                        box.color = cv::Scalar(93, 120, 138);
                    }
                }
                graphics.boxes.push_back(box);
            }
        }
    }
    //-- Mouse Callback
    void Algorithms::onMouseCallback(int event, int x, int y, int flags, void* userdata) {
        static_cast<Algorithms*>(userdata)->onMouse(event, x, y, flags);
    }
    //-- Mouse Events
    void Algorithms::onMouse(int event, int x, int y, int flags) {
        if (event == cv::EVENT_LBUTTONDOWN) {
            if (ready) {
                if (start_selected == false) {
                    for (int i = 0; i < movingOnGrid.areas.size(); i++) {
                        if (x > movingOnGrid.areas[i].topLeft.x && x < movingOnGrid.areas[i].bottomRight.x) {
                            if (y > movingOnGrid.areas[i].topLeft.y && y < movingOnGrid.areas[i].bottomRight.y) {
                                start.x = movingOnGrid.areas[i].topLeft.x;
                                start.y = movingOnGrid.areas[i].topLeft.y;
                                cv::rectangle(
                                    graphics.window,
                                    cv::Point(movingOnGrid.areas[i].topLeft.x, movingOnGrid.areas[i].topLeft.y),
                                    cv::Point(movingOnGrid.areas[i].bottomRight.x, movingOnGrid.areas[i].bottomRight.y),
                                    cv::Scalar(0, 0, 255),
                                    cv::FILLED,
                                    cv::LINE_AA,
                                    0
                                );
                                start_selected = true;
                                break;
                            }
                        }
                    }
                } else {
                    if (end_selected == false) {
                        for (int i = 0; i < movingOnGrid.areas.size(); i++) {
                            if (x > movingOnGrid.areas[i].topLeft.x && x < movingOnGrid.areas[i].bottomRight.x) {
                                if (y > movingOnGrid.areas[i].topLeft.y && y < movingOnGrid.areas[i].bottomRight.y) {
                                    end.x = movingOnGrid.areas[i].topLeft.x;
                                    end.y = movingOnGrid.areas[i].topLeft.y;
                                    cv::rectangle(
                                        graphics.window,
                                        cv::Point(movingOnGrid.areas[i].topLeft.x, movingOnGrid.areas[i].topLeft.y),
                                        cv::Point(movingOnGrid.areas[i].bottomRight.x, movingOnGrid.areas[i].bottomRight.y),
                                        cv::Scalar(0, 0, 255),
                                        cv::FILLED,
                                        cv::LINE_AA,
                                        0
                                    );
                                    end_selected = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            } else {
                if (p1_selected == false) {
                    p1.x = x;
                    p1.y = y;
                    cv::circle(graphics.window, cv::Point(x, y), 25, cv::Scalar(0, 140, 0), 2, cv::LINE_AA, 0);
                    cv::rectangle(graphics.window, cv::Point(x - 3, y - 3), cv::Point(x + 3, y + 3), cv::Scalar(0, 140, 0), cv::FILLED, cv::LINE_4, 0);
                    p1_selected = true;
                } else {
                    if (p2_selected == false) {
                        p2.x = x;
                        p2.y = y;
                        cv::circle(graphics.window, cv::Point(x, y), 25, cv::Scalar(0, 140, 0), 2, cv::LINE_AA, 0);
                        cv::rectangle(graphics.window, cv::Point(x - 3, y - 3), cv::Point(x + 3, y + 3), cv::Scalar(0, 140, 0), cv::FILLED, cv::LINE_4, 0);
                        cv::rectangle(
                            graphics.window,
                            cv::Point(p1.x, p1.y),
                            cv::Point(p2.x, p2.y),
                            cv::Scalar(0, 200, 0),
                            3,
                            cv::LINE_AA,
                            0
                        );
                        p2_selected = true;
                    }
                }
            }
            cv::imshow(WINDOW_NAME, graphics.window);
        } else if (event == cv::EVENT_RBUTTONDOWN) {
        } else if (event == cv::EVENT_MOUSEMOVE) {
            cv::Mat tmpMat;
            graphics.window.copyTo(tmpMat);
            if (ready == true) {
                for (int i = 0; i < movingOnGrid.areas.size(); i++) {
                    if (x > movingOnGrid.areas[i].topLeft.x && x < movingOnGrid.areas[i].bottomRight.x) {
                        if (y > movingOnGrid.areas[i].topLeft.y && y < movingOnGrid.areas[i].bottomRight.y) {
                            cv::rectangle(
                                tmpMat,
                                cv::Point(movingOnGrid.areas[i].topLeft.x, movingOnGrid.areas[i].topLeft.y),
                                cv::Point(movingOnGrid.areas[i].bottomRight.x, movingOnGrid.areas[i].bottomRight.y),
                                cv::Scalar(0, 0, 255),
                                3,
                                cv::LINE_AA,
                                0
                            );
                            cv::imshow(WINDOW_NAME, tmpMat);
                            break;
                        }
                    }
                }
            } else {
                if (p1_selected && p2_selected == false) {
                    cv::rectangle(
                        tmpMat,
                        cv::Point(p1.x, p1.y),
                        cv::Point(x, y),
                        cv::Scalar(0, 140, 255),
                        3,
                        cv::LINE_AA,
                        0
                    );
                }
                cv::circle(tmpMat, cv::Point(x, y), 25, cv::Scalar(0, 0, 255), 2, cv::LINE_AA, 0);
                cv::rectangle(tmpMat, cv::Point(x - 3, y - 3), cv::Point(x + 3, y + 3), cv::Scalar(0, 0, 140), cv::FILLED, cv::LINE_4, 0);
            }
            cv::imshow(WINDOW_NAME, tmpMat);
        }
    }
    //-- Generate Map Data
    void Algorithms::generateMapData(
        int size = 30,
        int graphic_mode = GRAPHICS_FOR_MAPS,
        int data_generation_method = RANDOM_DATA
    ) {
        if (data_generation_method == INPUT_FILE) {
            //-- Load Map Image and Open Cropper
            graphics.window = cv::imread(MAP_IMAGE, cv::IMREAD_COLOR);
            cv::Mat topologicalMap = cv::imread(TOPOLOGY_IMAGE, cv::IMREAD_COLOR);
            //-- Resize to Smaller
            cv::resize(graphics.window, graphics.window, cv::Size(graphics.window.cols * 0.9, graphics.window.rows * 0.9));
            cv::resize(topologicalMap, topologicalMap, cv::Size(topologicalMap.cols * 0.9, topologicalMap.rows * 0.9));
            //-- Save First Frame
            cv::Mat tmp;
            graphics.window.copyTo(tmp);
            cv::imshow(WINDOW_NAME, graphics.window);
            //-- Move Window to Center of Screen
            cv::moveWindow(
                WINDOW_NAME,
                graphics.windowPositionCenter.x - graphics.window.cols / 2,
                graphics.windowPositionCenter.y - graphics.window.rows / 2
            );
            //-- Set Mouse Callback
            cv::setMouseCallback(WINDOW_NAME, onMouseCallback, this);
            cv::waitKey(0);
            std::cout << LOG "Press Any Key to Continue ..." << std::endl;
            //-- Disable Mouse Callback
            cv::setMouseCallback(WINDOW_NAME, nullptr, nullptr);
            //-- Crop Selected Area
            tmp.copyTo(graphics.window);
            //-- Swap Points if Needed
            if (p1.x > p2.x) {
                int tmp = p1.x;
                p1.x = p2.x;
                p2.x = tmp;
            } else {
                if (p1.y > p2.y) {
                    int tmp = p1.y;
                    p1.y = p2.y;
                    p2.y = tmp;
                }
            }
            cv::Rect rect(p1.x, p1.y, p2.x - p1.x, p2.y - p1.y);
            cv::Mat croppedImage = graphics.window(rect);
            cv::Mat croppedTopologicalMap = topologicalMap(rect);
            cv::imshow(WINDOW_NAME, croppedImage);
            cv::waitKey(1);
            cv::moveWindow(
                WINDOW_NAME,
                graphics.windowPositionCenter.x - abs((p1.x - p2.x)) / 2,
                graphics.windowPositionCenter.y - (abs(p1.y - p2.y)) / 2
            );
            //-- Show Topological Map
            croppedImage.copyTo(tmp);
            for (int i = 0; i < croppedTopologicalMap.rows; i++) {
                for (int j = 0; j < croppedTopologicalMap.cols; j++) {
                    croppedImage.at<cv::Vec3b>(i, j)[0] = croppedTopologicalMap.at<cv::Vec3b>(i, j)[0];
                    croppedImage.at<cv::Vec3b>(i, j)[1] = croppedTopologicalMap.at<cv::Vec3b>(i, j)[1];
                    croppedImage.at<cv::Vec3b>(i, j)[2] = croppedTopologicalMap.at<cv::Vec3b>(i, j)[2];
                }
                if (i % 15 == 0) {
                    cv::imshow(WINDOW_NAME, croppedImage);
                    cv::waitKey(1);
                }
            }
            tmp.copyTo(croppedImage);
            croppedTopologicalMap.copyTo(tmp);
            //-- Show Topological Map
            for (int i = 0; i < croppedImage.rows; i++) {
                for (int j = 0; j < croppedImage.cols; j++) {
                    croppedTopologicalMap.at<cv::Vec3b>(i, j)[0] = croppedImage.at<cv::Vec3b>(i, j)[0];
                    croppedTopologicalMap.at<cv::Vec3b>(i, j)[1] = croppedImage.at<cv::Vec3b>(i, j)[1];
                    croppedTopologicalMap.at<cv::Vec3b>(i, j)[2] = croppedImage.at<cv::Vec3b>(i, j)[2];
                }
                if (i % 15 == 0) {
                    cv::imshow(WINDOW_NAME, croppedTopologicalMap);
                    cv::waitKey(1);
                }
            }
            cv::imshow(WINDOW_NAME, croppedTopologicalMap);
            tmp.copyTo(croppedTopologicalMap);
            // cv::waitKey(0);
            //-- Generate Square Areas on Map
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    Box box;
                    box.topLeft.x = i * croppedImage.cols / size;
                    box.topLeft.y = j * croppedImage.rows / size;
                    box.bottomRight.x = (i + 1) * croppedImage.cols / size;
                    box.bottomRight.y = (j + 1) * croppedImage.rows / size;
                    box.center.x = (box.topLeft.x + box.bottomRight.x) / 2;
                    box.center.y = (box.topLeft.y + box.bottomRight.y) / 2;
                    box.width = box.bottomRight.x - box.topLeft.x;
                    box.height = box.bottomRight.y - box.topLeft.y;
                    box.color = cv::Scalar(0, 0, 0);
                    graphics.boxes.push_back(box);
                    cv::rectangle(
                        croppedImage,
                        cv::Point(box.topLeft.x, box.topLeft.y),
                        cv::Point(box.bottomRight.x, box.bottomRight.y),
                        box.color,
                        1,
                        cv::LINE_AA,
                        0
                    );
                    croppedImage.copyTo(tmp);
                    // for (int ii = box.topLeft.y; ii < box.bottomRight.y - box.topLeft.y; ii++) {
                    //     for (int jj = box.topLeft.x; jj < box.bottomRight.x - box.topLeft.x; jj++) {
                    //         croppedImage.at<cv::Vec3b>(ii, jj)[0] = croppedTopologicalMap.at<cv::Vec3b>(ii, jj)[0];
                    //         croppedImage.at<cv::Vec3b>(ii, jj)[1] = croppedTopologicalMap.at<cv::Vec3b>(ii, jj)[1];
                    //         croppedImage.at<cv::Vec3b>(ii, jj)[2] = croppedTopologicalMap.at<cv::Vec3b>(ii, jj)[2];
                    //     }
                    // }
                }
                cv::imshow(WINDOW_NAME, croppedImage);
                cv::waitKey(1);
            }
            croppedImage.copyTo(tmp);
            //-- Calculate Block Weights Using Topological Colors
            for (int i = 0; i < graphics.boxes.size(); i++) {
                for (int j = graphics.boxes[i].topLeft.y; j < graphics.boxes[i].bottomRight.y; j++) {
                    for (int k = graphics.boxes[i].topLeft.x; k < graphics.boxes[i].bottomRight.x; k++) {
                        graphics.boxes[i].color[0] += croppedTopologicalMap.at<cv::Vec3b>(j, k)[0];
                        graphics.boxes[i].color[1] += croppedTopologicalMap.at<cv::Vec3b>(j, k)[1];
                        graphics.boxes[i].color[2] += croppedTopologicalMap.at<cv::Vec3b>(j, k)[2];
                    }
                }
                graphics.boxes[i].color[0] /= (graphics.boxes[i].width * graphics.boxes[i].height);
                graphics.boxes[i].color[1] /= (graphics.boxes[i].width * graphics.boxes[i].height);
                graphics.boxes[i].color[2] /= (graphics.boxes[i].width * graphics.boxes[i].height);
            }
            //-- Show Weights
            for (int i = 0; i < graphics.boxes.size(); i++) {
                cv::rectangle(
                    croppedImage,
                    cv::Point(graphics.boxes[i].topLeft.x, graphics.boxes[i].topLeft.y),
                    cv::Point(graphics.boxes[i].bottomRight.x, graphics.boxes[i].bottomRight.y),
                    graphics.boxes[i].color,
                    cv::FILLED,
                    cv::LINE_AA,
                    0
                );
                area tmpArea;
                tmpArea.bottomRight = graphics.boxes[i].bottomRight;
                tmpArea.topLeft = graphics.boxes[i].topLeft;
                tmpArea.weight = (graphics.boxes[i].color[0] + graphics.boxes[i].color[1] + graphics.boxes[i].color[2]) / 3;
                movingOnGrid.areas.push_back(tmpArea);
                // bool assigned = false;
                // for (int j = 0; j < height_colors.size(); j++) {
                //     cv::Scalar tmpScalar = cv::Scalar(
                //         static_cast<int>(graphics.boxes[i].color[0]), 
                //         static_cast<int>(graphics.boxes[i].color[1]),
                //         static_cast<int>(graphics.boxes[i].color[2]),
                //         static_cast<int>(graphics.boxes[i].color[3])
                //     );
                //     std::cout << tmpScalar << " " << height_colors[j] << " " << height_colors[j + 1] << std::endl;
                //     if (isColorBetween(graphics.boxes[i].color, height_colors[j], height_colors[j + 1])) {
                //         std::cout << "debug" << std::endl;
                //         tmpArea.weight = heights[j];
                //         assigned = true;
                //         break;
                //     }
                // }
                // if (assigned == false) {
                //     tmpArea.weight = 0;
                //     std::cout << WARNING "Area " << i << " Weight: " << tmpArea.weight << std::endl;
                //     cv::circle(
                //         croppedImage,
                //         cv::Point(graphics.boxes[i].center.x, graphics.boxes[i].center.y),
                //         10,
                //         cv::Scalar(0, 0, 255),
                //         cv::FILLED,
                //         cv::LINE_AA,
                //         0
                //     );
                // }
                // std::cout << INFO "Area " << i << " Weight: " << tmpArea.weight << std::endl;
                if (i % (size - 1) == 0) {
                    cv::imshow(WINDOW_NAME, croppedImage);
                    cv::waitKey(1);
                }
            }
            tmp.copyTo(croppedImage);
            croppedImage.copyTo(graphics.window);
            cv::imshow(WINDOW_NAME, croppedImage);
            movingOnGrid.setData(size);
            //-- Select Start and End Point
            cv::setMouseCallback(WINDOW_NAME, onMouseCallback, this);
            ready = true;
            cv::waitKey(0);
            cv::setMouseCallback(WINDOW_NAME, nullptr, nullptr);
        }
    }
# endif // ALGORITHMS_OMID_SOJOODI