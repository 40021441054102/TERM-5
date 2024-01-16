# ifndef ALGORITHMS_OMID_SOJOODI_GRAPHICS
    # include "Graphics.hpp"
    # include <iostream>
    cv::Scalar WINDOW_BACKGROUND(20, 10, 2);
    //-- Constructor
    Point::Point() {
        x = 0;
        y = 0;
        theta = 0;
    }
    //-- Constructor
    Graphics::Graphics() {
        std::cout << LOG "Graphics Module Loaded Successfully!" << std::endl;
        points.resize(0);
        window = cv::Mat(
            WINDOW_HEIGHT,
            WINDOW_WIDTH,
            CV_8UC3,
            WINDOW_BACKGROUND
        );
        int width, height;
        Display* disp = XOpenDisplay(NULL);
        Screen* scrn = DefaultScreenOfDisplay(disp);
        XCloseDisplay(disp);
        height = scrn->height;
        width = scrn->width;
        cv::imshow(WINDOW_NAME, window);
        cv::moveWindow(
            WINDOW_NAME,
            width / 2 - WINDOW_WIDTH / 2,
            height / 2 - WINDOW_HEIGHT / 2
        );
        // startAnimation();
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
            // cv::imshow(WINDOW_NAME, window);
            // cv::waitKey(1);
        }
        cv::imshow(WINDOW_NAME, window);
    }
# endif // ALGORITHMS_OMID_SOJOODI_GRAPHICS