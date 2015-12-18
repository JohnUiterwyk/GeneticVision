//
// Created by John Uiterwyk on 12/18/15.
//

#ifndef GENETICVISION_CVMATRIXDIVIDESCALAR_H
#define GENETICVISION_CVMATRIXDIVIDESCALAR_H




#include <string>
#include "TFunction.h"
#include "../types/ReturnImage.h"

class CvMatrixDivideScalar : public TFunction<CvMatrixDivideScalar, ReturnImage>
{
private:

public:
    /*************
     Constructor.
    **************/
    CvMatrixDivideScalar(GPConfig *conf);

    /*********************
     virtual destructor
    *********************/
    virtual ~CvMatrixDivideScalar();

    static const string NAME;

protected:
    virtual void evaluate_impl(ReturnData *out);

};

#endif //GENETICVISION_CVMATRIXDIVIDESCALAR_H
