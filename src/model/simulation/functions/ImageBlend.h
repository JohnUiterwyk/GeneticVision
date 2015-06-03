//
// Created by John Uiterwyk on 5/25/15.
//

#ifndef GENETICVISION_IMAGEBLEND_H
#define GENETICVISION_IMAGEBLEND_H

class GPConfig;

#include <string>
#include "TFunction.h"
#include "../types/ReturnImage.h"

class ImageBlend : public TFunction<ImageBlend, ReturnImage>
{
private:

public:
    /*************
     Constructor.
    **************/
    ImageBlend(GPConfig *conf);

    /*********************
     virtual destructor
    *********************/
    virtual ~ImageBlend();

    static const string NAME;

protected:
    virtual void evaluate_impl(ReturnData *out);

};

#endif //GENETICVISION_IMAGEBLEND_H
