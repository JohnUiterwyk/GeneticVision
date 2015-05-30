//
// Created by John Uiterwyk on 5/28/15.
//

#ifndef GENETICVISION_GENETICVISIONCONFIG_H
#define GENETICVISION_GENETICVISIONCONFIG_H

#include <string>
#include <vector>
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
        int logFrequency;
        string runLogPath;
        vector<vector<string> > imagePairPaths;
        string imageDirectoryPath;

    public:
        AppConfig():
            populationSize(100),
            mutation(0.28),
            crossover(0.70),
            elitism(0.02),
            minDepth(2),
            maxDepth(5),
            runLogPath("output/run_log.txt")
        {

        };
        void loadConfigFile(const string * filepath);
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
        vector<vector<string> > getImagePairPaths()  {
            return this->imagePairPaths;
        }
        const char * getRunLogPath() const {
            return runLogPath.c_str();
        }
        const char * getImageDirectoryPath() const {
            return imageDirectoryPath.c_str();
        }

    };

}




#endif //GENETICVISION_GENETICVISIONCONFIG_H
