# ifndef ALGORITHMS_OMID_SOJOODI
    //-- Include Needed Libraries
    # include <iostream>
    //-- Include Algorithms Module
    # include "Algorithms/Algorithms.hpp"
    //-- Define Colors
    # define CYAN "\033[38;2;0;255;255m"
    # define CYAN2 "\033[38;2;0;170;170m"
    # define GRAY "\033[38;2;170;170;170m"
    # define YELLOW "\033[38;2;255;255;0m"
    # define YELLOW2 "\033[38;2;120;120;0m"
    # define ERROR "\033[38;2;255;0;0m[ERROR]\033[0m "
    # define RESET "\033[0m"
    //-- Main Function
    int main() {
        int choice = -1;
        Algorithms algorithms;
        while(true) {
            if (choice == 0) {
                cv::destroyAllWindows();
                break;
            }
            std::cout << "\033[2J\x1b[H" << std::endl;
            std::cout << CYAN "Available Algorithms:" RESET << std::endl;
            std::cout << CYAN "1." CYAN2 " Sorts" RESET << std::endl;
            std::cout << CYAN "2." CYAN2 " TSP" RESET << std::endl;
            std::cout << CYAN "0." CYAN2 " Exit" RESET << std::endl;
            std::cout << GRAY "Please Select An Algorithm : " RESET; std::cin >> choice;
            switch (choice) {
                case 1: {
                    while (true) {
                        if (choice == 0) {
                            choice = -1;
                            break;
                        }
                        std::cout << "\033[2J\x1b[H" << std::endl;
                        std::cout << YELLOW "Available Sorts:" RESET << std::endl;
                        std::cout << YELLOW "1." YELLOW2 " Bubble Sort" RESET << std::endl;
                        std::cout << YELLOW "2." YELLOW2 " Insertion Sort" RESET << std::endl;
                        std::cout << YELLOW "3." YELLOW2 " Selection Sort" RESET << std::endl;
                        std::cout << YELLOW "4." YELLOW2 " Merge Sort" RESET << std::endl;
                        std::cout << YELLOW "5." YELLOW2 " Quick Sort" RESET << std::endl;
                        std::cout << YELLOW "6." YELLOW2 " Heap Sort" RESET << std::endl;
                        std::cout << YELLOW "8." YELLOW2 " Radix Sort" RESET << std::endl;
                        std::cout << YELLOW "0." YELLOW2 " Back" RESET << std::endl;
                        std::cout << GRAY "Please Select An Algorithm : " RESET; std::cin >> choice;
                        switch(choice) {
                            case 1: {
                                algorithms.graphics.showPoints();
                                // algorithms.sorts.bubble.
                                break;
                            }
                            case 2: {
                                break;
                            }
                            case 3: {
                                break;
                            }
                            case 0: {
                                break;
                            }
                            default:
                                break;
                        }
                    }
                    break;
                }
                case 2: {

                    break;
                }
                case 0: {
                    break;
                }
                default:
                    std::cout << "Please Select A Valid Algorithm!" << std::endl;
                    break;
            }
        }
    }
# endif // ALGORITHMS_OMID_SOJOODI