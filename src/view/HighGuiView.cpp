//
// Created by John Uiterwyk on 5/30/15.
//


#include "HighGuiView.h"
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
            output.showImages(runResult->bestResultImages);
        #endif //CV_HIGHGUI_ENABLED
    }
}



