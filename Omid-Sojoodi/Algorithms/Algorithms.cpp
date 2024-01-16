# ifndef ALGORITHMS_OMID_SOJOODI
    # include "Algorithms.hpp"
    //-- Constructor
    Algorithms::Algorithms() {
        std::cout << LOG "Algorithms Module Loaded Successfully!" << std::endl;
        //-- Initialize Random Data
        generateRandomData(AMOUNT_OF_POINTS, WINDOW_WIDTH / 10, WINDOW_WIDTH - WINDOW_WIDTH / 10);
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
        bool colorful = false
    ) {
        std::random_device _random;
        std::default_random_engine eng(_random());
        std::uniform_int_distribution<int> _red(0, 100);
        std::uniform_int_distribution<int> _green(0, 255);
        std::uniform_int_distribution<int> _blue(100, 255);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                Box box;
                box.topLeft.x = i * WINDOW_WIDTH / size;
                box.topLeft.y = j * WINDOW_HEIGHT / size;
                box.bottomRight.x = (i + 1) * WINDOW_WIDTH / size;
                box.bottomRight.y = (j + 1) * WINDOW_HEIGHT / size;
                box.center.x = (box.topLeft.x + box.bottomRight.x) / 2;
                box.center.y = (box.topLeft.y + box.bottomRight.y) / 2;
                box.width = box.bottomRight.x - box.topLeft.x;
                box.height = box.bottomRight.y - box.topLeft.y;
                if (colorful) {
                    box.color = cv::Scalar(_blue(eng), _green(eng), 0);
                } else {
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
# endif // ALGORITHMS_OMID_SOJOODI