//
// Created by John Uiterwyk on 12/18/15.
//

#ifndef GENETICVISION_CVMATRIXADD_H
#define GENETICVISION_CVMATRIXADD_H

#include <string>
#include "TFunction.h"
#include "../types/ReturnImage.h"

class CvMatrixAdd : public TFunction<CvMatrixAdd, ReturnImage>
{
private:

public:
    /*************
     Constructor.
    **************/
    CvMatrixAdd(GPConfig *conf);

    /*********************
     virtual destructor
    *********************/
    virtual ~CvMatrixAdd();

    static const string NAME;

protected:
    virtual void evaluate_impl(ReturnData *out);

};

#endif //GENETICVISION_CVMATRIXADD_H
