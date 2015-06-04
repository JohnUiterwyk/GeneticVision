//
// Created by John Uiterwyk on 5/30/15.
//

#ifndef GENETICVISION_STDOUTVIEW_H
#define GENETICVISION_STDOUTVIEW_H

#include "../AppConfig.h"
#include "../model/simulation/RunResult.h"

namespace GeneticVision
{
    class StdOutView {
    public:
        StdOutView(AppConfig * appConfig);;

        void update(RunResult *runResult);

        // getCurrentDateTime is adapted from StackOverflow answer posted by TrungTN:
        // http://stackoverflow.com/a/10467633
        const std::string getCurrentDateTime();

    };
}



#endif //GENETICVISION_STDOUTVIEW_H
