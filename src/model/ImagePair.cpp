//
// Created by John Uiterwyk on 27/04/15.
//

#include "ImagePair.h"
#include <opencv2/highgui/highgui.hpp>

ImagePair::ImagePair() {

}
ImagePair::~ImagePair() {

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
void ImagePair::setResultImage(cv::Mat & mat) {
    this->resultImage = mat;
}

cv::Mat & ImagePair::getTrainingImage() {
    return this->trainingImage;
}

cv::Mat & ImagePair::getGroundTruth() {
    return this->groundTruth;
}

cv::Mat & ImagePair::getResultImage() {
    return this->resultImage;
}

void ImagePair::setFilenameKey(const std::string &filenameKey) {
    this->filenameKey = filenameKey;
}
const std::string & ImagePair::getFilenameKey() const {
    return this->filenameKey;
}

bool ImagePair::isPairValid() {
    return (this->trainingImage.cols*this->trainingImage.rows > 0 && this->groundTruth.cols*this->groundTruth.rows > 0)  ;
}
