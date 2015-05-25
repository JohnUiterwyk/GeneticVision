//
// Created by John Uiterwyk on 5/25/15.
//

#include "ImageBlend.h"
#include "../types/ReturnImage.h"
#include "../types/ReturnDouble.h"


const string ImageBlend::NAME = "cv_blend";

ImageBlend::ImageBlend(GPConfig *conf) : TFunction(conf, 3)
{
    setArgNReturnType(0, ReturnDouble::TYPENUM);
    setArgNReturnType(1, ReturnImage::TYPENUM);
    setArgNReturnType(2, ReturnImage::TYPENUM);
}

ImageBlend::~ImageBlend()
{
}


void ImageBlend::evaluate_impl(ReturnData *out)
{
    ReturnDouble arg1;
    ReturnImage arg2;
    ReturnImage arg3;
    getArgN(0)->evaluate(&arg1);
    getArgN(1)->evaluate(&arg2);
    getArgN(2)->evaluate(&arg3);

    double alpha = arg1.getData();
    double beta = 1.0 - alpha;

    cv::Mat src1 = arg2.getData();
    cv::Mat src2 = arg3.getData();
    cv::Mat result;

    cv::addWeighted( src1, alpha, src2, beta, 0.0, result);



    //and now do some MAGIC!!
//    int threshold = (int)(fmod(returnDouble.getData(),1) * 255);
//    cv::Mat result = returnImage.getData() > threshold;

    dynamic_cast<ReturnImage *>(out)->setData(result);
}