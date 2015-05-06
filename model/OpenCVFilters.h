//
// Created by John Uiterwyk on 20/04/15.
//

#ifndef OPENCV_POC_OPENCVFILTERS_H
#define OPENCV_POC_OPENCVFILTERS_H

#include "opencv2/imgproc/imgproc.hpp"
#include "Stopwatch.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <sstream>

using namespace std;

class OpenCVFilters {
public:
    explicit OpenCVFilters();
    cv::Mat Gaussian(cv::Mat input, int x,int y);
    cv::Mat Sobel(cv::Mat input, int x,int y);
    cv::Mat Threshold(cv::Mat input, int x,int y);
    cv::Mat Bilateral(cv::Mat input, int x,int y);
    cv::Mat Erosion(cv::Mat input, int x,int y);
    cv::Mat Laplacian(cv::Mat input, int x,int y);
    double GetFitnessScore(cv::Mat input, cv::Mat truth);
    cv::Mat working;

private:
    enum class FilterName {GAUSSIAN = 0, SOBEL=1};
};


#endif //OPENCV_POC_OPENCVFILTERS_H
