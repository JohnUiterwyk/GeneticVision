//
// Created by John Uiterwyk on 5/28/15.
//

#ifndef GENETICVISION_GENETICVISIONCONFIG_H
#define GENETICVISION_GENETICVISIONCONFIG_H

#include <string>
#include <vector>
#include "model/ImagePair.h"
#include "util/json/json.h"
#include "model/simulation/ImagePairCollection.h"

using namespace std;
namespace GeneticVision
{
    class AppConfig
    {
    public:
        enum RunMode
        {
            EVOLVE,
            TEST,
            RUN
        };
    private:
        RunMode runMode;
        int generationsPerTick;
        int maxGenerations;

        int populationSize;
        double mutation;
        double crossover;
        double elitism;
        int minDepth;
        int maxDepth;
        double targetFitness;

        string runLogPath;

        int logFrequency;

        bool guiEnabled;

        string rootPath;
        string outputPath;
        string popFilesPath;
        string imagesOutputPath;

        ImagePairCollection trainPairs;
        ImagePairCollection testPairs;

        bool loadPopulationEnabled;
        string loadPopulationPath;

        bool saveResultImages;

    public:
        AppConfig();
        void parseCommandLineArgs(int argc, char **argv);
        void loadConfigFile(const string *filepath);
        void createMissingDirectories();
        void printToStdOut();


        /**
         *  getters and setters
         */
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
        ImagePairCollection & getTrainPairs()  {
            return this->trainPairs;
        }
        const string getRunLogPath() const {
            return runLogPath;
        }
        const string getRootPath() const {
            return rootPath;
        }
        const string getOutputPath() const {
            return outputPath;
        }
        const string getImagesOutputPath() const {
            return imagesOutputPath;
        }
        const string getPopFilesPath() const {
            return popFilesPath;
        }

        int getMaxGenerations() const {
            return maxGenerations;
        }

        int getGenerationsPerTick() const {
            return generationsPerTick;
        }
        bool isLoadPopulationEnabled() const {
            return loadPopulationEnabled;
        }
        bool isSaveResultImagesEnabled() const {
            return saveResultImages;
        }
        const string  getLoadPopulationPath()  {
            return loadPopulationPath;
        }

        double getTargetFitness() const {
            return targetFitness;
        }

        bool isGuiEnabled() const {
            return guiEnabled;
        }


    };

}




#endif //GENETICVISION_GENETICVISIONCONFIG_H
