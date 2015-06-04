//
// Created by John Uiterwyk on 4/05/15.
//

#ifndef GENETICVISION_GPSIMULATION_H
#define GENETICVISION_GPSIMULATION_H


#include "../../AppConfig.h"
#include "../ImagePair.h"
#include "RunResult.h"
#include "../../rmitgp/GPConfig.h"
#include "GvPopulation.h"

namespace GeneticVision
{
    class GvSimulation {

    private:
        vector<ImagePair> * imagePairs;
        GvPopulation * pop;
        GPConfig * runConfig;
        AppConfig * appConfig;
    public:

        GvSimulation(GeneticVision::AppConfig * appConfig);
        RunResult tick(int);
        void cleanUp();
    };

}


#endif //GENETICVISION_GPSIMULATION_H
