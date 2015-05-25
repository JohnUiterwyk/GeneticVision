//
// Created by John Uiterwyk on 4/05/15.
//

#ifndef GENETICVISION_GPSIMULATION_H
#define GENETICVISION_GPSIMULATION_H


#include "../../rmitgp/Population.h"
#include "../ImagePair.h"

class GpSimulation {

private:
    vector<ImagePair> * imagePairs;
    Population * pop;
    GPConfig * runConfig;
public:

    GpSimulation();
    void init(vector<ImagePair> *imagePairs);
    void run();
    bool tick(int);
};


#endif //GENETICVISION_GPSIMULATION_H
