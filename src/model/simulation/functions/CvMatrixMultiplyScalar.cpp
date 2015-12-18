//
// Created by John Uiterwyk on 12/18/15.
//

#include "CvMatrixMultiplyScalar.h"
//
// Created by John Uiterwyk on 12/18/15.
//

#include "CvMatrixMultiplyScalar.h"
#include "../types/ReturnImage.h"
#include "../types/ReturnDouble.h"


const string CvMatrixMultiplyScalar::NAME = "cv_matrix_multiply_scalar";

CvMatrixMultiplyScalar::CvMatrixMultiplyScalar(GPConfig *conf) : TFunction<CvMatrixMultiplyScalar, ReturnImage>(conf, 2)
{
    setArgNReturnType(0, ReturnImage::TYPENUM);
    setArgNReturnType(1, ReturnDouble::TYPENUM);
}

CvMatrixMultiplyScalar::~CvMatrixMultiplyScalar()
{
}


void CvMatrixMultiplyScalar::evaluate_impl(ReturnData *out)
{
    ReturnImage arg1;
    ReturnDouble arg2;
    getArgN(0)->evaluate(&arg1);
    getArgN(1)->evaluate(&arg2);
    cv::Mat src = arg1.getData();
    double scalar = arg2.getData();
    cv::Mat result;
    result = src * scalar;



    //and now do some MAGIC!!
//    int threshold = (int)(fmod(returnDouble.getData(),1) * 255);
//    cv::Mat result = returnImage.getData() > threshold;

    dynamic_cast<ReturnImage *>(out)->setData(result);
}