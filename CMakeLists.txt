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
model/ImagePair.cpp model/ImagePair.h
model/Model.cpp model/Model.h
view/OpenCVWindow.cpp view/OpenCVWindow.h
model/simulation/VisionFitness.cpp model/simulation/VisionFitness.h
model/simulation/functions/RandDouble.cpp model/simulation/functions/RandDouble.h
model/simulation/functions/ReturnDouble.cpp model/simulation/functions/ReturnDouble.h
model/simulation/functions/ReturnImage.cpp model/simulation/functions/ReturnImage.h
model/simulation/functions/ReturnKernel.cpp model/simulation/functions/ReturnKernel.h
model/simulation/functions/ReturnValue.cpp model/simulation/functions/ReturnValue.h
model/simulation/functions/Threshold.cpp model/simulation/functions/Threshold.h
model/simulation/functions/TFunction.h
model/simulation/functions/TTerminal.cpp model/simulation/functions/TTerminal.h
model/simulation/functions/ImageBrightness.cpp model/simulation/functions/ImageBrightness.h
model/simulation/GpSimulation.cpp model/simulation/GpSimulation.h)
target_link_libraries( GeneticVision ${OpenCV_LIBS} )
target_link_libraries(GeneticVision ${CMAKE_SOURCE_DIR}/rmitgp/librmitgp.a)