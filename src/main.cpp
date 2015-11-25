//
// Created by John Uiterwyk on 6/4/15.
//

#include <iostream>
#include <thread>
#include "GeneticVisionApp.h"

using namespace std;
using namespace GeneticVision;
int main( int argc, char** argv )
{
    //timer code:
//    double readTime = (double)getTickCount();
//    readTime = ((double)getTickCount() - readTime)/getTickFrequency();


    std::cout << endl;
    std::cout << "################################################" << endl;
    std::cout << "#                GENENTIC VISION               #" << endl;
    std::cout << "################################################" << endl;
    std::cout << endl;

    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";

    /// check for some arguments
    if(argc == 1)
    {
        cerr << "Error: No config file or options specified" << endl;
    }
    else
    {
        GeneticVisionApp app(argc, argv);
    }

    return 0;
}