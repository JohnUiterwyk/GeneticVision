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

        //Print date and time
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        cout << "DateTime, " << this->getCurrentDateTime() << endl;
        cout << "GenerationID, " << runResult->generationId << endl;
        cout << "Best Fitness, " << runResult->best->getFitness() << endl;

        string bestProgramString;
        runResult->best->print(bestProgramString);
        cout << "Program String, " << bestProgramString << endl;
        cout << endl;

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