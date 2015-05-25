//
// Created by John Uiterwyk on 28/04/15.
//

#include "VisionFitness.h"
#include "types/ReturnImage.h"
#include "terminals/ImageInput.h"

VisionFitness::VisionFitness(GPConfig *conf) : Fitness(conf), outputWindow("Best",100,100), testWindow("Test",100,100)
{

}

VisionFitness::~VisionFitness() { }

void VisionFitness::initFitness()
{
  goalValue = 0;
  testPair.loadFromFilePath("data/mg-300.jpg","data/mg-truth.jpg");
}
void VisionFitness::assignFitness(GeneticProgram *pop[], int popSize)
{
    int i;
    GeneticProgram* best = pop[0];
    best->setFitness(1000000);

    for(i=0; i<popSize; i++)
    {
        this->evalutateProgram(pop[i]);
        if(this->isBetter(pop[i],best))
        {
            best = pop[i];
        }
    }

    outputProgram(best);

}
void VisionFitness::evalutateProgram(GeneticProgram* prog)
{

    string progString;
    prog->print(progString);
    ReturnImage returnImage;

    ImageInput::setValue(testPair.getTrainingImage());

    prog->setFitness(0.0);
    prog->evaluate(&returnImage);

    int size = 90000;

    cv::Mat diff_mat;
    cv::compare(testPair.getGroundTruth(), returnImage.getData(), diff_mat, cv::CMP_EQ);
    int nonzero = cv::countNonZero(diff_mat);
    double score = 100* (size - (double)nonzero)/size;
    prog->setFitness(score);
    testWindow.showImage(returnImage.getData());

}

void VisionFitness::outputProgram(GeneticProgram* prog)
{

    string progString;
    prog->print(progString);
    ReturnImage returnImage;
    ImageInput::setValue(testPair.getTrainingImage());
    prog->evaluate(&returnImage);
    outputWindow.showImage(returnImage.getData());
    cout << "Best: " << prog->getFitness() << " " << progString << endl;


}
bool VisionFitness::solutionFound(GeneticProgram *pop[], int popSize) {
    int i=0;
    for (; i<popSize; i++)
    {
        if (pop[i]->getFitness() <= 0.1)
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
