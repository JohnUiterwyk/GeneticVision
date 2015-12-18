//
// Created by John Uiterwyk on 12/18/15.
//

#ifndef GENETICVISION_CVMATRIXSUBTRACT_H
#define GENETICVISION_CVMATRIXSUBTRACT_H

#include <string>
#include "TFunction.h"
#include "../types/ReturnImage.h"

class CvMatrixSubtract : public TFunction<CvMatrixSubtract, ReturnImage>
{
private:

public:
    /*************
     Constructor.
    **************/
    CvMatrixSubtract(GPConfig *conf);

    /*********************
     virtual destructor
    *********************/
    virtual ~CvMatrixSubtract();

    static const string NAME;

protected:
    virtual void evaluate_impl(ReturnData *out);

};

#endif //GENETICVISION_CVMATRIXSUBTRACT_H
