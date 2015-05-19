//
// Created by John Uiterwyk on 5/19/15.
//

#include <string>
#include <math.h>

using namespace std;

#include "ImageThreshold.h"
#include "../types/ReturnImage.h"
#include "../types/ReturnDouble.h"

ImageThreshold::ImageThreshold(GPConfig *config) :
        Function(ReturnImage::TYPENUM, 2, "cv_threshold", config)
{
    setArgNReturnType(0,ReturnImage::TYPENUM);
    setArgNReturnType(1,ReturnDouble::TYPENUM);
}

ImageThreshold::~ImageThreshold() { }

Function* ImageThreshold::generate(const string &name, GPConfig *config)
{
    if (name == "")
    {
        return new ImageThreshold(config);
    }
    else if (name == "cv_threshold")
    {
        return new ImageThreshold(config);
    }

    return NULL;
}

void ImageThreshold::evaluate(ReturnData *out)
{
    if(out->getTypeNum() != ReturnImage::TYPENUM)
    {
        throw string("ImageThreshold::evaluate, incorrect ReturnData type");
    }
    if (getArgNReturnType(0) != getArgN(0)->getReturnType())
    {
        throw string("ImageThreshold::evaluate Error argument 0 has incorrect return type");
    }
    if (getArgNReturnType(1) != getArgN(1)->getReturnType())
    {
        throw string("ImageThreshold::evaluate Error argument 1 has incorrect return type");
    }
    ReturnDouble returnDouble;
    ReturnImage returnImage;

    //and now do some MAGIC!!
    cv::Mat result = returnImage.getData()  > (int)(fmod(returnDouble.getData(),1) * 255);

    dynamic_cast<ReturnImage *>(out)->setData(result);
}

Node* ImageThreshold::copy()
{
    Function *tmp = new ImageThreshold(config);
    if(tmp == NULL)
    {
        throw string(" ImageThreshold::copy error, out of memory");
    }
    tmp->setArgN(0, getArgN(0)->copy());
    tmp->setArgN(1, getArgN(1)->copy());

    return dynamic_cast<Node *>(tmp);
}