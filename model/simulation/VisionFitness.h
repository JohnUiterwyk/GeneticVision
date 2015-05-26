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

class VisionFitness : public Fitness
{
    private:
    double goalValue;
    vector<ImagePair> * imagePairs;
    vector<cv::Mat> lastResult;
    OpenCVWindow outputWindow;


    public:
    //Constructor
    VisionFitness(GPConfig *conf, vector<ImagePair> * );
    virtual ~VisionFitness();
    virtual void initFitness();
    virtual void assignFitness(GeneticProgram* pop[], int popSize);
    void evalutateProgram(GeneticProgram* prog);
    virtual bool solutionFound(GeneticProgram* pop[], int popSize);
    virtual bool isBetter(GeneticProgram* gp1, GeneticProgram* gp2);
    virtual bool isWorse(GeneticProgram* gp1, GeneticProgram* gp2);
    virtual bool isEqual(GeneticProgram* gp1, GeneticProgram* gp2);

    virtual double best();
    virtual double worst();

    void outputProgram(GeneticProgram *prog);
};

#endif //GENETICVISION_FITNESS_H
