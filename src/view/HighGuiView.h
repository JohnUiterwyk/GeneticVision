//
// Created by John Uiterwyk on 5/30/15.
//

#ifndef GENETICVISION_HIGHGUI_H
#define GENETICVISION_HIGHGUI_H


#ifdef CV_HIGHGUI_ENABLED
    #include "OpenCVWindow.h"
#endif //CV_HIGHGUI_ENABLED


#include "../model/simulation/RunResult.h"
#include "../AppConfig.h"

namespace GeneticVision {
    class HighGuiView {
    public:

        #ifdef CV_HIGHGUI_ENABLED
            OpenCVWindow results;
            OpenCVWindow performance;
        #endif //CV_HIGHGUI_ENABLED

        HighGuiView(GeneticVision::AppConfig * appConfig);

        void update(RunResult *runResult);

    };
}


#endif //GENETICVISION_VIEWCONTROLLER_H
