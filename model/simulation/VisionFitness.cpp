//
// Created by John Uiterwyk on 28/04/15.
//

#include "VisionFitness.h"
#include "types/ReturnImage.h"
#include "terminals/ImageInput.h"

VisionFitness::VisionFitness(GPConfig *conf, vector<ImagePair> * imagePairs) : Fitness(conf)
{
    this->imagePairs = imagePairs;
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
        this->evaluateProgram(pop[i]);
        if(this->isBetter(pop[i],best))
        {
            best = pop[i];
        }
    }

    //outputProgram(best);



}
void VisionFitness::evaluateProgram(GeneticProgram* prog)
{
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

        // measure difference between result image and truth
        cv::Mat diff_mat;
        cv::compare(testPair->getGroundTruth(), returnImage.getData(), diff_mat, cv::CMP_EQ);
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

vector<cv::Mat> VisionFitness::getResultImages(GeneticProgram* prog)
{
    vector<cv::Mat> resultImages(this->imagePairs->size(),cv::Mat::zeros(1,1,CV_32F));
    ReturnImage returnImage;
    ImagePair * testPair;
    for(std::vector<ImagePair>::size_type i = 0; i != this->imagePairs->size(); i++)
    {
        testPair = &(this->imagePairs->at(i));
        ImageInput::setValue(testPair->getTrainingImage());
        prog->evaluate(&returnImage);
        returnImage.getData().copyTo(resultImages[i]);
    }
    return resultImages;
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
