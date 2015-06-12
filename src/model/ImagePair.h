//
// Created by John Uiterwyk on 27/04/15.
//

#ifndef GENETICVISION_IMAGEPAIR_H
#define GENETICVISION_IMAGEPAIR_H
#include <string.h>
#include <opencv2/core/core.hpp>
class ImagePair {
private:
    std::string filenameKey;
    std::string sourceImagePath;
    std::string targetImagePath;

    cv::Mat sourceImage;
    cv::Mat targetImage;
    cv::Mat resultImage;
public:
    ImagePair();
    void loadSourceImage(const std::string &imagePath);
    void loadTargetImage(const std::string &imagePath);

    cv::Mat &getSourceImage();
    cv::Mat &getTargetImage();
    cv::Mat & getResultImage();

    void setResultImage(cv::Mat & mat);
    void setFilenameKey(const std::string &filenameKey);
    const std::string & getFilenameKey() const;

    bool isPairValid();

    /*********************
     virtual destructor
    *********************/
    virtual ~ImagePair();

};


#endif //GENETICVISION_IMAGEPAIR_H
