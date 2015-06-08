//
// Created by John Uiterwyk on 5/19/15.
//

#ifndef GENETICVISION_RETURNIMAGE_H
#define GENETICVISION_RETURNIMAGE_H

#include "../../../rmitgp/ReturnData.h"
#include <opencv2/core/core.hpp>

class ReturnImage : public ReturnData {

private:
    cv::Mat data;

    /***********************************************
       This method sets the typeNum to be the typeid
       of the class.
    ************************************************/
    virtual void initTypeNum();

public:
    static const int TYPENUM;
    ReturnImage();
    virtual ~ReturnImage();

    /************************
     Set the data to be num
    ************************/
    void setData(cv::Mat image);

    /****************************
     Get the data of this class
    ****************************/
    cv::Mat & getData() ;
};


#endif //GENETICVISION_RETURNIMAGE_H
