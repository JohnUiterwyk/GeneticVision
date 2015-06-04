//
// Created by John Uiterwyk on 6/4/15.
//

#include "ViewController.h"
namespace GeneticVision
{

    ViewController::ViewController(GeneticVision::AppConfig * appConfig):
            highGuiView(appConfig),
            stdOutView(appConfig)
    {


    }

    void ViewController::update(RunResult *runResult) {
        this->highGuiView.update(runResult);
        this->stdOutView.update(runResult);
    }
}