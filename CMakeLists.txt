cmake_minimum_required(VERSION 3.1)
project(GeneticVision)

find_package( OpenCV )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")

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
model/simulation/types/ReturnDouble.cpp model/simulation/types/ReturnDouble.h
model/simulation/GpSimulation.cpp model/simulation/GpSimulation.h
model/simulation/types/ReturnImage.cpp model/simulation/types/ReturnImage.h
model/simulation/functions/ImageThreshold.cpp model/simulation/functions/ImageThreshold.h
model/simulation/terminals/RandDouble.cpp model/simulation/terminals/RandDouble.h
model/simulation/terminals/ImageInput.cpp model/simulation/terminals/ImageInput.h
model/simulation/functions/PlusDouble.cpp model/simulation/functions/PlusDouble.h
model/simulation/VisionFitness.cpp model/simulation/VisionFitness.h

model/simulation/functions/ImageGaussianBlur.cpp model/simulation/functions/ImageGaussianBlur.h model/simulation/functions/OpenCVFunction.cpp model/simulation/functions/OpenCVFunction.h)

target_link_libraries( GeneticVision ${OpenCV_LIBS} )
target_link_libraries(GeneticVision ${CMAKE_SOURCE_DIR}/rmitgp/librmitgp.a)