#ifndef _COEVOLUTIONPOPULATION_H_
#define _COEVOLUTIONPOPULATION_H_

/******************************************************************************
 Header file
 Class:        CoEvolutionPopulation 
 Date created: 18/09/2002
 Written by:   Dylan Mawhinney

 A CoEvolutionPopulation maintains a reference to another population, the
 other population is used during fitness evaluation for the current 
 generation. 
******************************************************************************/

class GPConfig;

#include <iostream>
#include <fstream>
#include <string>

#include "GeneticProgram.h"
#include "Mutation.h"
#include "Crossover.h"
#include "Selection.h"

#include "Population.h"

class CoEvolutionPopulation : public Population 
{
   private:
      string populationName;
      CoEvolutionPopulation *otherPopulation;

   protected:

   public:
      /**************************************************************
       Constructor, must specify the size (number of individuals)
       of the population, a log filename, a pointer to a GPConfig
       object, and the name of the population. The name is used when
       writing generations out to file to distinguish between 
       populations.
      **************************************************************/
      CoEvolutionPopulation(int size, const char *logFileName, GPConfig *conf,
                            string popName);

      virtual ~CoEvolutionPopulation();

      /**************************************************************
       Sets the otherPopulation member of this class.
      **************************************************************/ 
      void setOtherPopulation(CoEvolutionPopulation *aPop);

      /******************************************
       Assign fitness for the current population
      ******************************************/
      virtual void assignFitness();

      /***********************************************
       writeToFile will write the current generation
       out to a file in the current directory where
       the file name is of the form gen_XXXXX.gen,
       and XXXXX is the generation number.
      ************************************************/
      virtual void writeToFile();
};

#endif
