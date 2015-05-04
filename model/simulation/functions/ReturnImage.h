#ifndef _ReturnImage_H_
#define _ReturnImage_H_

#include "ReturnValue.h"
#include <opencv2/opencv.hpp>
using namespace cv;


class ReturnImage : public ReturnValue<Mat,ReturnImage>
{
public:
      ReturnImage();
      virtual ~ReturnImage();
	  static const int TYPENUM=TYPENUM_IMAGE;


};


#endif
