//
// Created by John Uiterwyk on 27/04/15.
//

#include "ImagePair.h"
#include <opencv2/highgui/highgui.hpp>

ImagePair::ImagePair() {

}

void ImagePair::loadFromFilePath(const std::string &trainingImagePath, const std::string &groundTruthPath)
{

    this->trainingImage = cv::imread( trainingImagePath, CV_LOAD_IMAGE_GRAYSCALE );
    this->groundTruth = cv::imread( groundTruthPath, CV_LOAD_IMAGE_GRAYSCALE );
}

cv::Mat ImagePair::getTrainingImage() {
    return this->trainingImage;
}

cv::Mat ImagePair::getGroundTruth() {
    return this->groundTruth;
}

ImagePair::~ImagePair() {

}
