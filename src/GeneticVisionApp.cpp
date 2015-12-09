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
        runResult = this->gvSimulation->getRunResult();
        runResult.testPerformance(this->appConfig.getTrainPairs().getVector());
        this->view->update(&runResult);
        
        if(this->appConfig.isEvolveEnabled())
        {
            do
            {
                runResult = this->gvSimulation->tick(this->appConfig.getLogFrequency());
                if (this->appConfig.isTestEnabled()) {
                    runResult.testPerformance(this->appConfig.getTrainPairs().getVector());
                }
                this->view->update(&runResult);

//                cout << "solutionFound:" << runResult.solutionFound << endl;
//                cout << "generationId:" << runResult.generationId  << endl;
//                cout << "getMaxGenerations:" << this->appConfig.getMaxGenerations() << endl;
//                cout << "isEvolveEnabled:" << this->appConfig.isEvolveEnabled() << endl;
//                cout << "isTestEnabled:" << this->appConfig.isTestEnabled() << endl;
            }while(runResult.solutionFound == false && runResult.generationId < this->appConfig.getMaxGenerations());
        }
        else if (this->appConfig.isTestEnabled())
        {
            runResult = this->gvSimulation->getRunResult();
            runResult.testPerformance(this->appConfig.getTrainPairs().getVector());
            this->view->update(&runResult);

            #ifdef CV_HIGHGUI_ENABLED
            cv::waitKey(0);
            #endif //CV_HIGHGUI_ENABLED
        }
    }

    GeneticVisionApp::~GeneticVisionApp() {

    }
}
