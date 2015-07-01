//
// Created by John Uiterwyk on 6/4/15.
//

#include "GvPopulation.h"
namespace GeneticVision {
    void GvPopulation::writeToFile() {
        char filename[512];
        ofstream outputFile;

        sprintf(filename, "%sgen-%06d.gen", outputDir.c_str(), generationNumber);
        outputFile.open(filename);

        if (outputFile.good())
            outputFile << *this;
        else
            throw string("Population::writeToFile Error could not open file");

        outputFile.close();

        if (useCompression)
            compressFile(filename);

        sprintf(filename, "%sgen-latest.gen", outputDir.c_str());
        outputFile.open(filename);

        if (outputFile.good())
            outputFile << *this;
        else
            throw string("Population::writeToFile Error could not open file");

        outputFile.close();
    }

    GvPopulation::~GvPopulation() {
            if (evaluations > 0)
            {
                writeToFile();
            }
    }
}