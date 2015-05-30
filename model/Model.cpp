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

    void Model::init(AppConfig &appConfig)
    {
        this->gpSimulation = new GpSimulation(appConfig);
        vector<vector<string> > imagePairPaths = appConfig.getImagePairPaths();
        this->imagePairs.resize(appConfig.getImagePairPaths().size());
        this->trainingImages.resize(appConfig.getImagePairPaths().size());
        this->groundTruthImages.resize(appConfig.getImagePairPaths().size());

        for(std::vector< vector<string> >::size_type i = 0; i != appConfig.getImagePairPaths().size(); i++)
        {
            vector<string> line = imagePairPaths[i];
            imagePairs[i].loadFromFilePath(appConfig.getImageDirectoryPath()+line[0],appConfig.getImageDirectoryPath()+line[1]);
            this->trainingImages[i] = imagePairs[i].getTrainingImage();
            this->groundTruthImages[i] = imagePairs[i].getGroundTruth();
        }

        std::cout << "Loaded "<< this->imageSetData.size() << " Image Pairs " << std::endl;
    }

    void Model::initSimulation()
    {
        this->gpSimulation->init(&this->imagePairs);
    }
    bool Model::tickSmulation()
    {
        return this->gpSimulation->tick(1);
    }

    vector<ImagePair> Model::getImagePairCollection() {
        return this->imagePairs;
    }

    vector<cv::Mat> Model::getTrainingImages() {
        return this->trainingImages;
    }

    vector<cv::Mat> Model::getGroundTruthImages() {
        return this->groundTruthImages;
    }
}
