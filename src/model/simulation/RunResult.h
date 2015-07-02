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
#include "ProgramStats.h"
#include "../ImagePair.h"

using namespace std;
using namespace cv;
class RunResult {
public:
    RunResult();
    int generationId;
    ProgramStats statAverage;
    GeneticProgram * bestProgram;
    std::map<std::string, ProgramStats> stats;
    std::map<std::string, cv::Mat> resultImagesMap;
    std::map<std::string, cv::Mat> performanceImagesMap;

    bool solutionFound;

    void testPerformance(std::vector<ImagePair> &imagePairs );
    void testImage(cv::Mat &target, cv::Mat &test, string filenameKey);


};


#endif //GENETICVISION_RUNRESULT_H
