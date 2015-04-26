cmake_minimum_required(VERSION 3.1)
project(GeneticVision)

find_package( OpenCV )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(
GeneticVision
${SOURCE_FILES}
GeneticVisionApp.cpp
GeneticVisionApp.h
util/csv/CSVParser.cpp
util/csv/CSVParser.h
model/ImagePair.cpp model/ImagePair.h)
target_link_libraries( GeneticVision ${OpenCV_LIBS} )