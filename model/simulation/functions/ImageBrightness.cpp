/*
 * ImageBrightness.cpp
 *
 *  Created on: 18/08/2013
 *      Author: james
 */

#include "ImageBrightness.h"

const string ImageBrightness::NAME = "L";

ImageBrightness::ImageBrightness(GPConfig *conf) : TTerminal(conf) {
	// TODO Auto-generated constructor stub

}

ImageBrightness::~ImageBrightness() {
	// TODO Auto-generated destructor stub
}

void ImageBrightness::evaluate(ReturnData *out)
{
	TTerminal<cv::Mat, ReturnImage, ImageBrightness>::evaluate(out);

	//CVDebug::logImage("ImageBrightness", this->value);

}
