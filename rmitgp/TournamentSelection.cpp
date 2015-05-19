/******************************************************************************
 Definition file
 Class:        TournamentSelection 
 Date created: 21/06/2002
 Written by:   Dylan Mawhinney

 See header file for details.
******************************************************************************/

using namespace std;

#include "TournamentSelection.h"
#include "GPConfig.h"

TournamentSelection::TournamentSelection(int tournamentSize) 
                                                    : tournSize(tournamentSize)
{
}

void TournamentSelection::setTournamentSize(int size)
{
   tournSize = size;
}

int TournamentSelection::select(GeneticProgram* pop[], int popSize,
                                GPConfig *config)
{
   int i;
   int individual;
   int bestIndividual=-1;

   for(i=0; i<tournSize; i++)
   {
      individual = (config->randomNumGenerator->randNum() % popSize);

      if (bestIndividual < 0)
         bestIndividual = individual;
      else if (config->fitnessObject->isBetter(pop[individual], pop[bestIndividual]))
      //else//Normalized fitness used to apply parsimony pressure
      //if(pop[individual]->getNormFitness() > 
         //                               pop[bestIndividual]->getNormFitness())
         bestIndividual = individual;
   }

   return bestIndividual;
}
