//
// Created by John Uiterwyk on 5/19/15.
//

#include "ImageInput.h"
#include "../types/ReturnImage.h"

cv::Mat ImageInput::value;

ImageInput::ImageInput(GPConfig *config) : Terminal(ReturnImage::TYPENUM, "input_image", config)
{

}

ImageInput::~ImageInput() { }

Terminal* ImageInput::generate(const string &name, GPConfig *config)
{
    if(name == "" || name == "input_image")
    {
        return new ImageInput(config);
    }
    return NULL;
}

void ImageInput::evaluate(ReturnData *out)
{
    if(out->getTypeNum() != (ReturnImage::TYPENUM))
    {
        throw string("ImageInput::evaluate, incorrect ReturnData type");
    }
    dynamic_cast<ReturnImage *>(out)->setData(value);
}

Node* ImageInput::copy()
{
    Node *tmp = new ImageInput(config);

    if(tmp == NULL)
    {
        throw string("ImageInput::copy error, out of memory");
    }
    return tmp;
}

void ImageInput::setValue(cv::Mat v)
{
    value = v;
}