//
// Created by John Uiterwyk on 5/26/15.
//

#ifndef GENETICVISION_IMAGEINVERT_H
#define GENETICVISION_IMAGEINVERT_H


class GPConfig;

#include <string>
#include "TFunction.h"
#include "../types/ReturnImage.h"

class ImageInvert : public TFunction<ImageInvert, ReturnImage>
{
private:

public:
    /*************
     Constructor.
    **************/
    ImageInvert(GPConfig *conf);

    /*********************
     virtual destructor
    *********************/
    virtual ~ImageInvert();

    static const string NAME;

protected:
    virtual void evaluate_impl(ReturnData *out);

};




#endif //GENETICVISION_IMAGEINVERT_H
