//
// Created by John Uiterwyk on 5/25/15.
//

#include <opencv2/imgproc/imgproc.hpp>
#include "ImageErode.h"
#include "../types/ReturnImage.h"
#include "../types/ReturnDouble.h"


const string ImageErode::NAME = "cv_erode";

ImageErode::ImageErode(GPConfig *conf) : TFunction(conf, 3)
{
    setArgNReturnType(0, ReturnImage::TYPENUM);
    setArgNReturnType(1, ReturnDouble::TYPENUM);
    setArgNReturnType(2, ReturnDouble::TYPENUM);
}

ImageErode::~ImageErode()
{
}


void ImageErode::evaluate_impl(ReturnData *out)
{
    ReturnImage arg0;
    ReturnDouble arg1;
    ReturnDouble arg2;
    getArgN(0)->evaluate(&arg0);
    getArgN(1)->evaluate(&arg1);
    getArgN(2)->evaluate(&arg2);

    cv::Mat element;
    cv::Mat result;
    cv::Mat input = arg0.getData();
    int erosion_size = (int)(arg1.getData()*21)%21+1;
    int erosion_type = (int)(arg2.getData()*3)%3;
    if( erosion_type == 0){ erosion_type = cv::MORPH_RECT; }
    else if( erosion_type == 1 ){ erosion_type = cv::MORPH_CROSS; }
    else if( erosion_type == 2) { erosion_type = cv::MORPH_ELLIPSE; }

    element = cv::getStructuringElement( erosion_type,
                                         cv::Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                         cv::Point( erosion_size, erosion_size ) );
    /// Apply the erosion operation
    erode( input, result, element );


    dynamic_cast<ReturnImage *>(out)->setData(result);
}