//
// Created by John Uiterwyk on 28/04/15.
//

#include "VisionFitness.h"
#include "types/ReturnImage.h"
#include "terminals/ImageInput.h"
#include "ProgramStats.h"
#include <math.h>
#include <thread>


VisionFitness::VisionFitness(GPConfig *conf, GeneticVision::ImagePairCollection & imagePairCollection, double targetFitness, int numOfThreads) : Fitness(conf)
{
    this->imagePairs = &imagePairCollection.getVector();
    this->targetFitness = targetFitness;
    this->numOfThreads = numOfThreads;
}

VisionFitness::~VisionFitness() { }

void VisionFitness::initFitness()
{
}

void VisionFitness::assignFitness(GeneticProgram *pop[], int popSize)
{
    int batchSize = popSize/this->numOfThreads;
    if(popSize % this->numOfThreads != 0){
        batchSize +=1;
    }

    double weight = 1/(double)this->imagePairs->size();

    // reset fitness
    for(int i=0; i<popSize; i++)
    {
        pop[i]->setFitness(0);
    }

    ImagePair * testPair;
    std::vector<std::thread> threads;

    for(std::vector<ImagePair>::size_type i = 0; i != this->imagePairs->size(); i++)
    {
        int batchStart = 0;
        int batchEnd = 0;

        //setup the image to test
        testPair = &(this->imagePairs->at(i));
        ImageInput::setValue(testPair->getSourceImage());
        cv::Mat targetImage = testPair->getTargetImage();

        for(int j=0; j<this->numOfThreads; j++) {

            if (batchStart >= popSize) {
                break;//this shouldnt happen;
            }
            batchEnd  = std::min(batchStart+batchSize-1, popSize-1);

            // create a thread to evaluate a batch of the population using the current image
            // this uses a lambda function approach
            auto evalBatch = [pop, batchStart, batchEnd, weight, targetImage](){
                for(int k=batchStart; k<=batchEnd; k++)
                {
                    GeneticProgram * prog = pop[k];
                    ReturnImage returnImage;
                    double score = 0;
                    int totalPixelCount = targetImage.cols * targetImage.rows;
                    prog->evaluate(&returnImage);

                    cv::Mat  trueNeg,  truePos, correct;
                    cv::compare(targetImage, returnImage.getData(), correct, cv::CMP_EQ);

                    //apply mask of negative pixels
                    cv::bitwise_and(correct,targetImage,trueNeg);

                    // we use the inverse of
                    cv::bitwise_and(correct,255 - targetImage,truePos);

                    ProgramStats stats;
                    stats.positivePixels  = cv::countNonZero(255- targetImage);
                    stats.negativePixels  = cv::countNonZero(targetImage);

                    stats.truePositiveCount = cv::countNonZero(truePos);
                    stats.trueNegativeCount = cv::countNonZero(trueNeg);
                    stats.falsePositiveCount = stats.positivePixels - stats.truePositiveCount;
                    stats.falseNegativeCount = stats.negativePixels - stats.trueNegativeCount;


                    // this add the weighted image error rate
                    // added to the total score so far
                    prog->setFitness(prog->getFitness()+stats.getNormalisedErrorRate()* weight);

                }
            };
            threads.push_back(std::thread(evalBatch));
            batchStart = batchEnd + 1;

        }

        for(std::vector<std::thread>::size_type i = 0; i != threads.size(); i++)
        {
            threads.at(i).join();
        }
        threads.clear();

    }

}


std::map<std::string, cv::Mat> VisionFitness::getResultImages(GeneticProgram* prog)
{

    std::map<std::string, cv::Mat> resultMap;
    ReturnImage returnImage;
    ImagePair * testPair;
    for(std::vector<ImagePair>::size_type i = 0; i != this->imagePairs->size(); i++)
    {
        testPair = &(this->imagePairs->at(i));
        resultMap.insert(std::make_pair(testPair->getFilenameKey(), cv::Mat::zeros(1,1,CV_32F)));
        ImageInput::setValue(testPair->getSourceImage());
        prog->evaluate(&returnImage);
        //cv::absdiff(testPair->getTargetImage(),returnImage.getData(),resultMap[testPair->getFilenameKey()]);
        returnImage.getData().copyTo(resultMap[testPair->getFilenameKey()]);
    }
    return resultMap;
}
bool VisionFitness::solutionFound(GeneticProgram *pop[], int popSize) {
    int i=0;
    for (; i<popSize; i++)
    {
        if (pop[i]->getFitness() <= targetFitness)
            return true;
    }
    return false;
}

bool VisionFitness::isBetter(GeneticProgram *gp1, GeneticProgram *gp2) {

    return (gp1->getFitness() < gp2->getFitness());
}

bool VisionFitness::isWorse(GeneticProgram *gp1, GeneticProgram *gp2) {

    return (gp1->getFitness() > gp2->getFitness());
}

bool VisionFitness::isEqual(GeneticProgram *gp1, GeneticProgram *gp2) {
    return (gp1->getFitness() == gp2->getFitness());
}

double VisionFitness::best() {
    return 0;
}

double VisionFitness::worst() {
    return DBL_MAX;
}


