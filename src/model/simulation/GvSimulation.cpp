//
// Created by John Uiterwyk on 4/05/15.
//

#include "GvSimulation.h"
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
#include "functions/ImageFilter2D.h"

namespace GeneticVision
{

    GvSimulation::GvSimulation(GeneticVision::AppConfig * appConfig)
    {
        this->appConfig = appConfig;
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
        this->runConfig->funcSet.addNodeToSet(ReturnImage::TYPENUM, ImageFilter2D::generate);
        this->runConfig->funcSet.addNodeToSet(ReturnDouble::TYPENUM, Mean::generate);
        this->runConfig->funcSet.addNodeToSet(ReturnDouble::TYPENUM, StdDev::generate);
        this->runConfig->funcSet.addNodeToSet(ReturnDouble::TYPENUM, PlusDouble::generate);



        //Set the fitness class to be used
        this->runConfig->fitnessObject = new VisionFitness(this->runConfig, appConfig->getTrainPairs(), appConfig->getTargetFitness(), appConfig->getNumOfThreads());

        //Initialise the fitness
        this->runConfig->fitnessObject->initFitness();


        this->pop = new GvPopulation(
                appConfig->getPopulationSize(),
                appConfig->getPopFilesPath(),
                appConfig->getRunLogPath().c_str(),
                this->runConfig);






        if(appConfig->isLoadPopulationEnabled())
        {
            try
            {
                //convert string to required non const char *
                std::string popPathString = appConfig->getLoadPopulationPath();
                char * popPathCharPtr = new char[popPathString.size() + 1];
                std::copy(popPathString.begin(), popPathString.end(), popPathCharPtr);
                popPathCharPtr[popPathString.size()] = '\0'; // don't forget the terminating 0


                //read the file into pop object
                this->pop->readFromFile(popPathCharPtr);

                //Set the depth limit for the system
                this->runConfig->maxDepth = this->pop->getDepthLimit();
                this->runConfig->minDepth = this->pop->getMinDepth();

                //Create the program generator
                this->runConfig->programGenerator = new ProgramGenerator(this->runConfig);

                // don't forget to free the string after finished using it
                delete[] popPathCharPtr;
            }
            catch(const string & err)
            {
                cerr << err << endl;
                cerr << "Exiting" << endl;
                exit(1);
            }
        } else
        {
            //Set the depth limit for the system
            this->runConfig->maxDepth = appConfig->getMaxDepth();
            this->runConfig->minDepth = appConfig->getMinDepth();

            //Create the program generator
            this->runConfig->programGenerator = new ProgramGenerator(this->runConfig);

            //Set the rates of mutation etc
            this->pop->setMinDepth(appConfig->getMinDepth());
            this->pop->setDepthLimit(appConfig->getMaxDepth());
            this->pop->setMutationRate(appConfig->getMutation());
            this->pop->setCrossoverRate(appConfig->getCrossover());
            this->pop->setElitismRate(appConfig->getElitism());

            //Set the return type for our programs
            this->pop->setReturnType(ReturnImage::TYPENUM);
            //init the population
            this->pop->generateInitialPopulation();
            //pseudo disable built int logging
        }

        if(appConfig->isEvolveEnabled())
        {
            this->pop->setLogFrequency(appConfig->getLogFrequency());
            this->pop->writeToFile();
        }
    //    //clean up
    }
    RunResult GvSimulation::tick(int generations)
    {
        // run x generations
        bool solutionFound = this->pop->evolve(generations);
        RunResult result = this->getRunResult();
        result.solutionFound = solutionFound;
        if(solutionFound)
        {
            this->pop->writeToFile();
        }
        return result;
    }

    RunResult GvSimulation::getRunResult()
    {
        VisionFitness * fitness = dynamic_cast<VisionFitness*>(this->runConfig->fitnessObject);

        RunResult runResult;
        runResult.bestProgram = this->pop->getBest();
        runResult.generationId = this->pop->getGenerationNumber();
        runResult.resultImagesMap = fitness->getResultImages(runResult.bestProgram);
        return runResult;
    }

    RunResult GvSimulation::testBest()
    {
        RunResult result = this->getRunResult();
        result.testPerformance(appConfig->getTrainPairs().getCollection());
        return result;
    }

    void GvSimulation::cleanUp()
    {
        this->runConfig->cleanUpObjects();
    }

}

