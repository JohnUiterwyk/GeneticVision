//
// Created by John Uiterwyk on 5/19/15.
//

#include "ReturnImage.h"
const int ReturnImage::TYPENUM=2;

ReturnImage::ReturnImage() : ReturnData()
{
    data = cv::Mat::zeros(1,1,CV_32F);
    initTypeNum();
}

ReturnImage::~ReturnImage()
{
}

void ReturnImage::initTypeNum()
{
    setTypeNum(ReturnImage::TYPENUM);
}

void ReturnImage::setData(cv::Mat image)
{
    data = image;
}

cv::Mat ReturnImage::getData() const
{
    return data;
}


