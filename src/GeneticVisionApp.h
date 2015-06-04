//
// Created by John Uiterwyk on 25/04/15.
//

#ifndef GENETICVISION_GENETICVISIONAPP_H
#define GENETICVISION_GENETICVISIONAPP_H
#include <string>
#include "model/Model.h"
#include "view/ViewController.h"


using namespace std;
namespace GeneticVision
{
    class GeneticVisionApp
    {
        public:
            /*************
             Constructor.
            **************/
            GeneticVisionApp(const string * jsonConfigFilePath);

            /*********************
             virtual destructor
            *********************/
            virtual ~GeneticVisionApp();

        private:
        GpSimulation * gpSimulation;
        ViewController * view;
        AppConfig appConfig;

    };
}

#endif //GENETICVISION_GENETICVISIONAPP_H
