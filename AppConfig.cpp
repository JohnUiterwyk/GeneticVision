//
// Created by John Uiterwyk on 5/28/15.
//

#include <fstream>
#include <streambuf>
#include <string>
#include <iostream>
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

    this->workingDirectory = filepath->substr(0, filepath->find_last_of("\\/"));

    this->runLogPath =      root.get("runLogPath", "output/run_log.txt" ).asString();
    this->populationSize =  root.get("populationSize",100 ).asInt();
    this->mutation =        root.get("mutation",0.70 ).asDouble();
    this->crossover =       root.get("crossover",0.02 ).asDouble();
    this->elitism =         root.get("elitism",0.28).asDouble();
    this->minDepth =         root.get("minDepth",2).asInt();
    this->maxDepth =         root.get("maxDepth",5).asInt();

    //load image paths / images
    const Json::Value imagePairPaths = root["imagePairPaths"];
    this->imagePairs.resize(imagePairPaths.size());
    for ( int index = 0; index < imagePairPaths.size(); ++index )
    {

        this->imagePairs[index].loadTrainingImage(imagePairPaths[index].get("test","").asString()) ;
        this->imagePairs[index].loadGroundTruth(imagePairPaths[index].get("truth","").asString()) ;
        // Iterates over the sequence elements.
    }
    cout << "Loaded " << imagePairPaths.size() << " image pairs" << endl;
}
