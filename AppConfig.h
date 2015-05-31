//
// Created by John Uiterwyk on 5/28/15.
//

#ifndef GENETICVISION_GENETICVISIONCONFIG_H
#define GENETICVISION_GENETICVISIONCONFIG_H

#include <string>
#include <vector>
#include "model/ImagePair.h"

using namespace std;
namespace GeneticVision
{
    class AppConfig
    {

    private:
        int populationSize;
        double mutation;
        double crossover;
        double elitism;
        int minDepth;
        int maxDepth;
        string runLogPath;
        int logFrequency;
        bool guiEnabled;
        vector<ImagePair > imagePairs;

        string workingDirectory;

    public:
        AppConfig()
        {

        };
        void loadConfigFile(const string *filepath);
        int getPopulationSize() const {
            return populationSize;
        }
        double getMutation() const {
            return mutation;
        }

        double getCrossover() const {
            return crossover;
        }

        double getElitism() const {
            return elitism;
        }

        int getMinDepth() const {
            return minDepth;
        }

        int getMaxDepth() const {
            return maxDepth;
        }

        int getLogFrequency() const {
            return logFrequency;
        }
        vector<ImagePair > * getImagePairs()  {
            return &this->imagePairs;
        }
        const char * getRunLogPath() const {
            return runLogPath.c_str();
        }
        const char * getWorkingDirectory() const {
            return workingDirectory.c_str();
        }

    };

}




#endif //GENETICVISION_GENETICVISIONCONFIG_H
