//
// Created by John Uiterwyk on 12/04/15.
//

#ifndef OPENCV_POC_STOPWATCH_H
#define OPENCV_POC_STOPWATCH_H


#include <ctime>
#include <sstream>
#include <string>
#include <sys/time.h>

class Stopwatch
{
public:
    explicit Stopwatch(bool start_now = false);
    void Start(bool reset = false);
    void Stop();
    long double GetTotalWallTime() const;
    long double GetTotalCPUTime() const;
    double GetCPUTime() const;
    double GetWallTime() const;

private:
    double cpu_start_time;
    double cpu_stop_time;
    double wall_start_time;
    double wall_stop_time;
    bool running;
    long double cpu_elapsed_time;
    long double wall_elapsed_time;
};


#endif //OPENCV_POC_STOPWATCH_H
