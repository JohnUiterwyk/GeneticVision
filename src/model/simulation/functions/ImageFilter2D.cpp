//
// Created by John Uiterwyk on 12/2/15.
//

#include "ImageFilter2D.h"
//
// Created by John Uiterwyk on 5/19/15.
// int(rand * 20 -10) = kernel element
//

#include <string>
#include <math.h>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
#include "opencv2/imgproc/imgproc.hpp"
#include "ImageFilter2D.h"
#include "../types/ReturnImage.h"
#include "../types/ReturnDouble.h"

ImageFilter2D::ImageFilter2D(GPConfig *config) :
        Function(ReturnImage::TYPENUM, 10, "cv_filter2D", config)
{
    setArgNReturnType(0,ReturnImage::TYPENUM);
    for( int i = 1; i <= 9; i++)
    {
        setArgNReturnType(i,ReturnDouble::TYPENUM);

    }
}

ImageFilter2D::~ImageFilter2D() { }

Function* ImageFilter2D::generate(const string &name, GPConfig *config)
{
    if (name == "")
    {
        return new ImageFilter2D(config);
    }
    else if (name == "cv_filter2D")
    {
        return new ImageFilter2D(config);
    }

    return NULL;
}

void ImageFilter2D::evaluate(ReturnData *out)
{
    if(out->getTypeNum() != ReturnImage::TYPENUM)
    {
        throw string("ImageFilter2D::evaluate, incorrect ReturnData type");
    }
    for( int i = 1; i <= 9; i++)
    {
        if (getArgNReturnType(i) != getArgN(i)->getReturnType())
        {
            throw string("ImageFilter2D::evaluate Error argument has incorrect return type");
        }

    }
    ReturnImage returnImage;
    ReturnDouble returnDouble1;
    ReturnDouble returnDouble2;
    ReturnDouble returnDouble3;
    ReturnDouble returnDouble4;
    ReturnDouble returnDouble5;
    ReturnDouble returnDouble6;
    ReturnDouble returnDouble7;
    ReturnDouble returnDouble8;
    ReturnDouble returnDouble9;

    getArgN(0)->evaluate(&returnImage);
    getArgN(1)->evaluate(&returnDouble1);
    getArgN(2)->evaluate(&returnDouble2);
    getArgN(3)->evaluate(&returnDouble3);
    getArgN(4)->evaluate(&returnDouble4);
    getArgN(5)->evaluate(&returnDouble5);
    getArgN(6)->evaluate(&returnDouble6);
    getArgN(7)->evaluate(&returnDouble7);
    getArgN(8)->evaluate(&returnDouble8);
    getArgN(9)->evaluate(&returnDouble9);

    //and now do some OpenCV MAGIC!!


    cv::Mat inputImage = returnImage.getData();
    double kernelValue1 = returnDouble1.getData();
    double kernelValue2 = returnDouble2.getData();
    double kernelValue3 = returnDouble3.getData();
    double kernelValue4 = returnDouble4.getData();
    double kernelValue5 = returnDouble5.getData();
    double kernelValue6 = returnDouble6.getData();
    double kernelValue7 = returnDouble7.getData();
    double kernelValue8 = returnDouble8.getData();
    double kernelValue9 = returnDouble9.getData();

    cv::Mat result; //do not initialise, let OpenCV do it since it handles memory management of Mats.

    cv::Point anchor = cv::Point( -1, -1 );
    double delta = 0;
    int ddepth = -1;

    //Filter2D
    cv::Mat kernel = (cv::Mat_<double>(3,3) <<
            kernelValue1, kernelValue2, kernelValue3,
            kernelValue4, kernelValue5, kernelValue6,
            kernelValue7, kernelValue8, kernelValue9);

    /// Apply filter
    filter2D(inputImage, result, ddepth , kernel, anchor, delta, cv::BORDER_DEFAULT );

    // end MAGIC!!!


    dynamic_cast<ReturnImage *>(out)->setData(result);
}

Node* ImageFilter2D::copy()
{
    Function *tmp = new ImageFilter2D(config);
    if(tmp == NULL)
    {
        throw string(" ImageFilter2D::copy error, out of memory");
    }
    for( int i = 0; i <= 9; i++)
    {
        tmp->setArgN(i, getArgN(i)->copy());

    }

    return dynamic_cast<Node *>(tmp);
}