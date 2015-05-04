//
// Created by John Uiterwyk on 28/03/15.
//

#include "opencv2/highgui/highgui.hpp"
#include "OpenCVWindow.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

OpenCVWindow::OpenCVWindow(const string& window_name, int width, int height) {
    this->width = width;
    this->height = height;
    this->window_name = window_name;
    namedWindow( window_name, WINDOW_NORMAL );
}

OpenCVWindow::~OpenCVWindow() {

}

void OpenCVWindow::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
    moveWindow(this->window_name,x,y);
}
void OpenCVWindow::setSize(int width, int height) {
    this->width = width;
    this->height = height+20;
    resizeWindow(this->window_name,width,this->height );
}

void OpenCVWindow::showImage(_InputArray const &inputArray) {
    imshow(this->window_name,inputArray);
}

void OpenCVWindow::showImages(std::vector<Mat> & imageVector) {

    cv::Mat buffer = this->makeCanvas(imageVector,300,3);
    imshow(this->window_name,buffer);
    cv::Size size = buffer.size();
    this->setSize(size.width,size.height);

}


cv::Mat OpenCVWindow::makeCanvas(std::vector<cv::Mat>& vecMat, int windowHeight, int nRows) {
    int N = vecMat.size();
    nRows  = nRows > N ? N : nRows;
    int edgeThickness = 10;
    int imagesPerRow = (int) ceil(double(N) / nRows);
    int resizeHeight = (int) floor(2.0 * ((floor(double(windowHeight - edgeThickness) / nRows)) / 2.0)) - edgeThickness;
    int maxRowLength = 0;

    std::vector<int> resizeWidth;
    for (int i = 0; i < N;) {
        int thisRowLen = 0;
        for (int k = 0; k < imagesPerRow; k++) {
            double aspectRatio = double(vecMat[i].cols) / vecMat[i].rows;
            int temp = int( ceil(resizeHeight * aspectRatio));
            resizeWidth.push_back(temp);
            thisRowLen += temp;
            if (++i == N) break;
        }
        if ((thisRowLen + edgeThickness * (imagesPerRow + 1)) > maxRowLength) {
            maxRowLength = thisRowLen + edgeThickness * (imagesPerRow + 1);
        }
    }
    int windowWidth = maxRowLength;
    cv::Mat canvasImage(windowHeight, windowWidth, CV_8UC3, Scalar(0, 0, 0));

    for (int k = 0, i = 0; i < nRows; i++) {
        int y = i * resizeHeight + (i + 1) * edgeThickness;
        int x_end = edgeThickness;
        for (int j = 0; j < imagesPerRow && k < N; k++, j++) {
            int x = x_end;
            cv::Rect roi(x, y, resizeWidth[k], resizeHeight);
            cv::Size s = canvasImage(roi).size();
            // change the number of channels to three
            cv::Mat target_ROI(s, CV_8UC3);
            if (vecMat[k].channels() != canvasImage.channels()) {
                if (vecMat[k].channels() == 1) {
                    cv::cvtColor(vecMat[k], target_ROI, CV_GRAY2BGR);
                }
            }
            cv::resize(target_ROI, target_ROI, s);
            if (target_ROI.type() != canvasImage.type()) {
                target_ROI.convertTo(target_ROI, canvasImage.type());
            }
            target_ROI.copyTo(canvasImage(roi));
            x_end += resizeWidth[k] + edgeThickness;
        }
    }
    return canvasImage;
}
