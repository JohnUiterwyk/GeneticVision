//
// Created by John Uiterwyk on 5/25/15.
//

#ifndef GENETICVISION_IMAGECANNYEDGE_H
#define GENETICVISION_IMAGECANNYEDGE_H

class GPConfig;

#include <string>
#include "TFunction.h"
#include "../types/ReturnImage.h"

class ImageCannyEdge : public TFunction<ImageCannyEdge, ReturnImage>
{
private:

public:
    /*************
     Constructor.
    **************/
    ImageCannyEdge(GPConfig *conf);

    /*********************
     virtual destructor
    *********************/
    virtual ~ImageCannyEdge();

    static const string NAME;

protected:
    virtual void evaluate_impl(ReturnData *out);

};


#endif //GENETICVISION_IMAGECANNYEDGE_H
