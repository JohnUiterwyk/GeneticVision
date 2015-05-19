//
// Created by John Uiterwyk on 5/19/15.
//

#include <string>
#include <math.h>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

#include "ImageGaussianBlur.h"
#include "../types/ReturnImage.h"
#include "../types/ReturnDouble.h"

ImageGaussianBlur::ImageGaussianBlur(GPConfig *config) :
        Function(ReturnImage::TYPENUM, 2, "cv_gaussian", config)
{
    setArgNReturnType(0,ReturnImage::TYPENUM);
    setArgNReturnType(1,ReturnDouble::TYPENUM);
}

ImageGaussianBlur::~ImageGaussianBlur() { }

Function* ImageGaussianBlur::generate(const string &name, GPConfig *config)
{
    if (name == "")
    {
        return new ImageGaussianBlur(config);
    }
    else if (name == "cv_gaussian")
    {
        return new ImageGaussianBlur(config);
    }

    return NULL;
}

void ImageGaussianBlur::evaluate(ReturnData *out)
{
    if(out->getTypeNum() != ReturnImage::TYPENUM)
    {
        throw string("ImageGaussianBlur::evaluate, incorrect ReturnData type");
    }
    if (getArgNReturnType(0) != getArgN(0)->getReturnType())
    {
        throw string("ImageGaussianBlur::evaluate Error argument 0 has incorrect return type");
    }
    if (getArgNReturnType(1) != getArgN(1)->getReturnType())
    {
        throw string("ImageGaussianBlur::evaluate Error argument 1 has incorrect return type");
    }
    ReturnImage returnImage;
    ReturnDouble returnDouble1;

    getArgN(0)->evaluate(&returnImage);
    getArgN(1)->evaluate(&returnDouble1);

    //and now do some MAGIC!!

    int x = (int)(returnDouble1.getData()*100) % 100 * 2+ 1;
    cv::Mat result;
    cv::GaussianBlur(returnImage.getData(), result, cv::Size(x, x), 0, 0);


    dynamic_cast<ReturnImage *>(out)->setData(result);
}

Node* ImageGaussianBlur::copy()
{
    Function *tmp = new ImageGaussianBlur(config);
    if(tmp == NULL)
    {
        throw string(" ImageGaussianBlur::copy error, out of memory");
    }
    tmp->setArgN(0, getArgN(0)->copy());
    tmp->setArgN(1, getArgN(1)->copy());

    return dynamic_cast<Node *>(tmp);
}