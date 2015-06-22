//
// Created by John Uiterwyk on 28/04/15.
//

#include "VisionFitness.h"
#include "types/ReturnImage.h"
#include "terminals/ImageInput.h"
#include <thread>
#include <math.h>


VisionFitness::VisionFitness(GPConfig *conf, GeneticVision::ImagePairCollection & imagePairCollection) : Fitness(conf)
{
    this->imagePairs = &imagePairCollection.getCollection();
}

VisionFitness::~VisionFitness() { }

void VisionFitness::initFitness()
{
    goalValue = 0;
}
void VisionFitness::assignFitness(GeneticProgram *pop[], int popSize)
{

    int threadCount = 2;
    int batchStart = 0;
    int batchSize = popSize/threadCount+1;
    int batchEnd = 0;

    int i;
    for(i=0; i<threadCount; i++) {

        if (batchStart >= popSize) {
            cerr << "ERROR VisionFitness::assignFitness : batchStart " << batchStart << "out of range " << popSize <<
                                                                                                           endl;
            throw;//this shouldnt happen;
        }
        batchEnd  = std::min(batchStart+batchSize-1, popSize-1);
        this->assignFitnessBatch(pop,batchStart,batchEnd);
        batchStart = batchEnd + 1;

    }



    //outputProgram(best);



}
void VisionFitness::assignFitnessBatch(GeneticProgram *pop[], int batchStart, int batchEnd)
{
    int i=batchStart;

    for(i=batchStart; i<=batchEnd; i++)
    {

        this->evaluateProgram(pop[i]);
    }
}

void VisionFitness::evaluateProgram(GeneticProgram* prog)
{
    ReturnImage returnImage;
    ImagePair * testPair;
    double score = 0;
    int size = this->imagePairs->at(0).getSourceImage().cols * this->imagePairs->at(0).getSourceImage().rows;


    prog->setFitness(0.0);
    for(std::vector<ImagePair>::size_type i = 0; i != this->imagePairs->size(); i++)
    {
        testPair = &(this->imagePairs->at(i));
        ImageInput::setValue(testPair->getSourceImage());
        prog->evaluate(&returnImage);

        // measure difference between result image and truth
        cv::Mat diff_mat;
        cv::compare(testPair->getTargetImage(), returnImage.getData(), diff_mat, cv::CMP_EQ);
        int nonzero = cv::countNonZero(diff_mat);

        // this is the number correct pixels divided by total number of pixels
        // added to the total score so far
        score += 100* (size - (double)nonzero)/size;
    }

    // Idea for improving fitness:
    // use an ensemble for fitness from best X of past generations;  add Mats , then use threshold of n/2
    // also use boosting: keep a running weight for each image.
    // decrease  weight of correctly classified examples.
    // Then use that weight when calculating fitness of next generation
    // Also, make this a setting in the config for fitness function
    //
    // current approach:
    // average the score from all result images
    prog->setFitness((double)(score/(double)(this->imagePairs->size())));

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
        if (pop[i]->getFitness() <= 0.02)
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
