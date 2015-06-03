//
// Created by John Uiterwyk on 5/26/15.
//

#ifndef GENETICVISION_IMAGESOBEL_H
#define GENETICVISION_IMAGESOBEL_H





class GPConfig;

#include <string>
#include "TFunction.h"
#include "../types/ReturnImage.h"

class ImageSobel : public TFunction<ImageSobel, ReturnImage>
{
private:

public:
    /*************
     Constructor.
    **************/
    ImageSobel(GPConfig *conf);

    /*********************
     virtual destructor
    *********************/
    virtual ~ImageSobel();

    static const string NAME;

protected:
    virtual void evaluate_impl(ReturnData *out);

};



#endif //GENETICVISION_IMAGESOBEL_H
