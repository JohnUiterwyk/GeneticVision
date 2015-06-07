//
// Created by John Uiterwyk on 5/28/15.
//

#ifndef GENETICVISION_GENETICVISIONCONFIG_H
#define GENETICVISION_GENETICVISIONCONFIG_H

#include <string>
#include <vector>
#include "model/ImagePair.h"
#include "util/json/json.h"

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
        vector<ImagePair > trainingImagePairs;
        vector<ImagePair > testImagePairs;
        string rootPath;
        string outputPath;
        string popFilesPath;
        string imagesOutputPath;
        int maxGenerations;
        int generationsPerTick;
        bool showImagesInHighGuiWindow;
        bool loadPopulationEnabled;
        string loadPopulationPath;
    public:
        AppConfig()
        {

        };
        void loadConfigFile(const string *filepath);
        vector<ImagePair> loadImages(const Json::Value &images);
        bool isValidImageType(string & filename);
        bool isMaskImage(string & filename);
        string getImagKey(string & filename);


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
        vector<ImagePair > * getTrainingImagePairs()  {
            return &this->trainingImagePairs;
        }
        vector<ImagePair > * getTestImagePairs()  {
            return &this->testImagePairs;
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
            return outputPath;
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
        const string  getLoadPopulationPath()  {
            return loadPopulationPath;
        }



    };

}




#endif //GENETICVISION_GENETICVISIONCONFIG_H
