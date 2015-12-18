//
// Created by John Uiterwyk on 12/18/15.
//

#include "CvMatrixAdd.h"
#include "../types/ReturnImage.h"
#include "../types/ReturnDouble.h"


const string CvMatrixAdd::NAME = "cv_matrix_add";

CvMatrixAdd::CvMatrixAdd(GPConfig *conf) : TFunction<CvMatrixAdd, ReturnImage>(conf, 2)
{
    setArgNReturnType(0, ReturnImage::TYPENUM);
    setArgNReturnType(1, ReturnImage::TYPENUM);
}

CvMatrixAdd::~CvMatrixAdd()
{
}


void CvMatrixAdd::evaluate_impl(ReturnData *out)
{
    ReturnImage arg1;
    ReturnImage arg2;
    getArgN(0)->evaluate(&arg1);
    getArgN(1)->evaluate(&arg2);
    cv::Mat src1 = arg1.getData();
    cv::Mat src2 = arg2.getData();
    cv::Mat result;
    result = src1 + src2;



    //and now do some MAGIC!!
//    int threshold = (int)(fmod(returnDouble.getData(),1) * 255);
//    cv::Mat result = returnImage.getData() > threshold;

    dynamic_cast<ReturnImage *>(out)->setData(result);
}