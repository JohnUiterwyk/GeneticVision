//
// Created by John Uiterwyk on 6/4/15.
//

#ifndef GENETICVISION_VIEWCONTROLLER_H
#define GENETICVISION_VIEWCONTROLLER_H


#include "../model/simulation/RunResult.h"
#include "../AppConfig.h"
#include "HighGuiView.h"
#include "StdOutView.h"
#include "ImageWriter.h"

namespace GeneticVision {
    class ViewController {

    public:

        HighGuiView highGuiView;
        StdOutView stdOutView;
        ImageWriter imageWriter;
        ViewController(AppConfig * appConfig);;

        void update(RunResult *runResult);
    protected:
    private:
    };
}


#endif //GENETICVISION_VIEWCONTROLLER_H
