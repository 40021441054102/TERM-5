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
# endif // ALGORITHMS_OMID_SOJOODI