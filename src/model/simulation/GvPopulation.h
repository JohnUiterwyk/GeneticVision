//
// Created by John Uiterwyk on 6/4/15.
//

#ifndef GENETICVISION_GVPOPULATION_H
#define GENETICVISION_GVPOPULATION_H


#include "../../rmitgp/Population.h"
namespace GeneticVision
{
    class GvPopulation: public Population{

    public:
         string outputDir;

        GvPopulation(Population &p)
                : Population(p)
        { }

        GvPopulation(int size, int initSize, const string outputDir, const char *logFileName, GPConfig *conf)
                : Population(size, initSize, logFileName, conf) {
            this->outputDir = outputDir;
        }

        virtual ~GvPopulation();

        GvPopulation(int size, const string outputDir, const char *logFileName, GPConfig *conf)
                : Population(size, logFileName, conf)
        {
            this->outputDir = outputDir;

        }
        void writeToFile() ;
        int getMinDepth()
        {
         return this->minDepth;
        }
        int getDepthLimit()
        {
            return this->depthLimit;
        }
    };

}


#endif //GENETICVISION_GVPOPULATION_H
