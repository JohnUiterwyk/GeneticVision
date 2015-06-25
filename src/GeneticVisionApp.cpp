//
// Created by John Uiterwyk on 25/04/15.
//

#include "GeneticVisionApp.h"
#include <string>
#include <vector>
#include "model/simulation/RunResult.h"



namespace GeneticVision
{

    GeneticVisionApp::GeneticVisionApp( int argc, char** argv )
    {

        this->appConfig.parseCommandLineArgs(argc,argv);
        //check for images, otherwise quit nicely
        if(this->appConfig.getTrainPairs().size() == 0)
        {
            cerr << "No images loaded. Need to load images to proceed." << endl;
            exit(1);
        }

        this->gvSimulation = new GvSimulation(&this->appConfig);
        this->view = new ViewController(&this->appConfig);


        RunResult runResult;
        do
        {
            runResult = this->gvSimulation->tick(this->appConfig.getLogFrequency());
            this->view->update(&runResult);


        }while(runResult.solutionFound == false && runResult.generationId < this->appConfig.getMaxGenerations());
    }

    GeneticVisionApp::~GeneticVisionApp() {

    }
}
