/******************************************************************************
 Definition file
 Class:        CoEvolutionPopulation 
 Date created: 18/09/2002
 Written by:   Dylan Mawhinney

 See header file for details.
******************************************************************************/

#include <cstdio>

using namespace std;

#include "CoEvolutionPopulation.h"
#include "CoEvolutionFitness.h"

#include "GPConfig.h"

CoEvolutionPopulation::CoEvolutionPopulation(int size, const char *logFileName,
                                            GPConfig *conf, string popName)
                                      : Population(size, logFileName, conf),
                                        populationName(popName),
                                        otherPopulation(NULL)
{
}

CoEvolutionPopulation::~CoEvolutionPopulation()
{
   otherPopulation = NULL;
}

void CoEvolutionPopulation::setOtherPopulation(CoEvolutionPopulation *aPop)
{
   otherPopulation = aPop;
}

void CoEvolutionPopulation::assignFitness()
{
   dynamic_cast<CoEvolutionFitness*>(config->fitnessObject)
               ->assignFitness(getPopulation(),
                               otherPopulation->getPopulation(),
                               getNumIndividuals(),
                               otherPopulation->getNumIndividuals());
}

void CoEvolutionPopulation::writeToFile()
{
   char filename[50];
   ofstream outputFile;

   sprintf(filename, "%s_gen_%05d.gen", populationName.c_str(),
                                        getGenerationNumber());
   outputFile.open(filename);
 
   if (outputFile.good())
      outputFile << *this;
   else
      throw string("CoEvolutionPopulation::writeToFile Error could not open file");

   outputFile.close();

   if (getCompressFiles())
      compressFile(filename);
}
