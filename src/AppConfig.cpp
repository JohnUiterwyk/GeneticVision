//
// Created by John Uiterwyk on 5/28/15.
// AppConfig uses the jsoncpp library: https://github.com/open-source-parsers/jsoncpp
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
#include <getopt.h>
#include <ctime>

namespace GeneticVision {


    AppConfig::AppConfig() :
            maxGenerations(100),
            populationSize(100),
            mutation(0.70),
            crossover(0.28),
            elitism(0.02),
            targetFitness(0.03),
            minDepth(2),
            maxDepth(5),
            saveResultImages(false),
            loadPopulationEnabled(false),
            rootPath("./"),
            outputPath("output/"),
            popFilesPath( "output/populations/"),
            imagesOutputPath("output/images/"),
            runLogPath("output/output.log"),
            evolveEnabled(false),
            testEnabled(false),
            logFrequency(1)
    {

    }

    void AppConfig::parseCommandLineArgs(int argc, char **argv) {

        int c;
        int option_index = 0;
        static struct option long_options[] = {
                {"config", required_argument, 0,  0 },
                {"evolve", no_argument, 0,  0 },
                {"test", no_argument, 0,  0 },
                {"run", no_argument, 0,  0 },
                {"images", required_argument, 0,  0 },
                {"generations", required_argument, 0,  0 },
                {"populationSize", required_argument, 0,  0 },
                {"mutation", required_argument, 0,  0 },
                {"crossover", required_argument, 0,  0 },
                {"elitism", required_argument, 0,  0 },
                {"minDepth", required_argument, 0,  0 },
                {"maxDepth", required_argument, 0,  0 },
                {"targetFitness", required_argument, 0,  0 },
                {"saveResultImages", no_argument, 0,  0 },
                {"population", required_argument, 0,  0 },
                {"logFrequency", required_argument, 0,  0 },
                {"outputPath", required_argument, 0,  0 }

        };

        //scan the options and look for the config file
        do{
            c = getopt_long(argc, argv, "", long_options, &option_index);
            if(c == 0 && string(long_options[option_index].name) == "config")
            {
                string jsonFilePath(optarg);
                cout << "loading config file: " << jsonFilePath << endl;
                this->loadConfigFile(&jsonFilePath);
            }
        }while(c != -1);

        // reset opt processing to 1 so we can rescan the options and get other options;
        // (yay. global vars. >_< let's wave our magic c wand.)
        optind = 1;

        //now apply other args
        do{
            c = getopt_long(argc, argv, "", long_options, &option_index);
            if (c == 0)
            {


                string longOptionName = long_options[option_index].name;
                std::stringstream argument;
                if(long_options[option_index].has_arg == true)
                {
                    argument << optarg;
                }
                //cout << "handle option: " << longOptionName;

                if(longOptionName == "evolve") this->evolveEnabled = true;
                if(longOptionName == "test") this->testEnabled = true;
                //if(longOptionName == "run") this->runMode = RUN;

                if(longOptionName == "generations") argument >> this->maxGenerations;

                if(longOptionName == "populationSize") argument >> this->populationSize;
                if(longOptionName == "mutation") argument >> this->mutation;
                if(longOptionName == "crossover") argument >> this->crossover;
                if(longOptionName == "elitism") argument >> this->elitism;
                if(longOptionName == "minDepth") argument >> this->minDepth;
                if(longOptionName == "maxDepth") argument >> this->maxDepth;
                if(longOptionName == "targetFitness") argument >> this->targetFitness;

                if(longOptionName == "logFrequency") argument >> this->logFrequency;

                if(longOptionName == "outputPath"){
                    argument >> this->outputPath;
                    if(this->outputPath.substr(this->outputPath.length()-1) != "/")
                    {
                        this->outputPath.append("/");
                    }
                }

                if(longOptionName == "guiEnabled") argument >> this->guiEnabled;

                if(longOptionName == "saveResultImages") argument >> this->saveResultImages;

                if(longOptionName == "population") // load population file
                {
                    this->loadPopulationEnabled = true;
                    this->loadPopulationPath = argument.str();
                }

                if(longOptionName == "images")
                {
                    this->trainPairs.loadFromDirectory(argument.str());
                }
            }

        }while(c != -1);

        if (optind < argc) {
            printf("non-option ARGV-elements: ");
            while (optind < argc)
                cout << argv[optind++];
            cout << endl;
        }
        this->setupOutputDirectories();

        //if evolve and test are not provide, assume evolve
        if(this->evolveEnabled == false && this->testEnabled == false)
        {
            this->evolveEnabled = true;
        }
    }

