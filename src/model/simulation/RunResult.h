//
// Created by John Uiterwyk on 5/31/15.
//

#ifndef GENETICVISION_RUNRESULT_H
#define GENETICVISION_RUNRESULT_H


#include <string>
#include <map>
#include <vector>
#include <opencv2/core/core.hpp>
#include "../../rmitgp/GeneticProgram.h"
#include "ProgramResult.h"

using namespace std;
using namespace cv;
class RunResult {
public:
    RunResult();
    int generationId;
    GeneticProgram * best;

    ProgramResult * bestPerformance;

    bool solutionFound;
    map<string, Mat> resultMap;



};


#endif //GENETICVISION_RUNRESULT_H
