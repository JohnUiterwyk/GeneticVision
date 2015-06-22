# GeneticVision
by John Uiterwyk

GeneticVision is a machine learning application that evolves programs that use functionality from OpenCV. 
The application is built with C++ using the following libraries:

- [RmitGP](http://goanna.cs.rmit.edu.au/~vc/rmitgp/), a genetic programming library developed at RMIT University .
- [OpenCV](http://opencv.org) an open source computer vision library
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp) a json library

## Using GeneticVision


### Config file
Here is an example config file:
```
    {
      "populationSize": 150,
      "maxGenerations":3000,
      "targetFitness":0.01,
      "generationsPerTick":1,
      "mutation":0.28,
      "crossover":0.70,
      "elitism":0.02,
      "minDepth": 2,
      "maxDepth":5,
      "logFrequency":100,
      "showResultImagesInHighGuiWindow": true,
      "saveResultImages": false,
      "loadPopulationEnabled":false,
      "loadPopulationPath":"output/populations/gen_000290.gen",
      "loadTrainingPairs":"true",
      "outputPath":"output/",
      "trainingSet":"images/",
      "testSet":[
          {"source": "images/easy-square0001.png", "target":"images/easy-square0001-mask.png"},
          {"source": "images/easy-square0002.png", "target":"images/easy-square0002-mask.png"},
          {"source": "images/easy-square0003.png", "target":"images/easy-square0003-mask.png"}
      ]
    }
```
## Compiling 
Compile this application using Cmake 2.8 or higher. This application requires that OpenCV has been installed properly. 
This application requires that OpenCV was installed correctly.
 
To compile the application with support for an output to a window, compile with the Cmake option "-D GUI=ON".  You will 
need to have installed OpenCV with HighGui support enabled.

## Developer Guide
