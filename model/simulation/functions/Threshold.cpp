
#include <string>

using namespace std;

#include "Threshold.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ReturnDouble.h"


const string Threshold::NAME = "th";

Threshold::Threshold(GPConfig *conf) : TFunction(conf, 2)
{
    setArgNReturnType(0, ReturnImage::TYPENUM);
    setArgNReturnType(1, ReturnDouble::TYPENUM);
}

Threshold::~Threshold()
{
}


void Threshold::evaluate_impl(ReturnData *out)
{

   ReturnImage src;
   ReturnDouble thresh;

   getArgN(0)->evaluate(&src);
   getArgN(1)->evaluate(&thresh);

   Mat result;

   cv::threshold(src.getData(), result, thresh.getData(), 1, THRESH_BINARY);

   dynamic_cast<ReturnImage *>(out)->setData(result);
}



