//
// Created by John Uiterwyk on 28/03/15.
//

#include "opencv2/highgui/highgui.hpp"
#include "OpenCVWindow.h"
#include <string>

using namespace std;

OpenCVWindow::OpenCVWindow(const string& window_name, int width, int height) {
    this->width = width;
    this->height = height;
    this->window_name = window_name;
    namedWindow( window_name, WINDOW_NORMAL );
    resizeWindow(window_name,width,height);
}

OpenCVWindow::~OpenCVWindow() {

}

void OpenCVWindow::setPosition(int x, int y) {
    moveWindow(this->window_name,x,y);
}

void OpenCVWindow::showImage(_InputArray const &inputArray) {
    imshow(this->window_name,inputArray);
}
