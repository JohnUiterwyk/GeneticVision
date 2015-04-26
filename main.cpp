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
    std::string imageSetFilePath;
    int guiEnabled = 0;
    for(int i=1;i<argc;i++)
    {
        if(strcmp(argv[i],"-gui") == 0)
        {
            guiEnabled = 1;
        } else
        {
            imageSetFilePath.append(argv[i]);
        }
    }

    GeneticVisionApp app = GeneticVisionApp(imageSetFilePath, guiEnabled);
    return 0;
}