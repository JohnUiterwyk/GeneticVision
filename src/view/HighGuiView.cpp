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
        :results("results",100,100),
        performance("performance",100,100)
    #endif //CV_HIGHGUI_ENABLED
    {

    }

    void HighGuiView::update(RunResult *runResult)
    {
        #ifdef CV_HIGHGUI_ENABLED
            vector<cv::Mat> resultVector;
            for ( std::map<string,cv::Mat>::iterator it=runResult->resultImagesMap.begin() ; it != runResult->resultImagesMap.end(); ++it )
            {
                resultVector.push_back(it->second);

            }
             results.showImages(resultVector);


            vector<cv::Mat> perfVector;
            for ( std::map<string,cv::Mat>::iterator it2=runResult->performanceImagesMap.begin() ; it2 != runResult->performanceImagesMap.end(); ++it2 )
            {
                perfVector.push_back(it2->second);

            }
            //performance.showImages(perfVector);
        //some issue with grid viewer
        #endif //CV_HIGHGUI_ENABLED
    }
}



