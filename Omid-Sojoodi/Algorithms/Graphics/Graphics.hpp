# ifndef ALGORITHMS_OMID_SOJOODI_GRAPHICS
    /**
     * @file Graphics.hpp
     * @author Ramtin Kosari (ramtinkosari@gmail.com)
     * @brief Graphics Header File
     * @version 0.1
     * @date 2024-01-03
     */
    # define ALGORITHMS_OMID_SOJOODI_GRAPHICS
    //-- Include Needed Libraries
    # include <opencv4/opencv2/highgui.hpp>
    # include <opencv4/opencv2/imgproc.hpp>
    # include <X11/Xlib.h>
    //-- Define Configurations
    # define WINDOW_WIDTH 1200
    # define WINDOW_HEIGHT 1200
    # define WINDOW_NAME "Graphical View"
    extern cv::Scalar WINDOW_BACKGROUND;
    //-- Include Needed Libraries
    # include <iostream>
    //-- Define Log Messages
    # define LOG "\033[38;2;0;255;0m[LOG]\033[0m "
    # define INFO "\033[38;2;0;255;255m[INFO]\033[0m "
    # define ERROR "\033[38;2;255;0;0m[ERROR]\033[0m "
    # define SUCCESS "\033[38;2;0;255;0m[SUCCESS]\033[0m "
    # define WARNING "\033[38;2;255;255;0m[WARNING]\033[0m "
    # define RESET "\033[0m"
    //-- Points Class Definition
    class Point {
        public:
            int x;
            int y;
            double theta;
            //-- Constructor
            Point();
    };
    //-- Graphics Class Definition
    class Graphics {
        private:
            //-- Main Window
            cv::Mat window, tmpMat;
        public:
            //-- Points
            std::vector<Point> points;
            //-- Constructor
            Graphics();
            //-- Start Animation
            void startAnimation();
            //-- Method to Show Generated Points
            void showPoints();
    };
# endif // ALGORITHMS_OMID_SOJOODI_GRAPHICS