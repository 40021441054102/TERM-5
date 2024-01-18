# ifndef ALGORITHMS_OMID_SOJOODI_MOVING_ON_GRID
    # include "MovingOnGrid.hpp"
    //-- Constructor
    MovingOnGrid::MovingOnGrid() {
        std::cout << LOG << "Moving on Grid Algorithm has been Initialized." << std::endl;
        weightMatrix.resize(0);
    }
    //-- Set Data
    void MovingOnGrid::setData(int size) {
        for (int i = 0; i < size; i++) {
            std::vector<double> row;
            for (int j = 0; j < size; j++) {
                row.push_back(areas[i * size + j].weight);
            }
            weightMatrix.push_back(row);
            row.resize(0);
        }
    }
    //-- Run
    void MovingOnGrid::run(cv::Mat _window) {
        window = _window;
        std::vector<std::vector<double>> arr;
        for (int i = 1; i < weightMatrix.size(); i++) {
            for (int j = 1; j < weightMatrix[i].size(); j++) {
                arr[i][j] += std::min(weightMatrix[i - 1][j - 1], weightMatrix[i - 1][j]);
                arr[i][j] += std::min(weightMatrix[i - 1][j - 1], weightMatrix[i][j - 1]);
                arr[i][j] += weightMatrix[i][j];
                cv::rectangle(window, areas[i * weightMatrix.size() + j].topLeft, areas[i * weightMatrix.size() + j].bottomRight, cv::Scalar(0, 0, 255), cv::FILLED);
                cv::imshow(WINDOW_NAME, window);
                cv::waitKey(1);
                // cv::rectangle(window, areas[i * weightMatrix.size() + j].topLeft, areas[i * weightMatrix.size() + j].bottomRight, cv::Scalar(0, 0, 255), cv::FILLED);
                // cv::imshow(WINDOW_NAME, window);
                // cv::waitKey(0);
            }
        }
        std::cout << LOG << "The Minimum Weight is: " << weightMatrix[weightMatrix.size() - 1][weightMatrix[weightMatrix.size() - 1].size() - 1] << std::endl;
    }
# endif // ALGORITHMS_OMID_SOJOODI_MOVING_ON_GRID