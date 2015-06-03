//
// Created by John Uiterwyk on 27/04/15.
//

#ifndef GENETICVISION_IMAGEPAIR_H
#define GENETICVISION_IMAGEPAIR_H
#include <string.h>
#include <opencv2/core/core.hpp>
class ImagePair {

private:
    std::string trainingImagePath;
    std::string groundTruthPath;

    cv::Mat trainingImage;
    cv::Mat groundTruth;
    cv::Mat resultImage;
public:
    ImagePair();
    void loadTrainingImage(const std::string &trainingImagePath);
    void loadGroundTruth(const std::string &groundTruthPath);

    cv::Mat getTrainingImage();
    cv::Mat getGroundTruth();
    cv::Mat getResultImage();

    /*********************
     virtual destructor
    *********************/
    virtual ~ImagePair();

};


#endif //GENETICVISION_IMAGEPAIR_H
