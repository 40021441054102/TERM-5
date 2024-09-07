# ifndef ALGORITHMS_OMID_SOJOODI
    //-- Include Needed Libraries
    # include <iostream>
    # include <chrono>
    //-- Include Algorithms Module
    # include "Algorithms/Algorithms.hpp"
    //-- Define Colors
    # define CYAN "\033[38;2;0;255;255m"
    # define CYAN2 "\033[38;2;0;170;170m"
    # define GRAY "\033[38;2;170;170;170m"
    # define YELLOW "\033[38;2;255;255;0m"
    # define YELLOW2 "\033[38;2;120;120;0m"
    # define ERROR "\033[38;2;255;0;0m[ERROR]\033[0m "
    # define RESET "\033[0m"
    //-- Main Function
    int main() {
        cv::Mat tmp, tmp2, show, mainWindow;
        int choice = -1;
        Algorithms algorithms;
        algorithms.graphics.window.copyTo(mainWindow);
        system("sleep 0.2");
        while(true) {
            if (choice == 0) {
                cv::destroyAllWindows();
                break;
            }
            std::cout << "\033[2J\x1b[H" << std::endl;
            std::cout << CYAN "Available Algorithms:" RESET << std::endl;
            std::cout << CYAN "1." CYAN2 " Sorts" RESET << std::endl;
            std::cout << CYAN "2." CYAN2 " Binary Search" RESET << std::endl;
            std::cout << CYAN "3." CYAN2 " Moving on Grid" RESET << std::endl;
            // std::cout << CYAN "2." CYAN2 " TSP" RESET << std::endl;
            // std::cout << CYAN "3." CYAN2 " 8 Queens" RESET << std::endl;
            // std::cout << CYAN "4." CYAN2 " Min Max" RESET << std::endl;
            std::cout << CYAN "0." CYAN2 " Exit" RESET << std::endl;
            std::cout << GRAY "Please Select An Algorithm : " RESET; std::cin >> choice;
            switch (choice) {
                case 1: {
                    mainWindow.copyTo(algorithms.graphics.window);
                    algorithms.graphics.showPoints();
                    while (true) {
                        std::cout << "\033[2J\x1b[H" << std::endl;
                        std::cout << YELLOW "Available Sorts (Sort by Theta from Lowest Point) :" RESET << std::endl;
                        std::cout << YELLOW "1." YELLOW2 " Bubble Sort" RESET << std::endl;
                        std::cout << YELLOW "2." YELLOW2 " Insertion Sort" RESET << std::endl;
                        std::cout << YELLOW "3." YELLOW2 " Selection Sort" RESET << std::endl;
                        std::cout << YELLOW "4." YELLOW2 " Merge Sort" RESET << std::endl;
                        std::cout << YELLOW "5." YELLOW2 " Quick Sort" RESET << std::endl;
                        std::cout << YELLOW "6." YELLOW2 " Heap Sort" RESET << std::endl;
                        std::cout << YELLOW "0." YELLOW2 " Back" RESET << std::endl;
                        //-- Find Lowest Point
                        std::cout << LOG "Finding Lowest Point ..." << std::endl;
                        int lowestPointIndex = 0;
                        algorithms.graphics.window.copyTo(tmp);
                        for (int i = 1; i < algorithms.graphics.points.size(); i++) {
                            if (algorithms.graphics.points[i].y > algorithms.graphics.points[lowestPointIndex].y) {
                                cv::circle(
                                    algorithms.graphics.window,
                                    cv::Point(
                                        algorithms.graphics.points[lowestPointIndex].x,
                                        algorithms.graphics.points[lowestPointIndex].y
                                    ),
                                    10,
                                    cv::Scalar(0, 170, 170),
                                    1,
                                    cv::LINE_8
                                );
                                cv::line(
                                    algorithms.graphics.window,
                                    cv::Point(
                                        algorithms.graphics.points[lowestPointIndex].x,
                                        algorithms.graphics.points[lowestPointIndex].y
                                    ),
                                    cv::Point(
                                        algorithms.graphics.points[i].x,
                                        algorithms.graphics.points[i].y
                                    ),
                                    cv::Scalar(0, 120, 120),
                                    1,
                                    cv::LINE_4
                                );
                                lowestPointIndex = i;
                            }
                            cv::circle(
                                algorithms.graphics.window,
                                cv::Point(
                                    algorithms.graphics.points[lowestPointIndex].x,
                                    algorithms.graphics.points[lowestPointIndex].y
                                ),
                                7,
                                cv::Scalar(0, 255, 0),
                                1,
                                cv::LINE_8
                                );
                            cv::imshow(WINDOW_NAME, algorithms.graphics.window);
                            cv::waitKey(1);
                        }
                        tmp.copyTo(algorithms.graphics.window);
                        std::cout << LOG "Lowest Point Found Successfully at (" << algorithms.graphics.points.at(lowestPointIndex).x << ", " << algorithms.graphics.points.at(lowestPointIndex).y << ")" << std::endl;
                        std::cout << GRAY "Please Select An Algorithm : " RESET; std::cin >> choice;
                        if (choice == 0) {
                            choice = -1;
                            break;
                        }
                        //-- Calculate Theta of each Point from Lowest Point
                        std::cout << LOG "Calculating Theta of each Point from Lowest Point ..." << std::endl;
                        algorithms.graphics.window.copyTo(tmp);
                        for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                            algorithms.graphics.points[i].theta = atan2(
                                algorithms.graphics.points[i].y - algorithms.graphics.points[lowestPointIndex].y,
                                algorithms.graphics.points[i].x - algorithms.graphics.points[lowestPointIndex].x
                            );
                            cv::circle(
                                algorithms.graphics.window,
                                cv::Point(
                                    algorithms.graphics.points[i].x,
                                    algorithms.graphics.points[i].y
                                ),
                                7,
                                cv::Scalar(120, 120, 0),
                                1,
                                cv::LINE_4
                            );
                            algorithms.graphics.points[i].theta = algorithms.graphics.points[i].theta * 180 / M_PI;
                            algorithms.graphics.window.copyTo(tmp2);
                            cv::line(
                                algorithms.graphics.window,
                                cv::Point(
                                    algorithms.graphics.points[lowestPointIndex].x,
                                    algorithms.graphics.points[lowestPointIndex].y
                                ),
                                cv::Point(
                                    algorithms.graphics.points[i].x,
                                    algorithms.graphics.points[i].y
                                ),
                                cv::Scalar(255, 255, 0),
                                1,
                                cv::LINE_4
                            );
                            cv::imshow(WINDOW_NAME, algorithms.graphics.window);
                            cv::waitKey(1);
                            tmp2.copyTo(algorithms.graphics.window);
                        }
                        cv::imshow(WINDOW_NAME, algorithms.graphics.window);
                        cv::waitKey(1);
                        tmp.copyTo(algorithms.graphics.window);
                        switch(choice) {
                            case 1: {
                                //-- Sort Points by Theta
                                std::cout << LOG "Sorting Points by Theta ..." << std::endl;
                                std::vector<double> thetas;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    thetas.push_back(algorithms.graphics.points[i].theta);
                                }
                                std::vector<int> xPoints;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    xPoints.push_back(algorithms.graphics.points[i].x);
                                }
                                std::vector<int> yPoints;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    yPoints.push_back(algorithms.graphics.points[i].y);
                                }
                                algorithms.sorts.bubble.setData(algorithms.graphics.window, thetas, xPoints, yPoints);
                                sortedPoints1 sorted;
                                sorted = algorithms.sorts.bubble.getSorted(true);
                                auto start_time = std::chrono::high_resolution_clock::now();
                                sorted = algorithms.sorts.bubble.getSorted(false);
                                auto end_time = std::chrono::high_resolution_clock::now();
                                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
                                // //-- Remove Duplicates
                                // std::cout << LOG "Removing Duplicates ..." << std::endl;
                                // for (int i = 0; i < sorted.theta.size(); i++) {
                                //     for (int j = i + 1; j < sorted.theta.size(); j++) {
                                //         if (sorted.theta[i] == sorted.theta[j]) {
                                //             sorted.theta.erase(sorted.theta.begin() + j);
                                //             sorted.x.erase(sorted.x.begin() + j);
                                //             sorted.y.erase(sorted.y.begin() + j);
                                //             j--;
                                //         }
                                //     }
                                // }
                                //-- Show Sorted Points
                                algorithms.graphics.window.copyTo(show);
                                for (int i = 0; i < sorted.x.size(); i++) {
                                    // std::cout << sorted.theta[i] << std::endl;
                                    cv::circle(
                                        show,
                                        cv::Point(
                                            sorted.x[i],
                                            sorted.y[i]
                                        ),
                                        2,
                                        cv::Scalar(0, 255, 0),
                                        1,
                                        cv::LINE_4
                                    );
                                    cv::putText(
                                        show,
                                        std::to_string(i + 1),
                                        cv::Point(
                                            sorted.x[i] - 11,
                                            sorted.y[i] + 25
                                        ),
                                        cv::FONT_HERSHEY_SIMPLEX,
                                        0.5,
                                        cv::Scalar(255, 255, 255)
                                    );
                                    cv::imshow(WINDOW_NAME, show);
                                    cv::waitKey(1);
                                }
                                std::cout << INFO "Time Elapsed: " << duration << " Nano Seconds" << std::endl;
                                cv::waitKey(0);
                                break;
                            }
                            case 2: {
                                //-- Sort Points by Theta
                                std::cout << LOG "Sorting Points by Theta ..." << std::endl;
                                std::vector<double> thetas;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    thetas.push_back(algorithms.graphics.points[i].theta);
                                }
                                std::vector<int> xPoints;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    xPoints.push_back(algorithms.graphics.points[i].x);
                                }
                                std::vector<int> yPoints;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    yPoints.push_back(algorithms.graphics.points[i].y);
                                }
                                algorithms.sorts.insertion.setData(algorithms.graphics.window, thetas, xPoints, yPoints);
                                sortedPoints2 sorted;
                                sorted = algorithms.sorts.insertion.getSorted(true);
                                auto start_time = std::chrono::high_resolution_clock::now();
                                sorted = algorithms.sorts.insertion.getSorted(false);
                                auto end_time = std::chrono::high_resolution_clock::now();
                                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
                                //-- Show Sorted Points
                                algorithms.graphics.window.copyTo(show);
                                for (int i = 0; i < sorted.x.size(); i++) {
                                    // std::cout << sorted.theta[i] << std::endl;
                                    cv::circle(
                                        show,
                                        cv::Point(
                                            sorted.x[i],
                                            sorted.y[i]
                                        ),
                                        2,
                                        cv::Scalar(0, 255, 0),
                                        1,
                                        cv::LINE_4
                                    );
                                    cv::putText(
                                        show,
                                        std::to_string(i + 1),
                                        cv::Point(
                                            sorted.x[i] - 11,
                                            sorted.y[i] + 25
                                        ),
                                        cv::FONT_HERSHEY_SIMPLEX,
                                        0.5,
                                        cv::Scalar(255, 255, 255)
                                    );
                                    cv::imshow(WINDOW_NAME, show);
                                    cv::waitKey(1);
                                }
                                std::cout << INFO "Time Elapsed: " << duration << " Nano Seconds" << std::endl;
                                cv::waitKey(0);
                                break;
                            }
                            case 3: {
                                //-- Sort Points by Theta
                                std::cout << LOG "Sorting Points by Theta ..." << std::endl;
                                std::vector<double> thetas;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    thetas.push_back(algorithms.graphics.points[i].theta);
                                }
                                std::vector<int> xPoints;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    xPoints.push_back(algorithms.graphics.points[i].x);
                                }
                                std::vector<int> yPoints;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    yPoints.push_back(algorithms.graphics.points[i].y);
                                }
                                algorithms.sorts.selection.setData(algorithms.graphics.window, thetas, xPoints, yPoints);
                                sortedPoints3 sorted;
                                sorted = algorithms.sorts.selection.getSorted(true);
                                auto start_time = std::chrono::high_resolution_clock::now();
                                sorted = algorithms.sorts.selection.getSorted(false);
                                auto end_time = std::chrono::high_resolution_clock::now();
                                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
                                //-- Show Sorted Points
                                algorithms.graphics.window.copyTo(show);
                                for (int i = 0; i < sorted.x.size(); i++) {
                                    // std::cout << sorted.theta[i] << std::endl;
                                    cv::circle(
                                        show,
                                        cv::Point(
                                            sorted.x[i],
                                            sorted.y[i]
                                        ),
                                        2,
                                        cv::Scalar(0, 255, 0),
                                        1,
                                        cv::LINE_4
                                    );
                                    cv::putText(
                                        show,
                                        std::to_string(i + 1),
                                        cv::Point(
                                            sorted.x[i] - 11,
                                            sorted.y[i] + 25
                                        ),
                                        cv::FONT_HERSHEY_SIMPLEX,
                                        0.5,
                                        cv::Scalar(255, 255, 255)
                                    );
                                    cv::imshow(WINDOW_NAME, show);
                                    cv::waitKey(1);
                                }
                                std::cout << INFO "Time Elapsed: " << duration << " Nano Seconds" << std::endl;
                                cv::waitKey(0);
                                break;
                            }
                            case 4: {
                                //-- Sort Points by Theta
                                std::cout << LOG "Sorting Points by Theta ..." << std::endl;
                                std::vector<double> thetas;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    thetas.push_back(algorithms.graphics.points[i].theta);
                                }
                                std::vector<int> xPoints;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    xPoints.push_back(algorithms.graphics.points[i].x);
                                }
                                std::vector<int> yPoints;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    yPoints.push_back(algorithms.graphics.points[i].y);
                                }
                                algorithms.sorts.merge.setData(algorithms.graphics.window, thetas, xPoints, yPoints);
                                sortedPoints4 sorted;
                                sorted = algorithms.sorts.merge.getSorted(true);
                                auto start_time = std::chrono::high_resolution_clock::now();
                                sorted = algorithms.sorts.merge.getSorted(false);
                                auto end_time = std::chrono::high_resolution_clock::now();
                                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
                                //-- Show Sorted Points
                                algorithms.graphics.window.copyTo(show);
                                for (int i = 0; i < sorted.x.size(); i++) {
                                    // std::cout << sorted.theta[i] << std::endl;
                                    cv::circle(
                                        show,
                                        cv::Point(
                                            sorted.x[i],
                                            sorted.y[i]
                                        ),
                                        2,
                                        cv::Scalar(0, 255, 0),
                                        1,
                                        cv::LINE_4
                                    );
                                    cv::putText(
                                        show,
                                        std::to_string(i + 1),
                                        cv::Point(
                                            sorted.x[i] - 11,
                                            sorted.y[i] + 25
                                        ),
                                        cv::FONT_HERSHEY_SIMPLEX,
                                        0.5,
                                        cv::Scalar(255, 255, 255)
                                    );
                                    cv::imshow(WINDOW_NAME, show);
                                    cv::waitKey(1);
                                }
                                std::cout << INFO "Time Elapsed: " << duration << " Nano Seconds" << std::endl;
                                cv::waitKey(0);
                                break;
                            }
                            case 5: {
                                //-- Sort Points by Theta
                                std::cout << LOG "Sorting Points by Theta ..." << std::endl;
                                std::vector<double> thetas;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    thetas.push_back(algorithms.graphics.points[i].theta);
                                }
                                std::vector<int> xPoints;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    xPoints.push_back(algorithms.graphics.points[i].x);
                                }
                                std::vector<int> yPoints;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    yPoints.push_back(algorithms.graphics.points[i].y);
                                }
                                algorithms.sorts.quick.setData(algorithms.graphics.window, thetas, xPoints, yPoints);
                                sortedPoints5 sorted;
                                sorted = algorithms.sorts.quick.getSorted(true);
                                auto start_time = std::chrono::high_resolution_clock::now();
                                sorted = algorithms.sorts.quick.getSorted(false);
                                auto end_time = std::chrono::high_resolution_clock::now();
                                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
                                //-- Show Sorted Points
                                algorithms.graphics.window.copyTo(show);
                                for (int i = 0; i < sorted.x.size(); i++) {
                                    // std::cout << sorted.theta[i] << std::endl;
                                    cv::circle(
                                        show,
                                        cv::Point(
                                            sorted.x[i],
                                            sorted.y[i]
                                        ),
                                        2,
                                        cv::Scalar(0, 255, 0),
                                        1,
                                        cv::LINE_4
                                    );
                                    cv::putText(
                                        show,
                                        std::to_string(i + 1),
                                        cv::Point(
                                            sorted.x[i] - 11,
                                            sorted.y[i] + 25
                                        ),
                                        cv::FONT_HERSHEY_SIMPLEX,
                                        0.5,
                                        cv::Scalar(255, 255, 255)
                                    );
                                    cv::imshow(WINDOW_NAME, show);
                                    cv::waitKey(1);
                                }
                                std::cout << INFO "Time Elapsed: " << duration << " Nano Seconds" << std::endl;
                                cv::waitKey(0);
                                break;
                            }
                            case 6: {
                                //-- Sort Points by Theta
                                std::cout << LOG "Sorting Points by Theta ..." << std::endl;
                                std::vector<double> thetas;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    thetas.push_back(algorithms.graphics.points[i].theta);
                                }
                                std::vector<int> xPoints;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    xPoints.push_back(algorithms.graphics.points[i].x);
                                }
                                std::vector<int> yPoints;
                                for (int i = 0; i < algorithms.graphics.points.size(); i++) {
                                    yPoints.push_back(algorithms.graphics.points[i].y);
                                }
                                algorithms.sorts.heap.setData(algorithms.graphics.window, thetas, xPoints, yPoints);
                                sortedPoints6 sorted;
                                sorted = algorithms.sorts.heap.getSorted(true);
                                auto start_time = std::chrono::high_resolution_clock::now();
                                sorted = algorithms.sorts.heap.getSorted(false);
                                auto end_time = std::chrono::high_resolution_clock::now();
                                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
                                //-- Show Sorted Points
                                algorithms.graphics.window.copyTo(show);
                                for (int i = 0; i < sorted.x.size(); i++) {
                                    // std::cout << sorted.theta[i] << std::endl;
                                    cv::circle(
                                        show,
                                        cv::Point(
                                            sorted.x[i],
                                            sorted.y[i]
                                        ),
                                        2,
                                        cv::Scalar(0, 255, 0),
                                        1,
                                        cv::LINE_4
                                    );
                                    cv::putText(
                                        show,
                                        std::to_string(i + 1),
                                        cv::Point(
                                            sorted.x[i] - 11,
                                            sorted.y[i] + 25
                                        ),
                                        cv::FONT_HERSHEY_SIMPLEX,
                                        0.5,
                                        cv::Scalar(255, 255, 255)
                                    );
                                    cv::imshow(WINDOW_NAME, show);
                                    cv::waitKey(1);
                                }
                                std::cout << INFO "Time Elapsed: " << duration << " Nano Seconds" << std::endl;
                                cv::waitKey(0);
                                break;
                            }
                            case 7: {
                                
                            }
                            case 0: {
                                break;
                            }
                            default:
                                break;
                        }
                    }
                    break;
                }
                case 2: {
                    mainWindow.copyTo(algorithms.graphics.window);
                    algorithms.graphics.showBoxes();
                    while (true) {
                        std::cout << "\033[2J\x1b[H" << std::endl;
                        std::cout << YELLOW "Available Searchs :" RESET << std::endl;
                        std::cout << YELLOW "1." YELLOW2 " Binary Search" RESET << std::endl;
                        std::cout << YELLOW "0." YELLOW2 " Back" RESET << std::endl;
                        //-- Generating Colorful Chess Board
                        std::cout << GRAY "Please Select An Algorithm : " RESET; std::cin >> choice;
                        if (choice == 0) {
                            choice = -1;
                            cv::destroyWindow(INFO_WINDOW_NAME);
                            break;
                        }
                        std::cout << LOG "Generating Colorful Chess Board ..." << std::endl;
                        algorithms.graphics.window.copyTo(tmp);
                        for (int sizeCounter = 0; sizeCounter < 41; sizeCounter++) {
                            algorithms.graphics.boxes.resize(0);
                            algorithms.generateChessBoard(sizeCounter, true);
                            for (int i = 0; i < algorithms.graphics.boxes.size(); i++) {
                                cv::rectangle(
                                    algorithms.graphics.window,
                                    cv::Point(
                                        algorithms.graphics.boxes[i].topLeft.x,
                                        algorithms.graphics.boxes[i].topLeft.y
                                    ),
                                    cv::Point(
                                        algorithms.graphics.boxes[i].bottomRight.x,
                                        algorithms.graphics.boxes[i].bottomRight.y
                                    ),
                                    algorithms.graphics.boxes[i].color,
                                    cv::FILLED,
                                    cv::LINE_4
                                );
                                if (i % (sizeCounter) == 0) {
                                    cv::imshow(WINDOW_NAME, algorithms.graphics.window);
                                    cv::waitKey(1);
                                }
                            }
                        }
                        std::cout << TAB SUCCESS "Chess Board Generated Successfully!" << std::endl;
                        std::cout << LOG "Please Select Box ID to Search" << std::endl;
                        std::cout << TAB TAB GRAY "Then Press 'S' Key " RESET << std::endl;
                        cv::waitKey(0);
                        algorithms.graphics.mouseStatus = EVENTS_INACTIVE;
                        switch (choice) {
                            case 1: {
                                std::cout << LOG "Searching Box ID " << algorithms.graphics.selectedBoxID <<" ..." << std::endl;
                                std::vector<int> array;
                                array.resize(0);
                                for (int i = 0; i < algorithms.graphics.boxes.size(); i++) {
                                    array.push_back(i);
                                }
                                std::vector<box> boxes;
                                for (int i = 0; i < algorithms.graphics.boxes.size(); i++) {
                                    box tmpBox;
                                    tmpBox.topLeft.x = algorithms.graphics.boxes[i].topLeft.x;
                                    tmpBox.topLeft.y = algorithms.graphics.boxes[i].topLeft.y;
                                    tmpBox.bottomRight.x = algorithms.graphics.boxes[i].bottomRight.x;
                                    tmpBox.bottomRight.y = algorithms.graphics.boxes[i].bottomRight.y;
                                    boxes.push_back(tmpBox);
                                }
                                // algorithms.search.binary.boxes
                                algorithms.search.binary.setData(boxes, array, algorithms.graphics.window, algorithms.graphics.selectedBoxID);
                                int result;
                                result = algorithms.search.binary.getFound(true);
                                auto start_time = std::chrono::high_resolution_clock::now();
                                result = algorithms.search.binary.getFound(false);
                                auto end_time = std::chrono::high_resolution_clock::now();
                                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
                                //-- Show Result
                                cv::rectangle(
                                    algorithms.graphics.window,
                                    cv::Point(
                                        algorithms.graphics.boxes[result].topLeft.x,
                                        algorithms.graphics.boxes[result].topLeft.y
                                    ),
                                    cv::Point(
                                        algorithms.graphics.boxes[result].bottomRight.x,
                                        algorithms.graphics.boxes[result].bottomRight.y
                                    ),
                                    cv::Scalar(0, 120, 0),
                                    cv::FILLED,
                                    cv::LINE_4
                                );
                                cv::rectangle(
                                    algorithms.graphics.window,
                                    cv::Point(
                                        algorithms.graphics.boxes[result].topLeft.x,
                                        algorithms.graphics.boxes[result].topLeft.y
                                    ),
                                    cv::Point(
                                        algorithms.graphics.boxes[result].bottomRight.x,
                                        algorithms.graphics.boxes[result].bottomRight.y
                                    ),
                                    cv::Scalar(0, 255, 0),
                                    4,
                                    cv::LINE_4
                                );
                                cv::imshow(WINDOW_NAME, algorithms.graphics.window);
                                std::cout << INFO "Time Elapsed: " << duration << " Nano Seconds" << std::endl;
                                cv::waitKey(0);
                                algorithms.graphics.mouseStatus = EVENTS_ACTIVE;
                                break;
                            }
                            default:
                                break;
                        }
                    }
                    break;
                }
                case 3: {
                    mainWindow.copyTo(algorithms.graphics.window);
                    std::cout << "\033[2J\x1b[H" << std::endl;
                    std::cout << YELLOW "Moving on Grid Algorithm on Real Topological Map" << std::endl;
                    std::cout << LOG "Please Crop Specific Part of the Map" << std::endl;
                    algorithms.generateMapData(
                        100,
                        GRAPHICS_FOR_MAPS,
                        INPUT_FILE
                    );
                    algorithms.movingOnGrid.run(algorithms.graphics.window);
                    break;
                }
                case 0: {
                    break;
                }
                default:
                    std::cout << "Please Select A Valid Algorithm!" << std::endl;
                    break;
            }
        }
    }
# endif // ALGORITHMS_OMID_SOJOODI