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
    std::string jsonConfigFilePath;
    if(argc==2)
    {
        jsonConfigFilePath.append(argv[1]);
        GeneticVisionApp app = GeneticVisionApp(&jsonConfigFilePath);
    }
    else
    {
        cerr << "Error: No config file specified" << endl;
        cerr << "Usage:" << endl;
        cerr << "GeneticVision path/to/config.json" << endl;

    }

    return 0;
}