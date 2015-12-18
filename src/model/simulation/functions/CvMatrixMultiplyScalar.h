//
// Created by John Uiterwyk on 12/18/15.
//

#ifndef GENETICVISION_CVMATRIXMULTIPLYSCALAR_H
#define GENETICVISION_CVMATRIXMULTIPLYSCALAR_H

#include <string>
#include "TFunction.h"
#include "../types/ReturnImage.h"

class CvMatrixMultiplyScalar : public TFunction<CvMatrixMultiplyScalar, ReturnImage>
{
private:

public:
    /*************
     Constructor.
    **************/
    CvMatrixMultiplyScalar(GPConfig *conf);

    /*********************
     virtual destructor
    *********************/
    virtual ~CvMatrixMultiplyScalar();

    static const string NAME;

protected:
    virtual void evaluate_impl(ReturnData *out);

};

#endif //GENETICVISION_CVMATRIXMULTIPLYSCALAR_H
