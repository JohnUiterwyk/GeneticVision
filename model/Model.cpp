//
// Created by John Uiterwyk on 26/04/15.
//

#include <iostream>
#include "Model.h"
#include "../util/csv/CSVParser.h"

namespace GeneticVision
{


    Model::Model() {
        this->gpSimulation = new GpSimulation();
    }

    void Model::loadImages(const string &imageSetPath)
    {
        CSVParser csvParser(imageSetPath+"image-set.csv");
        csvParser.parse();
        this->imageSetData = csvParser.getData();

        this->imagePairs.resize(this->imageSetData.size());
        this->trainingImages.resize(this->imageSetData.size());
        this->groundTruthImages.resize(this->imageSetData.size());

        for(std::vector< vector<string> >::size_type i = 0; i != this->imageSetData.size(); i++)
        {
            vector<string> line = this->imageSetData[i];
            imagePairs[i].loadFromFilePath(imageSetPath+line[0],imageSetPath+line[1]);
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
