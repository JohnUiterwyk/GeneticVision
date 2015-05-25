
#include <string>

using namespace std;

#include "StdDev.h"
#include "../types/ReturnImage.h"


const string StdDev::NAME = "cv_stddev";

StdDev::StdDev(GPConfig *conf) : TFunction(conf, 1)
{
      setArgNReturnType(0, ReturnImage::TYPENUM);
}

StdDev::~StdDev()
{
}


void StdDev::evaluate_impl(ReturnData *out)
{

   ReturnImage src;

   getArgN(0)->evaluate(&src);

   cv::Scalar mean;
   cv::Scalar stdev;

   cv::meanStdDev(src.getData(), mean, stdev);


   dynamic_cast<ReturnDouble *>(out)->setData(stdev.val[0]);
}



