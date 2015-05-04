/******************************************************************************
 Definition file
 Class:        ADFProgramGenerator 
 Date created: 23/12/2003
 Written by:   Dharma Teja Nanduri

 See header file for details.

******************************************************************************/
#include <string>
using namespace std;

#include <iostream>

#include "GPConfig.h"
#include "ADFProgramGenerator.h"

ADFProgramGenerator::ADFProgramGenerator(GPConfig *conf) : ProgramGenerator(conf)
{
   if (conf->fitnessObject == NULL)
   {
       cout << "ADFProgramGenerator::ADFProgramGenerator : The fitnessObject of the GPConfig object must be populated";
   }
   /* Making copies of the original config object for the main branch and the ADF */
   adfConf = new GPConfig(*conf);
   mainConf = new GPConfig(*conf);
   adfConf->defaultInit();
   mainConf->defaultInit();
   /* The function set of the main branch has one more function which is the ADF */
   mainConf->funcSet.addNodeToSet(conf->termSet.getNodeReturnType(0), ADFunction::generate);
   mainConf->programGenerator = new ProgramGenerator(mainConf);
   adfConf->programGenerator = new ProgramGenerator(adfConf);
   conf = adfConf;
}

void ADFProgramGenerator::generateInitialPopulation(GeneticProgram* pop[],
                                             int numIndividuals,
                                             int minSize,
                                             int maxSize, int expectedSize,
                                             int expectedReturnType)
{
   ADFRoot *tmproot;
   int i;

   /* Creating memory for the main population   */
   GeneticProgram** mainPop = new GeneticProgram* [numIndividuals];

   if (mainPop == NULL)
      throw string("ADFProgramGenerator::generateInitialPopulation() Error, out of memory");
  
   for(i=0; i<numIndividuals; i++)
   {
      mainPop[i] = new GeneticProgram(mainConf);

      if (mainPop[i] == NULL)
         throw string("ADFProgramGenerator::generateInitialPopulation() Error, out of memory");

      mainPop[i]->setReturnType(expectedReturnType);
   }

   /* Creating the memory for the ADF population   */
   GeneticProgram** adfPop = new GeneticProgram* [numIndividuals];

   if (adfPop == NULL)
      throw string("ADFProgramGenerator::generateInitialPopulation() Error, out of memory");
  
   for(i=0; i<numIndividuals; i++)
   {
      adfPop[i] = new GeneticProgram(adfConf); 

      if (adfPop[i] == NULL)
         throw string("ADFProgramGenerator::generateInitialPopulation() Error, out of memory");

      adfPop[i]->setReturnType(expectedReturnType);
   }

   adfConf->programGenerator->generateInitialPopulation(adfPop, numIndividuals, minSize, maxSize, expectedSize, expectedReturnType);
   mainConf->programGenerator->generateInitialPopulation(mainPop, numIndividuals, minSize, maxSize, expectedSize, expectedReturnType);

   for(i=0;i<numIndividuals;i++)
   {
      tmproot = new ADFRoot(mainConf, expectedReturnType);
      tmproot->setArgN(0, adfPop[i]->getRoot());
      tmproot->setArgN(1, mainPop[i]->getRoot());
      pop[i]->setRoot(tmproot);
   }
}
