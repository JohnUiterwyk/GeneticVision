//
// Created by John Uiterwyk on 4/05/15.
//

#include "GpSimulation.h"
#include "VisionFitness.h"

#include "types/ReturnImage.h"
#include "types/ReturnDouble.h"

#include "functions/ImageGaussianBlur.h"
#include "functions/ImageBlend.h"
#include "functions/ImageThreshold.h"
#include "functions/ImageCannyEdge.h"
#include "functions/ImageInvert.h"
#include "functions/ImageErode.h"
#include "functions/ImageSobel.h"
#include "functions/PlusDouble.h"
#include "functions/Mean.h"
#include "functions/StdDev.h"

#include "terminals/RandDouble.h"
#include "terminals/ImageInput.h"

#include "../../rmitgp/GPConfig.h"
#include "../../rmitgp/Population.h"
#include "../../rmitgp/ProgramGenerator.h"


GpSimulation::GpSimulation(GeneticVision::AppConfig * appConfig)
{
    this->runConfig = new GPConfig();
    //Do the default initialisation of the configuration
    this->runConfig->defaultInit();

    //Add the terminals we need
    this->runConfig->termSet.addNodeToSet(ReturnDouble::TYPENUM, RandDouble::generate);
    this->runConfig->termSet.addNodeToSet(ReturnImage::TYPENUM, ImageInput::generate);

    //Add the functions we need
    this->runConfig->funcSet.addNodeToSet(ReturnImage::TYPENUM, ImageThreshold::generate);
    this->runConfig->funcSet.addNodeToSet(ReturnImage::TYPENUM, ImageCannyEdge::generate);
    this->runConfig->funcSet.addNodeToSet(ReturnImage::TYPENUM, ImageGaussianBlur::generate);
    this->runConfig->funcSet.addNodeToSet(ReturnImage::TYPENUM, ImageBlend::generate);
    this->runConfig->funcSet.addNodeToSet(ReturnImage::TYPENUM, ImageInvert::generate);
    this->runConfig->funcSet.addNodeToSet(ReturnImage::TYPENUM, ImageErode::generate);
    this->runConfig->funcSet.addNodeToSet(ReturnImage::TYPENUM, ImageSobel::generate);
    this->runConfig->funcSet.addNodeToSet(ReturnDouble::TYPENUM, Mean::generate);
    this->runConfig->funcSet.addNodeToSet(ReturnDouble::TYPENUM, StdDev::generate);
    this->runConfig->funcSet.addNodeToSet(ReturnDouble::TYPENUM, PlusDouble::generate);


    //Set the depth limit for the system
    this->runConfig->maxDepth = appConfig->getMaxDepth();
    this->runConfig->minDepth = appConfig->getMinDepth();

    //Create the program generator
    this->runConfig->programGenerator = new ProgramGenerator(this->runConfig);



    this->pop = new Population(
            appConfig->getPopulationSize(),
            appConfig->getRunLogPath().c_str(),
            this->runConfig);


    //Set the rates of mutation etc
    this->pop->setMinDepth(appConfig->getMinDepth());
    this->pop->setDepthLimit(appConfig->getMaxDepth());
    this->pop->setMutationRate(appConfig->getMutation());
    this->pop->setCrossoverRate(appConfig->getCrossover());
    this->pop->setElitismRate(appConfig->getElitism());
    //Set the return type for our programs
    this->pop->setReturnType(ReturnImage::TYPENUM);



    //Set the fitness class to be used
    this->runConfig->fitnessObject = new VisionFitness(this->runConfig, appConfig->getImagePairs());

    //Initialise the fitness
    this->runConfig->fitnessObject->initFitness();

    //init the population
    this->pop->generateInitialPopulation();

    //pseudo disable built int logging
    this->pop->setLogFrequency(10000000);
    //this->pop->writeToFile();

//    //clean up
}

RunResult GpSimulation::tick(int generations)
{
    // run x generations
    bool solutionFound = this->pop->evolve(generations);
    GeneticProgram * best = this->pop->getBest();
    VisionFitness * fitness = dynamic_cast<VisionFitness*>(this->runConfig->fitnessObject);

    RunResult runResult;
    runResult.solutionFound = solutionFound;
    runResult.generationId = this->pop->getGenerationNumber();
    runResult.bestProgramId = best->getProgramID();
    runResult.bestProgramFitness = best->getFitness();
    runResult.bestResultImages = fitness->getResultImages(best);
    best->print(runResult.bestProgramString);

    return runResult;
}



void GpSimulation::cleanUp()
{
    this->runConfig->cleanUpObjects();
}

