//
// Created by John Uiterwyk on 26/04/15.
//

#include <iostream>
#include "Model.h"

using namespace std;
namespace GeneticVision
{


    Model::Model() {
    }

    void Model::init(AppConfig * appConfig)
    {
        this->gpSimulation = new GpSimulation(appConfig);
//        vector<ImagePair > imagePairs = appConfig->getImagePairs();
//        this->trainingImages.resize(appConfig->getImagePairs().size());
//        this->groundTruthImages.resize(appConfig->getImagePairs().size());
//
//        for(std::vector< vector<string> >::size_type i = 0; i != appConfig->getImagePairs().size(); i++)
//        {
//
//            this->trainingImages[i] = imagePairs[i].getTrainingImage();
//            this->groundTruthImages[i] = imagePairs[i].getGroundTruth();
//        }
//        std::cout << "Loaded "<< this->imageSetData.size() << " Image Pairs " << std::endl;

    }

    void Model::initSimulation()
    {
        this->gpSimulation->init(this->imagePairs);
    }
    bool Model::tickSmulation()
    {
        return this->gpSimulation->tick(1);
    }

}
