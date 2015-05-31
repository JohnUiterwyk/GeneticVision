//
// Created by John Uiterwyk on 27/04/15.
//

#include "ImagePair.h"
#include <opencv2/highgui/highgui.hpp>

ImagePair::ImagePair() {

}

void ImagePair::loadTrainingImage(const std::string &trainingImagePath)
{
    this->trainingImagePath = trainingImagePath;
    this->trainingImage = cv::imread( trainingImagePath, CV_LOAD_IMAGE_GRAYSCALE );
}
void ImagePair::loadGroundTruth(const std::string &groundTruthPath)
{
    this->groundTruthPath = groundTruthPath;
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

cv::Mat ImagePair::getResultImage() {
    return this->resultImage;
}
