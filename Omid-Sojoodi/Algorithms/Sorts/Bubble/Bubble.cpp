# ifndef ALGORITHMS_BUBBLE_SORT
    # include "Bubble.hpp"
    //-- Constructor
    Bubble::Bubble() {
        std::cout << LOG "Bubble Sort Algorithm Loaded Successfully!" << std::endl;
    }
    //-- Set Data
    void Bubble::setData(std::vector<double> _data) {
        data = _data;
    }
    //-- Sort
    std::vector<double> Bubble::getSorted() {
        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data.size() - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
        return data;
    }
# endif // ALGORITHMS_BUBBLE_SORT