//
// Created by John Uiterwyk on 25/04/15.
//

#include "GeneticVisionApp.h"
#include <string>
#include "model/ImagePair.h"
#include "view/OpenCVWindow.h"



namespace GeneticVision
{

    GeneticVisionApp::GeneticVisionApp(const string * jsonConfigFilePath)
    {



        this->appConfig.loadConfigFile(jsonConfigFilePath);
        this->gpSimulation = new GpSimulation(&this->appConfig);
        
        bool solutionFound = false;
        do
        {
            solutionFound = this->gpSimulation->tick(1);
        }while(solutionFound == false);
        waitKey(0);
    }

    GeneticVisionApp::~GeneticVisionApp() {

    }
}
