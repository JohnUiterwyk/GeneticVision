//
// Created by John Uiterwyk on 12/18/15.
//

#include "CvMatrixDivideScalar.h"
//
// Created by John Uiterwyk on 12/18/15.
//


#include "CvMatrixDivideScalar.h"
#include "../types/ReturnImage.h"
#include "../types/ReturnDouble.h"


const string CvMatrixDivideScalar::NAME = "cv_matrix_divide_scalar";

CvMatrixDivideScalar::CvMatrixDivideScalar(GPConfig *conf) : TFunction<CvMatrixDivideScalar, ReturnImage>(conf, 2)
{
    setArgNReturnType(0, ReturnImage::TYPENUM);
    setArgNReturnType(1, ReturnDouble::TYPENUM);
}

CvMatrixDivideScalar::~CvMatrixDivideScalar()
{
}


void CvMatrixDivideScalar::evaluate_impl(ReturnData *out)
{
    ReturnImage arg1;
    ReturnDouble arg2;
    getArgN(0)->evaluate(&arg1);
    getArgN(1)->evaluate(&arg2);
    cv::Mat src = arg1.getData();
    double scalar = arg2.getData();
    cv::Mat result;
    result = src / scalar;



    //and now do some MAGIC!!
//    int threshold = (int)(fmod(returnDouble.getData(),1) * 255);
//    cv::Mat result = returnImage.getData() > threshold;

    dynamic_cast<ReturnImage *>(out)->setData(result);
}