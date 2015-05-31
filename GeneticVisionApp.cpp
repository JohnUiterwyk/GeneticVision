//
// Created by John Uiterwyk on 25/04/15.
//

#include "GeneticVisionApp.h"
#include <string>
#include <vector>
#include "model/simulation/RunResult.h"

#ifdef CV_HIGHGUI_ENABLED
#include "view/OpenCVWindow.h"
#endif //CV_HIGHGUI_ENABLED


namespace GeneticVision
{

    GeneticVisionApp::GeneticVisionApp(const string * jsonConfigFilePath)
    {



        this->appConfig.loadConfigFile(jsonConfigFilePath);
        this->gpSimulation = new GpSimulation(&this->appConfig);


#ifdef CV_HIGHGUI_ENABLED
        OpenCVWindow output("output",100,100);
#endif //CV_HIGHGUI_ENABLED

        RunResult runResult;
        do
        {
            runResult = this->gpSimulation->tick(this->appConfig.getGenerationsPerTick());
            cout << runResult.toString() << endl;

#ifdef CV_HIGHGUI_ENABLED
            output.showImages(runResult.bestResultImages);
#endif //CV_HIGHGUI_ENABLED

        }while(runResult.solutionFound == false && runResult.generationId < this->appConfig.getMaxGenerations());
    }

    GeneticVisionApp::~GeneticVisionApp() {

    }
}
