//
// Created by John Uiterwyk on 5/26/15.
//

#ifndef GENETICVISION_IMAGEERODE_H
#define GENETICVISION_IMAGEERODE_H



class GPConfig;

#include <string>
#include "TFunction.h"
#include "../types/ReturnImage.h"

class ImageErode : public TFunction<ImageErode, ReturnImage>
{
private:

public:
    /*************
     Constructor.
    **************/
    ImageErode(GPConfig *conf);

    /*********************
     virtual destructor
    *********************/
    virtual ~ImageErode();

    static const string NAME;

protected:
    virtual void evaluate_impl(ReturnData *out);

};


#endif //GENETICVISION_IMAGEERODE_H
