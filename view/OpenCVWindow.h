//
// Created by John Uiterwyk on 28/03/15.
//

#ifndef _OPENCV_POC_OPENCVWINDOW_H_
#define _OPENCV_POC_OPENCVWINDOW_H_

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui_c.h"


using namespace std;
using namespace cv;

class OpenCVWindow {
    int width, height, x, y;
    string window_name;

public:
    /*************
     Constructor.
    **************/
    OpenCVWindow(const string& window_name, int width, int height);

    /*********************
     virtual destructor
    *********************/
    virtual ~OpenCVWindow();

    /*********************
     Set the position of the window
    *********************/
    void setPosition (int,int);

    /*********************
     Show an image in the window
    *********************/
    void showImage(InputArray);
};


#endif //_OPENCV_POC_OPENCVWINDOW_H_
