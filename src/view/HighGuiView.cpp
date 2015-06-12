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
        :output("output",100,100)
    #endif //CV_HIGHGUI_ENABLED
    {

    }

    void HighGuiView::update(RunResult *runResult)
    {
        #ifdef CV_HIGHGUI_ENABLED
            vector<cv::Mat> resultVector;
            for ( std::map<string,cv::Mat>::iterator it=runResult->resultMap.begin() ; it != runResult->resultMap.end(); ++it )
            {
                resultVector.push_back(it->second);

            }
            output.showImages(resultVector);
        #endif //CV_HIGHGUI_ENABLED
    }
}



