//
// Created by John Uiterwyk on 28/03/15.
//

#ifdef CV_HIGHGUI_ENABLED
#ifndef _OPENCV_POC_OPENCVWINDOW_H_
#define _OPENCV_POC_OPENCVWINDOW_H_

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <vector>


using namespace std;
using namespace cv;

class OpenCVWindow {
    string window_name;

public:
    int width, height, x, y;
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
     Set the position of the window
    *********************/

    void setSize(int , int);

    /*********************
     Show an image in the window
    *********************/
    void showImage(InputArray);

    /************************
     * Make a canvas
     */
    cv::Mat makeCanvas(std::vector<cv::Mat>& , int , int );

    void showImages(std::vector<cv::Mat>& );
};


#endif //_OPENCV_POC_OPENCVWINDOW_H_
#endif // CV_HIGHGUI_ENABLED
