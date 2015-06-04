//
// Created by John Uiterwyk on 5/28/15.
//

#include <fstream>
#include <streambuf>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include "util/json/json.h"
#include "AppConfig.h"

void GeneticVision::AppConfig::loadConfigFile(const string *filepath)
{
    std::ifstream config_json(filepath->c_str());
    if(config_json.good() == false)
    {
        throw std::string("Error reading json config file.");
    }
    // For info about Json reader see
    // see http://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html
    Json::Value root;
    config_json >> root;

    string configFileDirectory = filepath->substr(0, filepath->find_last_of("\\/"))+"/";
    this->rootPath = root.get("rootPath", configFileDirectory ).asString();
    this->outputPath = this->rootPath + root.get("outputPath", "output/" ).asString();
    this->popFilesPath = this->outputPath + "populations/";
    this->imagesOutputPath = this->outputPath + "images/";
    this->runLogPath = this->outputPath + "output.log";

    //
    this->loadPopulationEnabled =  root.get("loadPopulationEnabled",false ).asBool();
    if(this->loadPopulationEnabled)
    {
        this->loadPopulationPath = this->rootPath + root.get("loadPopulationPath", "output/populations/gen_latest.gen" ).asString();
    }

    // create directories
    mode_t process_mask = umask(0);
    int result_code1 = mkdir(this->outputPath.c_str(), S_IRWXU | S_IREAD | S_IWRITE);
    int result_code2 = mkdir(this->popFilesPath.c_str(),S_IRWXU | S_IREAD | S_IWRITE);
    int result_code3 = mkdir(this->imagesOutputPath.c_str(),S_IRWXU | S_IREAD | S_IWRITE);
    umask(process_mask);

    // fetch values from json, or use default if not present
    this->logFrequency =  root.get("logFrequency",10 ).asInt();
    this->populationSize =  root.get("populationSize",100 ).asInt();
    this->mutation =        root.get("mutation",0.70 ).asDouble();
    this->crossover =       root.get("crossover",0.02 ).asDouble();
    this->elitism =         root.get("elitism",0.28).asDouble();
    this->minDepth =         root.get("minDepth",2).asInt();
    this->maxDepth =         root.get("maxDepth",5).asInt();
    this->maxGenerations =         root.get("maxGenerations",100).asInt();
    this->generationsPerTick =         root.get("generationsPerTick",1).asInt();

    //load image paths / images
    const Json::Value imagePairPaths = root["imagePairs"];
    this->imagePairs.resize(imagePairPaths.size());

    for ( int index = 0; index < imagePairPaths.size(); ++index )
    {
        string testImage = configFileDirectory + imagePairPaths[index].get("test","").asString();
        string truthImage = configFileDirectory + imagePairPaths[index].get("truth","").asString();
        //cout << testImage << endl;
        //cout << truthImage << endl;

        this->imagePairs[index].loadTrainingImage(testImage) ;
        this->imagePairs[index].loadGroundTruth(truthImage) ;
        // Iterates over the sequence elements.
    }
    cout << "Loaded " << this->imagePairs.size() << " image pairs" << endl;
}
