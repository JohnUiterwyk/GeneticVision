//
// Created by John Uiterwyk on 5/25/15.
//

#include <opencv2/imgproc/imgproc.hpp>
#include "ImageInvert.h"
#include "../types/ReturnImage.h"
#include "../types/ReturnDouble.h"


const string ImageInvert::NAME = "cv_invert";

ImageInvert::ImageInvert(GPConfig *conf) : TFunction<ImageInvert, ReturnImage>(conf, 3)
{
    setArgNReturnType(0, ReturnImage::TYPENUM);
    setArgNReturnType(1, ReturnDouble::TYPENUM);
    setArgNReturnType(2, ReturnDouble::TYPENUM);
}

ImageInvert::~ImageInvert()
{
}


void ImageInvert::evaluate_impl(ReturnData *out)
{
    ReturnImage arg0;
    ReturnDouble arg1;
    ReturnDouble arg2;
    getArgN(0)->evaluate(&arg0);
    getArgN(1)->evaluate(&arg1);
    getArgN(2)->evaluate(&arg2);

    cv::Mat input = arg0.getData();
    cv::Mat detected_edges;
//    cv::Mat result;

//    int kernel_size = (int)(arg1.getData()*10) % 10 * 2+ 1;
    int kernel_size = 3;
    int lowThreshold = (int)(arg2.getData()*100) % 100 +1;
    int ratio = 3;

    cv::Canny( input, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );


    dynamic_cast<ReturnImage *>(out)->setData(detected_edges);
}