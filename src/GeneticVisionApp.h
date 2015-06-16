//
// Created by John Uiterwyk on 25/04/15.
//

#ifndef GENETICVISION_GENETICVISIONAPP_H
#define GENETICVISION_GENETICVISIONAPP_H
#include <string>
#include "view/ViewController.h"
#include "model/simulation/GvSimulation.h"


using namespace std;
namespace GeneticVision
{
    class GeneticVisionApp
    {
        public:
            /*************
             Constructor.
            **************/
            GeneticVisionApp( int argc, char** argv );

            /*********************
             virtual destructor
            *********************/
            virtual ~GeneticVisionApp();

        private:
        GvSimulation *gvSimulation;
        ViewController * view;
        AppConfig appConfig;

    };
}

#endif //GENETICVISION_GENETICVISIONAPP_H
