//
// Created by John Uiterwyk on 12/04/15.
//

#include "Stopwatch.h"

Stopwatch::Stopwatch(bool start_now)
        : cpu_start_time(0),
          cpu_stop_time(0),
          cpu_elapsed_time(0),
          wall_start_time(0),
          wall_stop_time(0),
          wall_elapsed_time(0),
          running(false)
{
    if (start_now)
    {
        Start(true);
    }
}
void Stopwatch::Start(bool reset)
{
    if (!running)
    {
        if (reset) {
            cpu_elapsed_time = 0;
            wall_elapsed_time = 0;
        }
        cpu_start_time = this->GetCPUTime();
        wall_start_time = this->GetWallTime();
        running = true;
    }
}
void Stopwatch::Stop()
{
    if (running)
    {
        cpu_stop_time = this->GetCPUTime();
        wall_stop_time = this->GetWallTime();
        cpu_elapsed_time += (long double)(cpu_stop_time - cpu_start_time);
        wall_elapsed_time += (long double)(wall_stop_time - wall_start_time);
        running = false;
    }
}
long double Stopwatch::GetTotalCPUTime() const
{
    if(running)
    {
        return  cpu_elapsed_time + this->GetCPUTime()- cpu_start_time;

    } else
    {
        return cpu_elapsed_time ;
    }
}

long double Stopwatch::GetTotalWallTime() const
{
    if(running)
    {
        return  wall_elapsed_time + this->GetWallTime() - wall_start_time;

    } else
    {
        return wall_elapsed_time ;
    }
}


double Stopwatch::GetCPUTime() const
{
    return (double)clock() / CLOCKS_PER_SEC;
}
double Stopwatch::GetWallTime() const
{
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}