//
// Created by John Uiterwyk on 6/29/15.
//

#ifndef GENETICVISION_PROGRAMPERFORMANCE_H
#define GENETICVISION_PROGRAMPERFORMANCE_H


#include "opencv2/core/core.hpp"
#include "../../rmitgp/GeneticProgram.h"
#include "../ImagePair.h"
#include "ProgramStats.h"

class ProgramResult
{
    public:
        ProgramStats statAverage;
        GeneticProgram geneticProgram;


        std::map<std::string, ImagePair> imagePairs;
        std::map<std::string, cv::Mat> imagePrediction;
        std::map<std::string, cv::Mat> imagePerformance;
    ProgramResult(GeneticProgram * geneticProgram, std::map<std::string, ImagePair> &imagePairs, std::map<std::string, cv::Mat> &imageResults):
            geneticProgram(*geneticProgram)
    {

        this->imagePairs = imagePairs;
        this->imagePrediction = imageResults;
    };

    ProgramStats testImage(cv::Mat target, cv::Mat test)
    {


        cv::Mat  trueNeg, falseNeg, truePos, falsePos, correct;


        //first get a mask of correct pixels
        cv::compare(target, test, correct, cv::CMP_EQ);

        //apply mask of
        cv::bitwise_and(correct,target,trueNeg);
        cv::bitwise_and(255 - correct,255 - target,falseNeg);

        // we use the inverse of
        cv::bitwise_and(correct,255 - target,truePos);
        cv::bitwise_and(255 - correct,target,falsePos);


        cv::Mat combined(target.size(), CV_8UC3, cv::Scalar(255,255,255));
        combined.setTo(cv::Scalar(0,0,0),truePos);
        combined.setTo(cv::Scalar(255,255,255),trueNeg);
        combined.setTo(cv::Scalar(0,200 ,0),falsePos);
        combined.setTo(cv::Scalar(0,0,255),falseNeg);
        //window.showImages(mats);

        ProgramStats stats;
        stats.positivePixels  = cv::countNonZero(255- target);
        stats.negativePixels  = cv::countNonZero(target);

        stats.truePositiveCount = cv::countNonZero(truePos);
        stats.falsePositiveCount = cv::countNonZero(falsePos);
        stats.trueNegativeCount = cv::countNonZero(trueNeg);
        stats.falseNegativeCount = cv::countNonZero(falseNeg);

    }
};


#endif //GENETICVISION_PROGRAMPERFORMANCE_H
