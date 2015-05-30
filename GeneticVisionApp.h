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
            GeneticVisionApp(const string& jsonConfigFilePath);

            /*********************
             virtual destructor
            *********************/
            virtual ~GeneticVisionApp();

        private:
        Model model;
//        MainView view;

    };
}

#endif //GENETICVISION_GENETICVISIONAPP_H
