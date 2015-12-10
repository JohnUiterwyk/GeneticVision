//
// Created by John Uiterwyk on 5/31/15.
//

#include "RunResult.h"
#include <sstream>
#include <iostream>

RunResult::RunResult()
{
};
void RunResult::testPerformance(std::vector<ImagePair> &imagePairs )
{


        int count = 0;

        cv::Mat  trueNeg, falseNeg, truePos, falsePos, correct;
        ImagePair  testPair;
        for(std::vector<ImagePair>::size_type i = 0; i != imagePairs.size(); i++)
        {
                testPair = imagePairs.at(i);
                string filenameKey = testPair.getFilenameKey();
                cv::Mat targetImage = testPair.getTargetImage();

                map<string,cv::Mat>::iterator resultImagesIterator = this->resultImagesMap.find(filenameKey);
                cv::Mat resultImage;
                if(resultImagesIterator != this->resultImagesMap.end())
                {
                        //element found;
                        resultImage = resultImagesIterator->second;


                        //first get a mask of correct pixels
                        cv::compare(targetImage, resultImage, correct, cv::CMP_EQ);

                        //apply mask of
                        cv::bitwise_and(correct,targetImage,trueNeg);
                        cv::bitwise_and(255 - correct,255 - targetImage,falseNeg);

                        // we use the inverse of
                        cv::bitwise_and(correct,255 - targetImage,truePos);
                        cv::bitwise_and(255 - correct,targetImage,falsePos);


                        cv::Mat performanceImage(targetImage.size(), CV_8UC3, cv::Scalar(255,255,255));
                        performanceImage.setTo(cv::Scalar(0,0,0),truePos);
                        performanceImage.setTo(cv::Scalar(255,255,255),trueNeg);
                        performanceImage.setTo(cv::Scalar(0,200 ,0),falsePos);
                        performanceImage.setTo(cv::Scalar(0,0,255),falseNeg);

                        // add result
                        if(this->performanceImagesMap.find(filenameKey) == this->performanceImagesMap.end())
                        {
                                this->performanceImagesMap.insert(std::make_pair(filenameKey, cv::Mat::zeros(1,1,CV_8UC3)));
                                performanceImage.copyTo(this->performanceImagesMap[filenameKey]);
                        }

                        ProgramStats stats;
                        stats.positivePixels  = cv::countNonZero(255- targetImage);
                        stats.negativePixels  = cv::countNonZero(targetImage);

                        stats.truePositiveCount = cv::countNonZero(truePos);
                        stats.trueNegativeCount = cv::countNonZero(trueNeg);
                        stats.falsePositiveCount = cv::countNonZero(falsePos);
                        stats.falseNegativeCount = cv::countNonZero(falseNeg);
                        statAverage.add(stats, 1/(double)imagePairs.size());
                } else{
                        std::cout << "Couldnt find key" << endl;
                }
        }
};
void RunResult::testImage(cv::Mat &target, cv::Mat &test, string filenameKey)
{


};
