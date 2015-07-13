//
// Created by John Uiterwyk on 5/30/15.
//


#include "HighGuiView.h"
#include <map>
#include "../model/simulation/RunResult.h"
namespace GeneticVision
{
    HighGuiView::HighGuiView(AppConfig *appConfig)
    #ifdef CV_HIGHGUI_ENABLED
        :results("results",100,100)
    #endif //CV_HIGHGUI_ENABLED
    {

    }

    void HighGuiView::update(RunResult *runResult)
    {
        #ifdef CV_HIGHGUI_ENABLED
        vector<cv::Mat> resultVector;
        if(runResult->performanceImagesMap.size() > 0) {
            for ( std::map<string,cv::Mat>::iterator it2=runResult->performanceImagesMap.begin() ; it2 != runResult->performanceImagesMap.end(); ++it2 )
            {
                resultVector.push_back(it2->second);
            }
        }
        else
        {
            for (std::map<string, cv::Mat>::iterator it = runResult->resultImagesMap.begin();
                 it != runResult->resultImagesMap.end(); ++it) {
                resultVector.push_back(it->second);
            }

        }
        if(resultVector.size() > 0)results.showImages(resultVector);


        //some issue with grid viewer
        #endif //CV_HIGHGUI_ENABLED
    }
}



