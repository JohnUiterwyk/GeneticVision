# GeneticVision
by John Uiterwyk

GeneticVision is a machine learning application that evolves programs that use functionality from OpenCV. 
The application is built with C++ using the following libraries:

- [RmitGP](http://goanna.cs.rmit.edu.au/~vc/rmitgp/), a genetic programming library developed at RMIT University .
- [OpenCV](http://opencv.org) an open source computer vision library
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp) a json library

## Using GeneticVision
The simplest way to run Genetic Vision (GV for short) is as follows:  
    `$ ./GeneticVision --evolve --images path/to/images`  
This will use the evolve a population using the images provided and with default settings.   


            
### Options:

#### Run Mode
GV has three main modes: evolve, test, run.  
Default: `evolve`

##### Evolve
Evolve will evolve a population of programs.  
Command line usage: `--evolve`  
Config file usage: `"runMode":"evolve"`  

##### Test 
Test will load a population and output accuracy/error information of the best program. 
Command line usage: `--test`  
Config file usage: `"runMode":"test"`  

##### Run
Run will execute a given program on a given set of images. 
Command line usage: `--run`  
Config file usage: `"runMode":"run"`  


Command line: 

### Default settings:
If you do set an setting via the config file, the command line option, or by loading a population file, the following 
are the default settings set in the applicaiton:

maxGenerations(100),
generationsPerTick(1),
populationSize(100),
mutation(0.70),
crossover(0.02),
elitism(0.28),
targetFitness(0.03),
minDepth(2),
maxDepth(5),
saveResultImages(false),
loadPopulationEnabled(false),
rootPath("./"),
outputPath("output/"),
popFilesPath( "output/populations/"),
runLogPath("output/output.log"),
runMode(AppConfig::EVOLVE),
logFrequency(1)
            

### Config file
Here is an example config file:  
````
    {  
        "maxGenerations":3000,  
        "generationsPerTick":1,  
        "populationSize": 150,  
        "mutation":0.28,  
        "crossover":0.70,  
        "elitism":0.02,  
        "minDepth": 2,  
        "maxDepth":5,  
        "targetFitness":0.01,  
        "logFrequency":100,  
        "guiEnabled":true,  
        "outputPath":"output/",  
        "saveResultImages": false,  
        "population":"output/populations/gen_000290.gen",  
        "images":"images/"  
    }
````
## Compiling 
Compile this application using Cmake 2.8 or higher. This application requires that OpenCV has been installed properly. 
This application requires that OpenCV was installed correctly.
 
To compile the application with support for an output to a window, compile with the Cmake option "-D GUI=ON".  You will 
need to have installed OpenCV with HighGui support enabled.

## Developer Guide
