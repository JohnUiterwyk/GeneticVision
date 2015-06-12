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
#include <map>

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

        string configFileDirectory = "./";

        //if the config file path has a slash in it, extract the directory
        unsigned long slashPosition = filepath->find_last_of("\\/");
        if(slashPosition != string::npos)
        {
            configFileDirectory = filepath->substr(0,slashPosition) + "/";
        }

        this->rootPath = root.get("rootPath", configFileDirectory).asString();
        this->outputPath = this->rootPath + root.get("outputPath", "output/").asString();
        this->popFilesPath = this->outputPath + "populations/";
        this->imagesOutputPath = this->outputPath + "images/";
        this->runLogPath = this->outputPath + "output.log";

        // load training set images
        Json::Value trainingSet = root["trainingSet"];
        if (trainingSet.size() == 0)
        {
            string path = this->rootPath + trainingSet.asString();
            this->trainPairs.loadFromDirectory(path);
        }else
        {
            this->trainPairs.loadFromJson(trainingSet, this->rootPath);
        }

        // load test set images
        Json::Value testSet = root["testSet"];
        if (testSet.size() == 0)
        {
            string path = this->rootPath + testSet.asString();
            this->testPairs.loadFromDirectory(path);
        }else
        {
            this->testPairs.loadFromJson(testSet, this->rootPath);
        }

        // check for load from file
        this->loadPopulationEnabled = root.get("loadPopulationEnabled", false).asBool();
        if (this->loadPopulationEnabled) {
            this->loadPopulationPath =
                    this->rootPath + root.get("loadPopulationPath", "output/populations/gen_latest.gen").asString();
        }

        // create output directories
        mode_t process_mask = umask(0);
        int result_code1 = mkdir(this->outputPath.c_str(), S_IRWXU | S_IREAD | S_IWRITE);
        int result_code2 = mkdir(this->popFilesPath.c_str(), S_IRWXU | S_IREAD | S_IWRITE);
        int result_code3 = mkdir(this->imagesOutputPath.c_str(), S_IRWXU | S_IREAD | S_IWRITE);
        umask(process_mask);

        // fetch values from json, or use default if not present
        this->logFrequency = root.get("logFrequency", 1).asInt();
        this->populationSize = root.get("populationSize", 100).asInt();
        this->mutation = root.get("mutation", 0.70).asDouble();
        this->crossover = root.get("crossover", 0.02).asDouble();
        this->elitism = root.get("elitism", 0.28).asDouble();
        this->minDepth = root.get("minDepth", 2).asInt();
        this->maxDepth = root.get("maxDepth", 5).asInt();
        this->maxGenerations = root.get("maxGenerations", 1).asInt();
        this->generationsPerTick = root.get("generationsPerTick", 1).asInt();
        this->saveResultImages = root.get("saveResultImages",true).asBool();

    }




}
