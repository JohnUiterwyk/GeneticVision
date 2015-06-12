//
// Created by John Uiterwyk on 5/31/15.
//

#ifndef GENETICVISION_RUNRESULT_H
#define GENETICVISION_RUNRESULT_H


#include <string>
#include <map>
#include <vector>
#include <opencv2/core/core.hpp>

class RunResult {
public:
    int generationId;
    int bestProgramId;
    double bestProgramFitness;
    std::string bestProgramString;
    bool solutionFound;
    std::vector<cv::Mat> bestResultImages;
    std::map<std::string, cv::Mat> resultMap;

    std::string toString();


};


#endif //GENETICVISION_RUNRESULT_H
