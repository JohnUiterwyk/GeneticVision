//
// Created by John Uiterwyk on 28/04/15.
//

#ifndef GENETICVISION_FITNESS_H
#define GENETICVISION_FITNESS_H

#include "../../rmitgp/GeneticProgram.h"
#include "../../rmitgp/GPConfig.h"
#include "../../rmitgp/Fitness.h"
#include "../ImagePair.h"
#include "../../view/OpenCVWindow.h"
#include "ImagePairCollection.h"
#include <map>

class VisionFitness : public Fitness
{
    private:
    double targetFitness;
    vector<ImagePair> * imagePairs;


    public:

    //Constructor
    VisionFitness(GPConfig *conf, GeneticVision::ImagePairCollection & imagePairCollection, double targetFitness );
    virtual ~VisionFitness();
    virtual void initFitness();
    virtual void assignFitness(GeneticProgram* pop[], int popSize);
    virtual bool solutionFound(GeneticProgram* pop[], int popSize);
    virtual bool isBetter(GeneticProgram* gp1, GeneticProgram* gp2);
    virtual bool isWorse(GeneticProgram* gp1, GeneticProgram* gp2);
    virtual bool isEqual(GeneticProgram* gp1, GeneticProgram* gp2);

    virtual double best();
    virtual double worst();

    void evaluateProgram(GeneticProgram* prog);
    std::map<std::string, cv::Mat> getResultImages(GeneticProgram* prog);
    void setTargetFitness(double target);
    void scoreCurrentImage(GeneticProgram *pop[], int batchStart, int batchEnd, double weight, cv::Mat targetImage);
};

#endif //GENETICVISION_FITNESS_H
