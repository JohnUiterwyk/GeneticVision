//
// Created by John Uiterwyk on 5/28/15.
//

#include <fstream>
#include <streambuf>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "AppConfig.h"
#include "util/json/json.h"

namespace GeneticVision {
    void AppConfig::loadConfigFile(const string *filepath) {
        std::ifstream config_json(filepath->c_str());
        if (config_json.good() == false) {
            throw std::string("Error reading json config file.");
        }
        // For info about Json reader see:
        // https://github.com/open-source-parsers/jsoncpp
        // http://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html
        // https://github.com/open-source-parsers/jsoncpp/wiki
        Json::Value root;
        config_json >> root;

        string configFileDirectory = filepath->substr(0, filepath->find_last_of("\\/")) + "/";
        this->rootPath = root.get("rootPath", configFileDirectory).asString();
        this->outputPath = this->rootPath + root.get("outputPath", "output/").asString();
        this->popFilesPath = this->outputPath + "populations/";
        this->imagesOutputPath = this->outputPath + "images/";
        this->runLogPath = this->outputPath + "output.log";

        vector<ImagePair> result;

        Json::Value trainingSet = root["trainingSet"];
        cout << "trainingSet length: " << trainingSet.size() << endl;
        result = this->loadImages(trainingSet);
        cout << "result length: " << result.size() << endl;
        this->trainingImagePairs.insert( this->trainingImagePairs.end(), result.begin(), result.end() );


        Json::Value testSet = root["testSet"];
        cout << "trainingSet length: " << testSet.size() << endl;
        result = this->loadImages(testSet);
        cout << "result length: " << result.size() << endl;
        this->testImagePairs.insert( this->trainingImagePairs.end(), result.begin(), result.end() );

        // check for load from file
        this->loadPopulationEnabled = root.get("loadPopulationEnabled", false).asBool();
        if (this->loadPopulationEnabled) {
            this->loadPopulationPath =
                    this->rootPath + root.get("loadPopulationPath", "output/populations/gen_latest.gen").asString();
        }

        // create directories
        mode_t process_mask = umask(0);
        int result_code1 = mkdir(this->outputPath.c_str(), S_IRWXU | S_IREAD | S_IWRITE);
        int result_code2 = mkdir(this->popFilesPath.c_str(), S_IRWXU | S_IREAD | S_IWRITE);
        int result_code3 = mkdir(this->imagesOutputPath.c_str(), S_IRWXU | S_IREAD | S_IWRITE);
        umask(process_mask);

        // fetch values from json, or use default if not present
        this->logFrequency = root.get("logFrequency", 10).asInt();
        this->populationSize = root.get("populationSize", 100).asInt();
        this->mutation = root.get("mutation", 0.70).asDouble();
        this->crossover = root.get("crossover", 0.02).asDouble();
        this->elitism = root.get("elitism", 0.28).asDouble();
        this->minDepth = root.get("minDepth", 2).asInt();
        this->maxDepth = root.get("maxDepth", 5).asInt();
        this->maxGenerations = root.get("maxGenerations", 100).asInt();
        this->generationsPerTick = root.get("generationsPerTick", 1).asInt();

    }

    /**
     * loadImagesFromJson processess a list of objects that define a test image and the truthImage
     */
    vector<ImagePair> AppConfig::loadImages(const Json::Value &images) {
        vector<ImagePair> result;

        if (images.size() == 0)
        {
            // if size == 0, its a string and is a relative path
            vector<string> filePaths;
            string path = images.asString();
            DIR *directory;
            struct dirent * directoryEntry;
            directory = opendir ("./");
            if (directory != NULL)
            {
                while (directoryEntry = readdir (directory) )
                {

                }
                    puts (directoryEntry->d_name);
                (void) closedir (directory);
            }
            else
            {
                cerr << "Couldn't open the directory" << endl;
            }
        } else
        {
            // if size > 0, images is a json object
            result.resize(images.size());

            for (int index = 0; index < images.size(); ++index) {
                string testImage = this->rootPath + images[index].get("test", "").asString();
                string truthImage = this->rootPath + images[index].get("truth", "").asString();
                //cout << testImage << endl;
                //cout << truthImage << endl;

                result[index].loadTrainingImage(testImage);
                result[index].loadGroundTruth(truthImage);
                // Iterates over the sequence elements.
            }


        }
        cout << "Loaded " << result.size() << " image pairs" << endl;
        return result;

    }

}
