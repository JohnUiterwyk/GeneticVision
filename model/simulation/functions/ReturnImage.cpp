
#include "ReturnImage.h"

//Initialise static data

ReturnImage::ReturnImage()
{
	data = Mat::zeros(1, 1, CV_32F);
}

ReturnImage::~ReturnImage()
{
}

