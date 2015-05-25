//
// Created by John Uiterwyk on 4/05/15.
//

#include "GpSimulation.h"
#include "../../rmitgp/GPConfig.h"
#include "../../rmitgp/Population.h"
#include "../../rmitgp/ProgramGenerator.h"
#include "types/ReturnImage.h"
#include "types/ReturnDouble.h"
#include "terminals/RandDouble.h"
#include "functions/ImageThreshold.h"
#include "functions/PlusDouble.h"
#include "terminals/ImageInput.h"
#include "VisionFitness.h"
#include "functions/ImageGaussianBlur.h"

GpSimulation::GpSimulation()
{
    this->runConfig = new GPConfig();
    this->pop = new Population(1000,"output/run-log.txt",this->runConfig);
}

void GpSimulation::init(vector<ImagePair> * imagePairs)
{
    this->imagePairs = imagePairs;

    //Do the default initialisation of the configuration
    this->runConfig->defaultInit();

    //Add the terminals we need
    this->runConfig->termSet.addNodeToSet(ReturnDouble::TYPENUM, RandDouble::generate);
    this->runConfig->termSet.addNodeToSet(ReturnImage::TYPENUM, ImageInput::generate);

    //Add the functions we need
    this->runConfig->funcSet.addNodeToSet(ReturnImage::TYPENUM, ImageThreshold::generate);
    this->runConfig->funcSet.addNodeToSet(ReturnImage::TYPENUM, ImageGaussianBlur::generate);
    this->runConfig->funcSet.addNodeToSet(ReturnDouble::TYPENUM, PlusDouble::generate);

    //Set the depth limit for the system
    this->runConfig->maxDepth = 4;
    this->runConfig->minDepth = 2;


    //Create the program generator
    this->runConfig->programGenerator = new ProgramGenerator(this->runConfig);

    //Set the fitness class to be used
    this->runConfig->fitnessObject = new VisionFitness(this->runConfig, this->imagePairs);

    //Initialise the fitness
    this->runConfig->fitnessObject->initFitness();

    //Set the rates of mutation etc
    this->pop->setMutationRate(0.28);
    this->pop->setCrossoverRate(0.70);
    this->pop->setElitismRate(0.02);

    //Set the return type for our programs
    this->pop->setReturnType(ReturnImage::TYPENUM);

    //Set the depth limit for the population
    this->pop->setMinDepth(this->runConfig->minDepth);
    this->pop->setDepthLimit(this->runConfig->maxDepth);

    //Write out the population every N generations
    this->pop->setLogFrequency(10);




    //init the population
    this->pop->generateInitialPopulation();
    this->pop->writeToFile();


    this->pop->setLogFrequency(100);

//    //clean up
//    this->runConfig->cleanUpObjects();
}

bool GpSimulation::tick(int generations)
{
    // run x generations
    bool foundSolution = this->pop->evolve(generations);

    string str1;
    this->pop->getBest()->print(str1);
    VisionFitness * fitness = dynamic_cast<VisionFitness*>(this->runConfig->fitnessObject);
    fitness->outputProgram(this->pop->getBest());
    cout << "Fitness " << this->pop->getBest()->getFitness() << " " << str1 << endl;
    return foundSolution;
}
