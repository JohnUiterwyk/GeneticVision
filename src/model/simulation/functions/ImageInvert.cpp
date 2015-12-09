//
// Created by John Uiterwyk on 5/25/15.
//

#include <opencv2/imgproc/imgproc.hpp>
#include "ImageInvert.h"
#include "../types/ReturnImage.h"
#include "../types/ReturnDouble.h"


const string ImageInvert::NAME = "cv_invert";

ImageInvert::ImageInvert(GPConfig *conf) : TFunction<ImageInvert, ReturnImage>(conf, 1)
{
    setArgNReturnType(0, ReturnImage::TYPENUM);
}

ImageInvert::~ImageInvert()
{
}


void ImageInvert::evaluate_impl(ReturnData *out)
{
    ReturnImage arg0;
    getArgN(0)->evaluate(&arg0);
    cv::Mat input = arg0.getData();
    cv::Mat result;
    result = 255 - input;


    dynamic_cast<ReturnImage *>(out)->setData(result);
}