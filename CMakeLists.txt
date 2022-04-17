cmake_minimum_required(VERSION 3.21)
project(ArtChart)

set(CMAKE_CXX_STANDARD 11)

add_executable(ArtChart main.cpp DataStructure1_Tests.h ArtChart.cpp ArtChart.h ArtDisplay.cpp ArtDisplay.h QueryData.h radixSort.h sortByRelevance.h HeapSort.cpp HeapSort.h)
