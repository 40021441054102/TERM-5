cmake_minimum_required(VERSION 3.12)

project(Algorithms)

# Add the main executable
add_executable(main main.cpp)

# Add source files in Sorts directory
add_library(Algorithms
    Algorithms/Graphics/Graphics.hpp
    Algorithms/Graphics/Graphics.cpp
    Algorithms/Algorithms.hpp
    Algorithms/Algorithms.cpp
    Algorithms/Sorts/Sorts.hpp
    Algorithms/Sorts/Sorts.cpp
    Algorithms/Sorts/Bubble/Bubble.hpp
    Algorithms/Sorts/Bubble/Bubble.cpp
    Algorithms/Sorts/Insertion/Insertion.hpp
    Algorithms/Sorts/Insertion/Insertion.cpp
)

# Link libraries to the main executable
target_link_libraries(main Algorithms)

# Optionally, you can set C++ standard
set_property(TARGET main PROPERTY CXX_STANDARD 11)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include OpenCV directories and link the library
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(main ${OpenCV_LIBS})

# Find X11 package
find_package(X11 REQUIRED)

# Include X11 directories and link the library
include_directories(${X11_INCLUDE_DIR})
target_link_libraries(main ${X11_LIBRARIES})
