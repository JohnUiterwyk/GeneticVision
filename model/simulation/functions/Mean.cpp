
#include <string>

using namespace std;

#include "Mean.h"
#include "../types/ReturnImage.h"


const string Mean::NAME = "cv_mean";

Mean::Mean(GPConfig *conf) : TFunction(conf, 1)
{
      setArgNReturnType(0, ReturnImage::TYPENUM);
}

Mean::~Mean()
{
}


void Mean::evaluate_impl(ReturnData *out)
{

   ReturnImage src;

   getArgN(0)->evaluate(&src);

   cv::Scalar result;

   result=cv::mean(src.getData());


   dynamic_cast<ReturnDouble *>(out)->setData(result.val[0]);
}



