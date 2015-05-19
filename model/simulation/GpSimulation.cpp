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

GpSimulation::GpSimulation() {

}

void GpSimulation::init() {
    GPConfig runConfig;

    Population pop(100, "run-log.txt", &runConfig);

    //Set the rates of mutation etc
    pop.setMutationRate(0.26);
    pop.setCrossoverRate(0.70);
    pop.setElitismRate(0.04);

    //Set the return type for our programs
    pop.setReturnType(ReturnImage::TYPENUM);

    //Set the depth limit for the system
    runConfig.maxDepth = 4;
    runConfig.minDepth = 2;

    //Set the depth limit for the population
    pop.setMinDepth(runConfig.minDepth);
    pop.setDepthLimit(runConfig.maxDepth);

    //Write out the population every N generations
    pop.setLogFrequency(10);


    //Do the default initialisation of the configuration
    runConfig.defaultInit();

    //Add the terminals we need
    runConfig.termSet.addNodeToSet(ReturnDouble::TYPENUM, RandDouble::generate);
    runConfig.termSet.addNodeToSet(ReturnImage::TYPENUM, ImageInput::generate);

    //Add the functions we need
    runConfig.funcSet.addNodeToSet(ReturnImage::TYPENUM, ImageThreshold::generate);
    runConfig.funcSet.addNodeToSet(ReturnImage::TYPENUM, ImageGaussianBlur::generate);
    runConfig.funcSet.addNodeToSet(ReturnDouble::TYPENUM, PlusDouble::generate);

    //Create the program generator
    runConfig.programGenerator = new ProgramGenerator(&runConfig);

    //Set the fitness class to be used
    runConfig.fitnessObject = new VisionFitness(&runConfig);

    //Initialise the fitness
    runConfig.fitnessObject->initFitness();

    //init the population
    pop.generateInitialPopulation();
    pop.writeToFile();


    pop.setLogFrequency(100);

    try
    {
        string str1;
        cout << "evolve" << endl;

        if (pop.evolve(1000))
        {
            cout << "Found solution" << endl;
        }
        else
        {
            cout << "Didn't find solution" << endl;
        }

        pop.getBest()->print(str1);
        VisionFitness * fitness = dynamic_cast<VisionFitness*>(runConfig.fitnessObject);
        fitness->outputProgram(pop.getBest());
        cout << "Best program" << endl
        << "Fitness " << pop.getBest()->getFitness() << endl
        << str1 << endl;
    }
    catch (const string & s)
    {
        cerr << s <<endl;
        cerr << "Exiting" << endl;
        exit(1);
    }

    waitKey(0);
//    //clean up
//    runConfig.cleanUpObjects();
}
void GpSimulation::tick()
{

}
