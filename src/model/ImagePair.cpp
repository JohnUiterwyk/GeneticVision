//
// Created by John Uiterwyk on 27/04/15.
//

#include "ImagePair.h"
#include <opencv2/highgui/highgui.hpp>

ImagePair::ImagePair() {

}
ImagePair::~ImagePair() {

}
void ImagePair::loadSourceImage(const std::string &imagePath)
{
    this->sourceImagePath = imagePath;
    this->sourceImage = cv::imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE );
}
void ImagePair::loadTargetImage(const std::string &imagePath)
{
    this->targetImagePath = imagePath;
    this->targetImage = cv::imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE );
}
void ImagePair::setResultImage(cv::Mat & mat) {
    this->resultImage = mat;
}

cv::Mat & ImagePair::getSourceImage() {
    return this->sourceImage;
}

cv::Mat & ImagePair::getTargetImage() {
    return this->targetImage;
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
    return (this->sourceImage.cols*this->sourceImage.rows > 0 && this->targetImage.cols*this->targetImage.rows > 0)  ;
}
