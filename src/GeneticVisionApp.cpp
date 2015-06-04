//
// Created by John Uiterwyk on 25/04/15.
//

#include "GeneticVisionApp.h"
#include <string>
#include <vector>
#include "model/simulation/RunResult.h"



namespace GeneticVision
{

    GeneticVisionApp::GeneticVisionApp(const string * jsonConfigFilePath)
    {



        this->appConfig.loadConfigFile(jsonConfigFilePath);
        this->gpSimulation = new GpSimulation(&this->appConfig);
        this->view = new ViewController(&this->appConfig);


        RunResult runResult;
        do
        {
            runResult = this->gpSimulation->tick(this->appConfig.getGenerationsPerTick());
            this->view->update(&runResult);


        }while(runResult.solutionFound == false && runResult.generationId < this->appConfig.getMaxGenerations());
    }

    GeneticVisionApp::~GeneticVisionApp() {

    }
}
