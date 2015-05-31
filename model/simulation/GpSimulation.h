//
// Created by John Uiterwyk on 4/05/15.
//

#ifndef GENETICVISION_GPSIMULATION_H
#define GENETICVISION_GPSIMULATION_H


#include "../../AppConfig.h"
#include "../../rmitgp/Population.h"
#include "../ImagePair.h"

class GpSimulation {

private:
    vector<ImagePair> * imagePairs;
    Population * pop;
    GPConfig * runConfig;
public:

    GpSimulation(GeneticVision::AppConfig * appConfig);
    bool tick(int);
    void cleanUp();
};


#endif //GENETICVISION_GPSIMULATION_H
