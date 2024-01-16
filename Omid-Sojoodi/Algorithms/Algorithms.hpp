# ifndef ALGORITHMS_OMID_SOJOODI
    /**
     * @file Algorithms.hpp
     * @author Ramtin Kosari (ramtinkosari@gmail.com)
     * @brief Algorithms Header File
     * @date 2023-12-01
     */
    # define ALGORITHMS_OMID_SOJOODI
    //-- Include Graphics Module
    # ifndef ALGORITHMS_OMID_SOJOODI_GRAPHICS
        # include "Graphics/Graphics.hpp"
    # endif // ALGORITHMS_OMID_SOJOODI_GRAPHICS
    //-- Include Sorts Module
    # ifndef ALGORITHMS_OMID_SOJOODI_SORTS
        # include "Sorts/Sorts.hpp"
    # endif // ALGORITHMS_OMID_SOJOODI_SORTS
    //-- Include Search Module
    # ifndef ALGORITHMS_OMID_SOJOODI_SEARCH
        # include "Search/Search.hpp"
    # endif // ALGORITHMS_OMID_SOJOODI_SEARCH
    //-- Include Needed Libraries
    # include <iostream>
    # include <random>
    //-- Amount of Points
    # define AMOUNT_OF_POINTS 100
    //-- Define Log Messages
    # define LOG "\033[38;2;0;255;0m[LOG]\033[0m "
    # define INFO "\033[38;2;0;255;255m[INFO]\033[0m "
    # define ERROR "\033[38;2;255;0;0m[ERROR]\033[0m "
    # define SUCCESS "\033[38;2;0;255;0m[SUCCESS]\033[0m "
    # define WARNING "\033[38;2;255;255;0m[WARNING]\033[0m "
    # define RESET "\033[0m"
    # define TAB "   "
    //-- Class Definition
    class Algorithms {
        public:
            //-- Graphics
            Graphics graphics;
            //-- Constructor
            Algorithms();
            //-- Generate Random Data
            void generateRandomData(
                int size,
                int min,
                int max
            );
            //-- Generate Chess Board
            void generateChessBoard(
                int size,
                bool colorful
            );
            //-- Sorts
            Sorts sorts;
            //-- Search
            Search search;
    };
# endif // ALGORITHMS_OMID_SOJOODI