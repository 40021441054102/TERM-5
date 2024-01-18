# ifndef ALGORITHMS_OMID_SOJOODI_MOVING_ON_GRID
    /**
     * @file MovingOnGrid.hpp
     * @author Ramtin Kosari
     * @brief Moving on Grid Algorithm
     * @version 0.1
     * @date 2024-01-17
     */
    # define ALGORITHMS_OMID_SOJOODI_MOVING_ON_GRID
    //-- Define Configurations
    # define WINDOW_NAME "Graphical View"
    //-- Map Image
    # define MAP_IMAGE "../Algorithms/Moving-on-Grid/Data/map.jpg"
    //-- Topology Image
    # define TOPOLOGY_IMAGE "../Algorithms/Moving-on-Grid/Data/map_topological.jpg"
    //-- Map Data
    # define MAP_DATA "../Algorithms/Moving-on-Grid/Data/main.txt"
    //-- Include Needed Libraries
    # include <opencv4/opencv2/highgui.hpp>
    # include <opencv4/opencv2/imgproc.hpp>
    # include <iostream>
    # include <vector>
    //-- Define Colors Vectors
    extern std::vector<cv::Scalar> height_colors;
    extern std::vector<double> heights;
    //-- Define Log Messages
    # define LOG "\033[38;2;0;255;0m[LOG]\033[0m "
    //-- Area Structure
    struct area {
        cv::Point bottomRight;
        cv::Point topLeft;
        double weight;
    };
    //-- Class Definition
    class MovingOnGrid {
        private:
            //-- Window
            cv::Mat window;
        public:
            //-- Weight Matrix
            std::vector<std::vector<double>> weightMatrix;
            //-- Boxes
            std::vector<area> areas;
            //-- Constructor
            MovingOnGrid();
            //-- Set Data
            void setData(int size);
            //-- Run
            void run(cv::Mat _window);
    };
# endif // ALGORITHMS_OMID_SOJOODI_MOVING_ON_GRID