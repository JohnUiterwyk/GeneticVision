#ifndef _PROGRAMGENERATOR_H_
#define _PROGRAMGENERATOR_H_

/******************************************************************************
 Header file
 Class:        ProgramGenerator 
 Date created: 22/04/2002
 Written by:   Dylan Mawhinney

 The ProgramGenerator class generates program trees.

******************************************************************************/


#include "NodeVector.h"
#include "GeneticProgram.h"
#include "Node.h"

class ProgramGenerator 
{
   private:
      GPConfig *config;

      NodeVector<Node> *growTable;
      NodeVector<Node> *fullTable;

   protected:

   public:
      ProgramGenerator(GPConfig *conf);
      virtual ~ProgramGenerator();

      /*********************************************
       Generates an inital population.
      **********************************************/
      virtual void generateInitialPopulation(GeneticProgram* pop[],
                                             int numIndividuals,
                                             int minSize,
                                             int maxSize, int expectedSize,
                                             int expectedReturnType);

      virtual Node* createFullProgram(int curDepth, int maxDepth,
                                      int expectedReturnType);

      virtual Node* createGrowProgram(int curDepth, int maxDepth, 
                                      int expectedReturnType);

};

#endif
