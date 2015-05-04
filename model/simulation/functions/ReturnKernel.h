#ifndef _ReturnKernel_H_
#define _ReturnKernel_H_

#include "ReturnValue.h"
#include <opencv2/opencv.hpp>
using namespace cv;


class ReturnKernel : public ReturnValue<Mat, ReturnKernel>
{
public:
      ReturnKernel();
      virtual ~ReturnKernel();
	  static const int TYPENUM=TYPENUM_ReturnKernel;

};


#endif
