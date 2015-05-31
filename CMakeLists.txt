cmake_minimum_required(VERSION 3.1)
project(GeneticVision)

find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES main.cpp)
add_executable(
GeneticVision
${SOURCE_FILES}
GeneticVisionApp.cpp
GeneticVisionApp.h
util/jsoncpp.cpp
util/json/json.h
util/json/json-forwards.h
model/ImagePair.cpp model/ImagePair.h
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
model/simulation/functions/ImageGaussianBlur.cpp model/simulation/functions/ImageGaussianBlur.h
model/simulation/functions/OpenCVFunction.cpp model/simulation/functions/OpenCVFunction.h
model/simulation/functions/TFunction.h
model/simulation/functions/Mean.h model/simulation/functions/Mean.cpp
model/simulation/functions/StdDev.h model/simulation/functions/StdDev.cpp
model/simulation/functions/ImageBlend.cpp model/simulation/functions/ImageBlend.h model/simulation/functions/ImageCannyEdge.cpp model/simulation/functions/ImageCannyEdge.h model/simulation/functions/ImageInvert.cpp model/simulation/functions/ImageInvert.h model/simulation/functions/ImageErode.cpp model/simulation/functions/ImageErode.h model/simulation/functions/ImageSobel.cpp model/simulation/functions/ImageSobel.h AppConfig.cpp AppConfig.h view/StdOutView.cpp view/StdOutView.h view/ViewController.cpp view/ViewController.h model/simulation/RunResult.cpp model/simulation/RunResult.h)

add_definitions(-DCV_HIGHGUI_ENABLED)

target_link_libraries(GeneticVision ${OpenCV_LIBS} )
target_link_libraries(GeneticVision ${CMAKE_SOURCE_DIR}/rmitgp/librmitgp.a)