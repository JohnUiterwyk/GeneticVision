//
// Created by John Uiterwyk on 28/04/15.
//

#include "VisionFitness.h"
#include "types/ReturnImage.h"
#include "terminals/ImageInput.h"

VisionFitness::VisionFitness(GPConfig *conf, vector<ImagePair> * imagePairs) : Fitness(conf)
{
    this->imagePairs = imagePairs;
    this->lastResult.resize(this->imagePairs->size(),cv::Mat::zeros(1,1,CV_32F));
}

VisionFitness::~VisionFitness() { }

void VisionFitness::initFitness()
{
    goalValue = 0;
}
void VisionFitness::assignFitness(GeneticProgram *pop[], int popSize)
{
    int i;
    GeneticProgram* best = pop[0];

    for(i=0; i<popSize; i++)
    {
        this->evalutateProgram(pop[i]);
        if(this->isBetter(pop[i],best))
        {
            best = pop[i];
        }
    }

    //outputProgram(best);



}
vector<cv::Mat > * VisionFitness::evalutateProgram(GeneticProgram* prog)
{

    string progString;
    prog->print(progString);
    ReturnImage returnImage;
    ImagePair * testPair;
    double score = 0;
    int size = this->imagePairs->at(0).getTrainingImage().cols * this->imagePairs->at(0).getTrainingImage().rows;


    prog->setFitness(0.0);
    for(std::vector<ImagePair>::size_type i = 0; i != this->imagePairs->size(); i++)
    {
        testPair = &(this->imagePairs->at(i));
        ImageInput::setValue(testPair->getTrainingImage());
        prog->evaluate(&returnImage);
        returnImage.getData().copyTo(lastResult[i]);

        cv::Mat diff_mat;
        cv::compare(testPair->getGroundTruth(), returnImage.getData(), diff_mat, cv::CMP_EQ);
        int nonzero = cv::countNonZero(diff_mat);
        score += 100* (size - (double)nonzero)/size;
    }

    prog->setFitness((double)(score/(double)(this->imagePairs->size())));
    return &this->lastResult;

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
