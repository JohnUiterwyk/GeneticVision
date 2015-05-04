/*
 * ImageGreyscale.h
 *
 *      Author: john
 */

#ifndef IMAGEBRIGHTNESS_H_
#define IMAGEBRIGHTNESS_H_

#include "opencv2/opencv.hpp"
#include "TTerminal.h"
#include "ReturnImage.h"

class ImageBrightness : public TTerminal<cv::Mat, ReturnImage, ImageBrightness> {
public:
	ImageBrightness(GPConfig *conf);
	virtual ~ImageBrightness();
	virtual void evaluate(ReturnData *out);


    static const string NAME;
};

#endif /* IMAGEBRIGHTNESS_H_ */
