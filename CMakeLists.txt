cmake_minimum_required(VERSION 2.8)
project(GeneticVision)

find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

set (GeneticVision_VERSION_MAJOR 1)
set (GeneticVision_VERSION_MINOR 0)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
# build the librmitgp if needed
add_custom_target(
   librmitgp
   COMMAND make
   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/rmitgp
)

set(SOURCE_FILES
src/main.cpp
src/GeneticVisionApp.cpp
src/GeneticVisionApp.h
src/util/jsoncpp.cpp
src/util/json/json.h
src/util/json/json-forwards.h
src/model/ImagePair.cpp src/model/ImagePair.h
src/view/OpenCVWindow.cpp src/view/OpenCVWindow.h
src/model/simulation/VisionFitness.cpp src/model/simulation/VisionFitness.h
src/model/simulation/types/ReturnDouble.cpp src/model/simulation/types/ReturnDouble.h
src/model/simulation/GvSimulation.cpp src/model/simulation/GvSimulation.h
src/model/simulation/types/ReturnImage.cpp src/model/simulation/types/ReturnImage.h
src/model/simulation/functions/ImageThreshold.cpp src/model/simulation/functions/ImageThreshold.h
src/model/simulation/terminals/RandDouble.cpp src/model/simulation/terminals/RandDouble.h
src/model/simulation/terminals/ImageInput.cpp src/model/simulation/terminals/ImageInput.h
src/model/simulation/functions/PlusDouble.cpp src/model/simulation/functions/PlusDouble.h
src/model/simulation/VisionFitness.cpp src/model/simulation/VisionFitness.h
src/model/simulation/functions/ImageGaussianBlur.cpp src/model/simulation/functions/ImageGaussianBlur.h
src/model/simulation/functions/TFunction.h
src/model/simulation/functions/Mean.h src/model/simulation/functions/Mean.cpp
src/model/simulation/functions/StdDev.h src/model/simulation/functions/StdDev.cpp
src/model/simulation/functions/ImageBlend.cpp src/model/simulation/functions/ImageBlend.h
src/model/simulation/functions/ImageCannyEdge.cpp src/model/simulation/functions/ImageCannyEdge.h
src/model/simulation/functions/ImageInvert.cpp src/model/simulation/functions/ImageInvert.h
src/model/simulation/functions/ImageErode.cpp src/model/simulation/functions/ImageErode.h
src/model/simulation/functions/ImageSobel.cpp src/model/simulation/functions/ImageSobel.h
src/AppConfig.cpp src/AppConfig.h
src/view/StdOutView.cpp src/view/StdOutView.h
src/view/HighGuiView.cpp src/view/HighGuiView.h
src/model/simulation/RunResult.cpp src/model/simulation/RunResult.h
src/view/ViewController.cpp src/view/ViewController.h
src/model/simulation/GvPopulation.cpp src/model/simulation/GvPopulation.h
src/view/ImageWriter.cpp src/view/ImageWriter.h
src/model/simulation/ImagePairCollection.cpp src/model/simulation/ImagePairCollection.h
src/model/simulation/ProgramResult.cpp src/model/simulation/ProgramResult.h
src/model/simulation/ProgramStats.cpp src/model/simulation/ProgramStats.h
)
add_executable(GeneticVision ${SOURCE_FILES} )

# CV_HIGHGUI_ENABLED flag
# This enables a GUI output window on systems that can support opencv highgui
# note: disable on VPAC since it is not supported
OPTION(GUI "Enable guid window" OFF)
IF(GUI)
    add_definitions(-DCV_HIGHGUI_ENABLED)
ENDIF(GUI)

target_link_libraries(GeneticVision ${OpenCV_LIBS} )
target_link_libraries(GeneticVision ${CMAKE_SOURCE_DIR}/src/rmitgp/librmitgp.a)
add_dependencies(GeneticVision librmitgp)