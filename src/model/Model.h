//
// Created by John Uiterwyk on 26/04/15.
//

#ifndef GENETICVISION_MODEL_H
#define GENETICVISION_MODEL_H
#include "ImagePair.h"
#include "simulation/GpSimulation.h"
#include <string>
#include <vector>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
namespace GeneticVision
{
    class Model {
    public:

        /*************
         Constructor.
        **************/
        Model();
        void init(AppConfig * appConfig);
        void initSimulation();
        bool  tickSmulation();

    private:
        GpSimulation * gpSimulation;

    };
}


#endif //GENETICVISION_MODEL_H
