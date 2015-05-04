//
// Created by John Uiterwyk on 25/04/15.
//

#ifndef GENETICVISION_GENETICVISIONAPP_H
#define GENETICVISION_GENETICVISIONAPP_H
#include <string>
#include "model/Model.h"


using namespace std;
namespace GeneticVision
{
    class GeneticVisionApp
    {
        public:
            /*************
             Constructor.
            **************/
            GeneticVisionApp(const string& imageSetPath, int guiEnabled);

            /*********************
             virtual destructor
            *********************/
            virtual ~GeneticVisionApp();

        private:
        int guiEnabled;
        string imageSetPath;
        Model model;
//        MainView view;

    };
}

#endif //GENETICVISION_GENETICVISIONAPP_H
