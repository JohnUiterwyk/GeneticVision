//
// Created by John Uiterwyk on 5/30/15.
//

#include <iostream>
#include "StdOutView.h"
namespace GeneticVision
{

    StdOutView::StdOutView(AppConfig *appConfig)
    {
        this->appConfig = appConfig;
    }

    void StdOutView::update(RunResult *runResult)
    {

        //Print date and time
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        cout << "################################################" << endl;
        cout << "Timestamp: " << this->getCurrentDateTime() << endl;
        cout << "GenerationID: " << runResult->generationId << endl;
        cout << "################################################" << endl;
        cout << "Best Program Details" << endl;
        cout << "Fitness: " << runResult->bestProgram->getFitness() << endl;

        string bestProgramString;
        runResult->bestProgram->print(bestProgramString);
        cout << "Program String: " << bestProgramString << endl;
        if(this->appConfig->isTestEnabled())
        {
            cout << runResult->statAverage.toString();
        }
        cout << "################################################" << endl;
        cout << endl;

    }

    const std::string StdOutView::getCurrentDateTime() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
        // for more information about date/time format
        strftime(buf, sizeof(buf), "%Y-%m-%d-%I-%M-%S", &tstruct);

        return buf;
    }
}