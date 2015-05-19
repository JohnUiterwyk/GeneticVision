/******************************************************************************
 Definition file
 Class:        Selection 
 Date created: 07/05/2002
 Written by:   Dylan Mawhinney

 See header file for details.
******************************************************************************/

#include <string>

using namespace std;

#include "Selection.h"
#include "GPConfig.h"

int Selection::select(GeneticProgram* pop[], int popSize, GPConfig *config)
{
   int i;
   double totalFitness=0;
   double randValue;
   double cumulFitness;

   for(i=0; i<popSize; i++)
   {
      totalFitness += pop[i]->getAdjFitness();
   } 

   double tmpRand = config->randomNumGenerator->randReal();
   randValue = totalFitness * tmpRand; 

   cumulFitness = totalFitness;
   for(i=0; i<popSize; i++)
   {
      cumulFitness -= pop[i]->getAdjFitness();

      if(cumulFitness <= randValue) 
         break;   
   }

   if (i >= popSize)
   {
      i = popSize-1;
   }

   return i;
}

Selection::~Selection()
{
}
