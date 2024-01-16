# ifndef ALGORITHMS_OMID_SOJOODI_GRAPHICS
    # include "Graphics.hpp"
    cv::Scalar WINDOW_BACKGROUND(20, 10, 2);
    //-- Constructor
    Point::Point() {
        x = 0;
        y = 0;
        theta = 0;
    }
    //-- Constructor
    Box::Box() {
        topLeft.x = 0;
        topLeft.y = 0;
        bottomRight.x = 0;
        bottomRight.y = 0;
        center.x = 0;
        center.y = 0;
        width = 0;
        height = 0;
    }
    //-- Constructor
    Graphics::Graphics() {
        std::cout << LOG "Graphics Module Loaded Successfully!" << std::endl;
        selectedBoxID = -1;
        points.resize(0);
        window = cv::Mat(
            WINDOW_HEIGHT,
            WINDOW_WIDTH,
            CV_8UC3,
            WINDOW_BACKGROUND
        );
        infoWindow = cv::Mat(
            INFO_WINDOW_HEIGHT,
            INFO_WINDOW_WIDTH,
            CV_8UC3,
            WINDOW_BACKGROUND
        );
        int width, height;
        Display* disp = XOpenDisplay(NULL);
        Screen* scrn = DefaultScreenOfDisplay(disp);
        XCloseDisplay(disp);
        height = scrn->height;
        width = scrn->width;
        windowPositionCenter.x = width / 2;
        windowPositionCenter.y = height / 2;
        cv::imshow(WINDOW_NAME, window);
        cv::moveWindow(
            WINDOW_NAME,
            width / 2 - WINDOW_WIDTH / 2,
            height / 2 - WINDOW_HEIGHT / 2
        );
        // startAnimation();
        //-- Set Mouse Callback
        cv::setMouseCallback(WINDOW_NAME, onMouseCallback, this);
        //-- Set Mouse Event Active Status
        mouseStatus = EVENTS_ACTIVE;
    }
    //-- Start Animation
    void Graphics::startAnimation() {
        cv::Mat mainTMP;
        window.copyTo(mainTMP);
        int color = 0;
        int radius = WINDOW_HEIGHT;
        int maxcolor = 255;
        for (int j = 0; j < 180; j++) {
            for (int i = 0; i < radius / 2; i++) {
                color = i * maxcolor / WINDOW_HEIGHT;
                if (i % ((j + 1) * 2) == 0) {
                    cv::rectangle(
                        window,
                        cv::Point(
                            WINDOW_HEIGHT / 2 - i,
                            WINDOW_HEIGHT / 2 - i
                        ),
                        cv::Point(
                            WINDOW_HEIGHT / 2 + i,
                            WINDOW_HEIGHT / 2 + i
                        ),
                        cv::Scalar(
                            color, color - i, 0
                        ),
                        2,
                        cv::LINE_AA,
                        0
                    );
                    cv::imshow(WINDOW_NAME, window);
                    cv::waitKey(1);
                }
            }
            maxcolor /= 0.37;
        }
        for (int i = 0; i < radius / 15; i++) {
            cv::rectangle(
                window,
                cv::Point(
                    WINDOW_HEIGHT / 2 - i,
                    WINDOW_HEIGHT / 2 - i
                ),
                cv::Point(
                    WINDOW_HEIGHT / 2 + i,
                    WINDOW_HEIGHT / 2 + i
                ),
                cv::Scalar(
                    0, 0, 0
                ),
                2,
                cv::LINE_AA,
                0
            );
            cv::imshow(WINDOW_NAME, window);
            cv::waitKey(1);
        }
        std::string teacher = "Algorithm Design by Dr. Omid Sojoodi";
        cv::Size textSize = cv::getTextSize("Ramtin Kosari", cv::FONT_HERSHEY_COMPLEX, 2, 1, nullptr);
        cv::Point textPosition(WINDOW_HEIGHT / 2 - textSize.width / 2, WINDOW_HEIGHT / 2 + textSize.height / 2);
        cv::Size textSize2 = cv::getTextSize(teacher, cv::FONT_HERSHEY_COMPLEX, 1, 1, nullptr);
        cv::Point textPosition2(WINDOW_HEIGHT / 2 - textSize2.width / 2, WINDOW_HEIGHT / 2 + textSize2.height / 2 + 75);
        for (int i = 0; i < 255 * 3; i++) {
            // output.copyTo(tmp);
            cv::putText(window, "Ramtin Kosari", textPosition, cv::FONT_HERSHEY_COMPLEX, 2, cv::Scalar(i / 4 + 20, i / 4 + 20, i / 4));
            if (i < 255) {
                cv::putText(window, teacher, textPosition2, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(i, i, 0));
            } else if (i >= 255 * 2) {
                cv::putText(window, teacher, textPosition2, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255 - (i - 255 * 2), 255 - (i - 255 * 2), 0));
            } else {
                cv::putText(window, teacher, textPosition2, cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 255, 0));
            }
            cv::imshow(WINDOW_NAME, window);
            cv::waitKey(5);
        }
        cv::imshow(WINDOW_NAME, window);
        mainTMP.copyTo(window);
    }
    //-- Method to Show Generated Points
    void Graphics::showPoints() {
        window.copyTo(tmpMat);
        for (int i = 0; i < points.size(); i++) {
            cv::circle(
                window,
                cv::Point(
                    points[i].x,
                    points[i].y
                ),
                2,
                cv::Scalar(255, 255, 0),
                cv::FILLED,
                cv::LINE_4,
                0
            );
            cv::imshow(WINDOW_NAME, window);
            cv::waitKey(1);
        }
        cv::imshow(WINDOW_NAME, window);
    }
    //-- Method to Show Generated Boxes
    void Graphics::showBoxes() {
        window.copyTo(tmpMat);
        for (int i = 0; i < boxes.size(); i++) {
            cv::rectangle(
                window,
                boxes[i].topLeft,
                boxes[i].bottomRight,
                boxes[i].color,
                cv::FILLED,
                cv::LINE_4,
                0
            );
            cv::imshow(WINDOW_NAME, window);
            cv::waitKey(1);
        }
        cv::imshow(WINDOW_NAME, window);
    }
    //-- Mouse Callback
    void Graphics::onMouseCallback(int event, int x, int y, int flags, void* userdata) {
        static_cast<Graphics*>(userdata)->onMouse(event, x, y, flags);
    }
    //-- Mouse Events
    void Graphics::onMouse(int event, int x, int y, int flags) {
        if (event == cv::EVENT_LBUTTONDOWN) {
            selectedBoxID = selected;
            std::cout << INFO "Box " << selectedBoxID << " is selected." << std::endl;
            infoWindow = cv::Mat(
                INFO_WINDOW_HEIGHT,
                INFO_WINDOW_WIDTH,
                CV_8UC3,
                boxes[selectedBoxID].color
            );
            //-- Show Box ID in Middle
            cv::Size textSize = cv::getTextSize("Box " + std::to_string(selectedBoxID), cv::FONT_HERSHEY_COMPLEX, 1, 2, nullptr);
            cv::putText(
                infoWindow,
                "Box " + std::to_string(selectedBoxID),
                cv::Point(
                    INFO_WINDOW_WIDTH / 2 - textSize.width / 2,
                    INFO_WINDOW_HEIGHT / 2 + textSize.height / 2
                ),
                cv::FONT_HERSHEY_COMPLEX,
                0.9,
                cv::Scalar(255, 255, 255),
                2
            );
            //-- Show Box Color in Bottom
            cv::rectangle(
                infoWindow,
                cv::Point(
                    0,
                    INFO_WINDOW_HEIGHT - 35
                ),
                cv::Point(
                    INFO_WINDOW_WIDTH,
                    INFO_WINDOW_HEIGHT
                ),
                cv::Scalar(0, 0, 0),
                cv::FILLED,
                cv::LINE_AA,
                0
            );
            cv::putText(
                infoWindow,
                "Color: " + std::to_string(int(boxes[selectedBoxID].color[0])) + ", " + std::to_string(int(boxes[selectedBoxID].color[1])) + ", " + std::to_string(int(boxes[selectedBoxID].color[2])),
                cv::Point(
                    10,
                    INFO_WINDOW_HEIGHT - 10
                ),
                cv::FONT_HERSHEY_COMPLEX,
                0.7,
                cv::Scalar(255, 255, 255),
                2
            );
            cv::imshow(INFO_WINDOW_NAME, infoWindow);
            //-- Move Info Window to Center Left of Main Window
            cv::moveWindow(
                INFO_WINDOW_NAME,
                windowPositionCenter.x - WINDOW_WIDTH / 2 - INFO_WINDOW_WIDTH - 10,
                windowPositionCenter.y - INFO_WINDOW_WIDTH / 2
            );
        } else if (event == cv::EVENT_RBUTTONDOWN) {
            cv::destroyWindow(INFO_WINDOW_NAME);
        } else if (event == cv::EVENT_MOUSEMOVE) {
            //-- Search for Which Box is Selected
            cv::Mat tmp;
            window.copyTo(tmp);
            for (int i = 0; i < boxes.size(); i++) {
                if (x >= boxes[i].topLeft.x && x <= boxes[i].bottomRight.x && y >= boxes[i].topLeft.y && y <= boxes[i].bottomRight.y) {
                    cv::rectangle(
                        tmp,
                        boxes[i].topLeft,
                        boxes[i].bottomRight,
                        cv::Scalar(0, 100, 240),
                        3,
                        cv::LINE_AA,
                        0
                    );
                    cv::Size textSize = cv::getTextSize("Box " + std::to_string(i), cv::FONT_HERSHEY_COMPLEX, 1, 2, nullptr);
                    //-- Initialize text position to center of right of the box
                    cv::Point textPosition;
                    if (x > WINDOW_WIDTH / 2) {
                        textPosition = cv::Point(
                            boxes[i].center.x - boxes[i].width / 2 - textSize.width,
                            boxes[i].center.y + textSize.height / 2
                        );
                    } else {
                        textPosition = cv::Point(
                            boxes[i].center.x + boxes[i].width / 2,
                            boxes[i].center.y + textSize.height / 2
                        );
                    }
                    cv::rectangle(
                        tmp,
                        cv::Point(
                            textPosition.x,
                            boxes[i].topLeft.y
                        ),
                        cv::Point(
                            textPosition.x + textSize.width,
                            boxes[i].bottomRight.y
                        ),
                        cv::Scalar(0, 100, 240),
                        cv::FILLED,
                        cv::LINE_AA,
                        0
                    );
                    cv::rectangle(
                        tmp,
                        cv::Point(
                            textPosition.x,
                            boxes[i].topLeft.y
                        ),
                        cv::Point(
                            textPosition.x + textSize.width,
                            boxes[i].bottomRight.y
                        ),
                        cv::Scalar(0, 100, 240),
                        3,
                        cv::LINE_AA,
                        0
                    );
                    cv::putText(
                        tmp,
                        "Box " + std::to_string(i),
                        cv::Point(
                            textPosition.x + 10,
                            textPosition.y
                        ),
                        cv::FONT_HERSHEY_COMPLEX,
                        0.9,
                        cv::Scalar(255, 255, 255),
                        2
                    );
                    if (mouseStatus == EVENTS_ACTIVE) {
                        cv::imshow(WINDOW_NAME, tmp);
                        selected = i;
                    }
                    break;
                }
            }
            // std::cout << INFO "Mouse move over the window - position (" << x << ", " << y << ")" << std::endl;
        }
    }
# endif // ALGORITHMS_OMID_SOJOODI_GRAPHICS