    void AppConfig::setupOutputDirectories()
    {
        this->outputPath = this->outputPath + "gv-run-" + this->getTimestampString()+"/";
        this->popFilesPath = this->outputPath + "populations/";
        this->imagesOutputPath = this->outputPath + "images/";
        this->runLogPath = this->outputPath + "run.log";
        
        // create output directories
        try {
            mode_t process_mask = umask(0);
            int result_code1 = mkdir(this->outputPath.c_str(), S_IRWXU | S_IREAD | S_IWRITE);
            int result_code2 = mkdir(this->popFilesPath.c_str(), S_IRWXU | S_IREAD | S_IWRITE);
            int result_code3 = mkdir(this->imagesOutputPath.c_str(), S_IRWXU | S_IREAD | S_IWRITE);
            umask(process_mask);
        }
        catch(int e)
        {
            cerr << "Error creating directories in AppConfig::createMissingDirectories()" << endl;
            throw;
        }

    }

    void AppConfig::loadConfigFile(const string *filepath) {
        std::ifstream config_json(filepath->c_str());
        if (config_json.good() == false) {
            throw std::string("Error reading json config file.");
        }
        Json::Value root;
        config_json >> root;

        // set default root directory
        string configFileDirectory = "./";
        // if the config file path has a slash in it
        unsigned long slashPosition = filepath->find_last_of("\\/");
        if(slashPosition != string::npos)
        {
            // extract the directory
            configFileDirectory = filepath->substr(0,slashPosition) + "/";
        }
        this->rootPath = root.get("rootPath", configFileDirectory).asString();

        if(root["outputPath"].isNull() == false)
        {
            this->outputPath = this->rootPath + root.get("outputPath", this->outputPath).asString();
            this->popFilesPath = this->outputPath + "populations/";
            this->imagesOutputPath = this->outputPath + "images/";
            this->runLogPath = this->outputPath + "run.log";
        }

        // load training set images
        Json::Value imagesJson = root["images"];
        if (imagesJson.size() == 0)
        {
            string path = this->rootPath + imagesJson.asString();
            this->trainPairs.loadFromDirectory(path);
        }else
        {
            this->trainPairs.loadFromJson(imagesJson, this->rootPath);
        }

        // check for load from file
        if(root["population"].isNull() == false)
        {
            this->loadPopulationEnabled = true;
            this->loadPopulationPath = this->rootPath + root.get("population", this->loadPopulationPath).asString();
        }

        // fetch values from json, or use default if not present

        // TODO: make log frequency and gens per tick consistent
        // currently you can have a mismatch of gens per tick and log frquency such that you never get any logs
        this->logFrequency = root.get("logFrequency", this->logFrequency).asInt();
        this->populationSize = root.get("populationSize", this->populationSize).asInt();
        this->mutation = root.get("mutation", this->mutation).asDouble();
        this->crossover = root.get("crossover", this->crossover).asDouble();
        this->elitism = root.get("elitism", this->elitism).asDouble();
        this->minDepth = root.get("minDepth", this->minDepth).asInt();
        this->maxDepth = root.get("maxDepth", this->maxDepth).asInt();
        this->maxGenerations = root.get("maxGenerations", this->maxGenerations).asInt();
        this->saveResultImages = root.get("saveResultImages",this->saveResultImages).asBool();
        this->testEnabled = root.get("test",this->testEnabled).asBool();
        this->evolveEnabled = root.get("evolve",this->evolveEnabled).asBool();

    }


    string AppConfig::getTimestampString() {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[256];

        time (&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer,256,"%Y-%m-%d-%H-%M-%S",timeinfo);
        std::string str(buffer);

        return str;
    }
}
