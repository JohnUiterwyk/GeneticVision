//
// Created by John Uiterwyk on 25/04/15.
//

#include "GeneticVisionApp.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "model/ImagePair.h"
#include "view/OpenCVWindow.h"


namespace GeneticVision
{

    GeneticVisionApp::GeneticVisionApp(const string& imageSetPath, int guiEnabled)
    {


//
//        this->guiEnabled = guiEnabled;
        this->guiEnabled = false;
        this->imageSetPath = imageSetPath;
        this->model.loadImages(imageSetPath);


        if(this->guiEnabled)
        {
            OpenCVWindow sourceWindow("Training",100,100);
            OpenCVWindow truthWindow("Truth",100,100);

            sourceWindow.setPosition(0,0);
            sourceWindow.showImages(this->model.trainingImages);
            truthWindow.setPosition(0,sourceWindow.height+20);
            truthWindow.showImages(this->model.groundTruthImages);

        }
        this->model.initSimulation();
        bool solutionFound = false;
        do
        {
            solutionFound = this->model.tickSmulation();
        }while(solutionFound == false);
        waitKey(0);
    }

    GeneticVisionApp::~GeneticVisionApp() {

    }
}
