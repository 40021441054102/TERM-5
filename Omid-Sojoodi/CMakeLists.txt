cmake_minimum_required(VERSION 3.12)

project(Algorithms)

# Add the main executable
add_executable(main main.cpp)

# Add source files in Sorts directory
add_library(Algorithms
    # - Main Modules
    Algorithms/Graphics/Graphics.hpp
    Algorithms/Graphics/Graphics.cpp
    Algorithms/Algorithms.hpp
    Algorithms/Algorithms.cpp
    # - Sort Algorithms
    Algorithms/Sorts/Sorts.hpp
    Algorithms/Sorts/Sorts.cpp
    Algorithms/Sorts/Bubble/Bubble.hpp
    Algorithms/Sorts/Bubble/Bubble.cpp
    Algorithms/Sorts/Insertion/Insertion.hpp
    Algorithms/Sorts/Insertion/Insertion.cpp
    Algorithms/Sorts/Selection/Selection.hpp
    Algorithms/Sorts/Selection/Selection.cpp
    Algorithms/Sorts/Merge/Merge.hpp
    Algorithms/Sorts/Merge/Merge.cpp
    Algorithms/Sorts/Quick/Quick.hpp
    Algorithms/Sorts/Quick/Quick.cpp
    Algorithms/Sorts/Heap/Heap.hpp
    Algorithms/Sorts/Heap/Heap.cpp
    # Algorithms/Sorts/Radix/Radix.hpp
    # Algorithms/Sorts/Radix/Radix.cpp
    # Algorithms/Sorts/Shell/Shell.hpp
    # Algorithms/Sorts/Shell/Shell.cpp
    # Algorithms/Sorts/Counting/Counting.hpp
    # Algorithms/Sorts/Counting/Counting.cpp
    # Algorithms/Sorts/Bucket/Bucket.hpp
    # Algorithms/Sorts/Bucket/Bucket.cpp
    # Algorithms/Sorts/Comb/Comb.hpp
    # Algorithms/Sorts/Comb/Comb.cpp
    # Algorithms/Sorts/Cycle/Cycle.hpp
    # Algorithms/Sorts/Cycle/Cycle.cpp
    # Algorithms/Sorts/Flash/Flash.hpp
    # Algorithms/Sorts/Flash/Flash.cpp
    # Algorithms/Sorts/Gnome/Gnome.hpp
    # Algorithms/Sorts/Gnome/Gnome.cpp
    # Algorithms/Sorts/Intro/Intro.hpp
    # Algorithms/Sorts/Intro/Intro.cpp
    # Algorithms/Sorts/OddEven/OddEven.hpp
    # Algorithms/Sorts/OddEven/OddEven.cpp
    # Algorithms/Sorts/Pancake/Pancake.hpp
    # Algorithms/Sorts/Pancake/Pancake.cpp
    # Algorithms/Sorts/Pigeonhole/Pigeonhole.hpp
    # Algorithms/Sorts/Pigeonhole/Pigeonhole.cpp
    # Algorithms/Sorts/SelectionRecursive/SelectionRecursive.hpp
    # Algorithms/Sorts/SelectionRecursive/SelectionRecursive.cpp
    # Algorithms/Sorts/Stooge/Stooge.hpp
    # Algorithms/Sorts/Stooge/Stooge.cpp
    # Algorithms/Sorts/Strand/Strand.hpp
    # Algorithms/Sorts/Strand/Strand.cpp
    # Algorithms/Sorts/Tree/Tree.hpp
    # Algorithms/Sorts/Tree/Tree.cpp
    # Algorithms/Sorts/Bitonic/Bitonic.hpp
    # Algorithms/Sorts/Bitonic/Bitonic.cpp
    # Algorithms/Sorts/Bozo/Bozo.hpp
    # Algorithms/Sorts/Bozo/Bozo.cpp
    # Algorithms/Sorts/Circle/Circle.hpp
    # Algorithms/Sorts/Circle/Circle.cpp
    # Algorithms/Sorts/Cocktail/Cocktail.hpp
    # Algorithms/Sorts/Cocktail/Cocktail.cpp
    # - Search Algorithms
    Algorithms/Search/Search.hpp
    Algorithms/Search/Search.cpp
    Algorithms/Search/Binary/BinarySearch.hpp
    Algorithms/Search/Binary/BinarySearch.cpp
    # - Moving on Grid Algorithm
    Algorithms/Moving-on-Grid/MovingOnGrid.hpp
    Algorithms/Moving-on-Grid/MovingOnGrid.cpp
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
