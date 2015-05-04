#ifndef _ADFPROGRAMGENERATOR_H_
#define _ADFPROGRAMGENERATOR_H_

/******************************************************************************
 Header file
 Class:        ADFProgramGenerator 
 Date created: 23/12/2004
 Written by:   Dharma Teja Nanduri

 The ADFProgramGenerator class generates program trees with Automatically
 Defined Function. Currently only one ADF is created per tree. The ADF does
 not take any arguements.

******************************************************************************/


#include "NodeSet.h"
#include "ProgramGenerator.h"

#include "ADFunction.h"
#include "ADFRoot.h"

class ADFProgramGenerator : public ProgramGenerator
{
   private:
      //ProgramGenerator *adfProgramGenerator;
      GPConfig *mainConf;
      GPConfig *adfConf;
   public:
      /**************
       Constructor
       *************/
      ADFProgramGenerator(GPConfig*);

      virtual void generateInitialPopulation(GeneticProgram* pop[],
                                             int numIndividuals,
                                             int minSize,
                                             int maxSize, int expectedSize,
                                             int expectedReturnType);

};

#endif
