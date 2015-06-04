//
// Created by John Uiterwyk on 5/30/15.
//

#include <iostream>
#include "StdOutView.h"
namespace GeneticVision
{

    StdOutView::StdOutView(AppConfig *appConfig)
    {

    }

    void StdOutView::update(RunResult *runResult)
    {
        std::ostringstream result;

        //Print date and time
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        result << "DateTime, " << this->getCurrentDateTime() << endl;
        result << "GenerationID, " << runResult->generationId << endl;
        result << "Best Fitness, " << runResult->bestProgramFitness << endl;
        result << "Program String, " << runResult->bestProgramString << endl;
        result << endl;

        cout << result.str();
    }

    const std::string StdOutView::getCurrentDateTime() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
        // for more information about date/time format
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

        return buf;
    }
}