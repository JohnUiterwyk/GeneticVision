#include <iostream>
#include "GeneticVisionApp.h"

using namespace std;
using namespace GeneticVision;
int main( int argc, char** argv )
{
    //timer code:
//    double readTime = (double)getTickCount();
//    readTime = ((double)getTickCount() - readTime)/getTickFrequency();

    /// Load the source image
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