# GeneticVision v0.1
by John Uiterwyk

[GeneticVision](https://github.com/JohnUiterwyk/genetic-vision) is a C++ machine learning application that evolves computer vision programs.  

This application utilises the following libraries:
- [RmitGP](http://goanna.cs.rmit.edu.au/~vc/rmitgp/) - a genetic programming library developed at RMIT University .
- [OpenCV](http://opencv.org) - an open source computer vision library
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp) - a json library

## Supported Platforms
- Linux
- OS X

The application has been tested on OS X 10.10, CentOS 6.3, and Amazon Linux AMI 2015.03

## Prerequisites
- OpenCV 2.4.x  
- CMake 2.8+

## Downloading
You can download a [zip of the the latest version of GeneticVision from github](https://github.com/JohnUiterwyk/genetic-vision/archive/master.zip)
Alternatively you can [clone the repo from github](https://github.com/JohnUiterwyk/genetic-vision)

## Using GeneticVision
The simplest way to run GeneticVision (GV for short) is as follows:  
```
$ ./GeneticVision --images path/to/images
```
This will  evolve a population using the images provided and with default settings.   

### Additional examples :  
Load a population and continue evolving  
```
$ ./GeneticVision --population path/to/population.gen --images path/to/images
```  

Load a config file
```
$ ./GeneticVision --config path/to/config.json
```

Configure a run with command line options
```
$ ./GeneticVision --images path/to/images --populationSize 300 --generations 1000 --targetFitness 0.1
```
### Preparing Training Images
The Genetic Vision application works by taking a source image and trying to evolve an application that predicts a target 
image. Ideally you provide the application with a large set of source/target image pairs to train with. Genetic Vision 
expects a set of images to be contained withing a directory and using a specific naming convention. The basic rule is 
the target image should have the same name as the source file with `-mask` added to the filename. So for example, if you
have a source image `example.png`, the target image should be named `example-mask.png`. The application accepts the 
following file types:  
- .png
- .jpg
- .bmp
- .tif


### Output
When you run GeneticVision, it will create a folder in the current directory names `output/` . In this folder, the
application will create:

- `output/populations`  where it will write population files
- `output/images` directory where result image will be written. 
- `output/run.log` a log output of the evolution runs

You can change the output directory via the `outputPath` option.


## Compiling 

Compile this application using Cmake 2.8 or higher. 
GeneticVision requires that OpenCV has been installed correctly.
 
To compile the application with support for an output to a window, compile with the Cmake option "-D GUI=ON".  You will 
need to have installed OpenCV with HighGui support enabled.

#### Overview:
- [Install OpenCV](http://docs.opencv.org/doc/tutorials/introduction/linux_install/linux_install.html)
- Clone the project from the github repo
- Compile the project using CMake 2.8 or higher
- Prep a directory of images with proper naming conventions.
- Execute an evolution run using the compiled binary and the prepared images

#### Step by step
- Make the project directory `$ mkdir ~/genetic-vision/`
- Change to the project directory `$ cd ~/genetic-vision/`
- Clone the project from the github repo: `$ git clone https://github.com/JohnUiterwyk/genetic-vision.git .`
- Make a directory for the compiled executable `$ mkdir ~/genetic-vision/bin`
- Change to the build directory `$ cd ~/genetic-vision/bin`
- Compile the project with CMake, passing the path to the parent folder `$ cmake ..` . This is performing what is known
as an 'out of source build'. Just to keep things cleaner
- Change to the data working directory `$ cd ~/my-test-data/`
- create a folder for the images `$ mkdir training-images/` and add source/target pairs of images using the convention 
described in the "Preparing Training Images" section.
- Run GV with the images directory `$ ~/genetic-vision/bin/GeneticVision --evolve --images ./training-images`

## Developer Guide

The code has been thoroughly commented and a reference has been generated using Doxygen. You can view the doxygen output here: (TODO)

## Project Road Map

You can [view the project roadmap task board here](https://trello.com/b/BjXlMQlh/genetic-vision-roadmap)
            
## Options:
The only required option is the images option. Without images, nothing can be done. Options can be set via config file or via command line option. Command line options will override config file settings. Loading a population file will override both command line and config file settings.

### Run Mode
GV has three main modes: evolve, test, run.  
Default: `evolve`

##### Evolve
Evolve will evolve a population of programs.  
Command line usage: `--evolve`  
Config file usage: `"runMode":"evolve"`  

##### Test
**Development to be completed**
```
Test will load a population and output accuracy/error information of the best program. 
Command line usage: `--test`  
Config file usage: `"runMode":"test"`  
```

##### Run
**Development to be completed**
```
Run will execute a given program on a given set of images. 
Command line usage: `--run`  
Config file usage: `"runMode":"run"`  
```

### Images
Load a set of images for the purpose of training, testing, or running.  This option requires that images sets be 
prepared using a naming convention. Training is performed using pairs of images: a source image and a target image. The 
target image is what we want the evolved program to output given the source images. Target images should be have the 
same filename as the source images only with the string '-mask' inserted before the file extension. For example:
> easy-square0001.png  
> easy-square0001-mask.png  
> easy-square0002.png  
> easy-square0003-mask.png  
> ...  

Be sure to include the trailing slash.

Command line usage: `--images path/to/images/`  
Config file usage: `"images":"path/to/images/"` 
Option argument type: _string path to images directory_ 

### Max Generations
Maximum number of generations to evolve a population. The evolution is terminated when a program reaches the target 
fitness or when the maximum number of generations has been reached.

Command line usage: `--generations 3000`  
Config file usage: `"maxGenerations": 3000` 
Option argument type: _integer_ 
Default: 100

### Population Size
The number of programs in the population.

Command line usage: `--populationSize 100`  
Config file usage: `"populationSize": 100`  
Option argument type: _integer_ 
Default: 100

### Mutation Rate
The rate of mutation when producing a new generation from a population.

Command line usage: `--mutation 0.70`  
Config file usage: `"mutation": 0.70`  
Option argument type: _float between 0 and 1_  
Default: 0.70

### Crossover Rate
The rate of crossover when producing a new generation from a population.

Command line usage: `--crossover 0.28`  
Config file usage: `"crossover": 0.28`  
Option argument type: _float between 0 and 1_  
Default: 0.28

### Elitism Rate
The rate of elitism when producing a new generation from a population.

Command line usage: `--elitism 0.02`  
Config file usage: `"elitism": 0.02`  
Option argument type: _float between 0 and 1_  
Default: 0.02

### Min depth
The minimum depth of a program tree.

Command line usage: `--minDepth 2`  
Config file usage: `"minDepth": 2`  
Option argument type: _integer_  
Default: 0.02

### Elitism Rate
The maximum depth of a program tree. Increasing this can result in an exponential increase in run time for a generation.

Command line usage: `--maxDepth 5`  
Config file usage: `"maxDepth": 5`  
Option argument type: _integer_   
Default: 5

### Target Fitness
The target fitness for the evolution run. If the best program of a population is less than this number, then the evolution run is terminated. 

Command line usage: `--targetFitness 0.02`  
Config file usage: `"targetFitness": 0.02`  
Option argument type: _float between 0 and 1_  
Default: 0.02


### Save Result Images
If this option is enabled, every X generations, an image will be written to disk for each image pair in the training set. The frequency of image writing is determined by the logFrequency option.

Command line usage: `--saveResultImages`  
Config file usage: `"saveResultImages": true` 
Option argument type: _true | false_   
Default: false

### Load Population
Load a population from a *.gen file. The value for this option should be the path to the gen file. Loading a population file will overide most population specific settings.

Command line usage: `--population path/to/file.gen`  
Config file usage: `"population": "path/to/file.gen"` 
Option argument type: _string_  

### Log Frequency
This sets how frequently logging information is outputed. This option affects the frequency of the following:
- writing summary information for the current generation to stdout
- writing result images to disk for the current generation
- writing gen files to disk

Command line usage: `--logFrequency 10`  
Config file usage: `"logFrequency": 10` 
Option argument type: _integer_   
Default: 1

### Load Configuration File
Load settings from a JSON formatted configuration file. Please note that **all paths within a config file are relative to the config file** unless the rootPath option is set.

Command line usage: `--config path/to/config`  
Option argument type: _string_  

##### Example Config File:  
````
    {  
        "maxGenerations":3000,  
        "populationSize": 150,  
        "mutation":0.28,  
        "crossover":0.70,  
        "elitism":0.02,  
        "minDepth": 2,  
        "maxDepth":5,  m
        "targetFitness":0.01,  
        "logFrequency":100,  
        "guiEnabled":true,  
        "outputPath":"output/",  
        "saveResultImages": false,  
        "population":"output/populations/gen_000290.gen",  
        "images":"images/"  
    }
````

