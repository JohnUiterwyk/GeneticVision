//
// Created by John Uiterwyk on 5/25/15.
//

#include <opencv2/imgproc/imgproc.hpp>
#include "ImageSobel.h"
#include "../types/ReturnImage.h"
#include "../types/ReturnDouble.h"


const string ImageSobel::NAME = "cv_sobel";

ImageSobel::ImageSobel(GPConfig *conf) : TFunction(conf, 3)
{
    setArgNReturnType(0, ReturnImage::TYPENUM);
    setArgNReturnType(1, ReturnDouble::TYPENUM);
    setArgNReturnType(2, ReturnDouble::TYPENUM);
}

ImageSobel::~ImageSobel()
{
}


void ImageSobel::evaluate_impl(ReturnData *out)
{
    ReturnImage arg0;
    ReturnDouble arg1;
    ReturnDouble arg2;
    getArgN(0)->evaluate(&arg0);
    getArgN(1)->evaluate(&arg1);
    getArgN(2)->evaluate(&arg2);

    cv::Mat result;
    cv::Mat input = arg0.getData();
    int x = (int)(arg1.getData()*2) % 2+1;
    int y = (int)(arg2.getData()*2) % 2+1;

    cv::Sobel(input, result, CV_8U, x, y);


    dynamic_cast<ReturnImage *>(out)->setData(result);
}