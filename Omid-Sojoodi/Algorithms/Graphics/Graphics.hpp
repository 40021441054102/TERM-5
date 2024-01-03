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
    //-- Points Class Definition
    class Point {
        private:
            int x;
            int y;
            double theta;
        public:
            //-- Constructor
            Point();
    };
    //-- Graphics Class Definition
    class Graphics {
        private:
            //-- Main Window
            cv::Mat window;
        public:
            //-- Constructor
            Graphics();
            //-- Start Animation
            void startAnimation();
    };
# endif // ALGORITHMS_OMID_SOJOODI_GRAPHICS