#ifndef _COEVOLUTIONFITNESS_H_
#define _COEVOLUTIONFITNESS_H_

/******************************************************************************
 Header file
 Class:        CoEvolutionFitness 
 Date created: 18/09/2002
 Written by:   Dylan Mawhinney

 CoEvolutionFitness is a Fitness object which can be used in co-evolutionary
 situations. The assign fitness method accepts two populations instead
 of the usual single population. Typically one population is evolve
 competitively against the other.

 The assignFitness method is pure virtual, meaning all concrete classes
 must implement this method (along with the other pure virtual methods
 from class Fitness).
******************************************************************************/

class GPConfig;
#include "Fitness.h"

class CoEvolutionFitness : public Fitness
{
   private:

   protected:

   public:
      //Constructor
      CoEvolutionFitness(GPConfig *conf); 

      /***********************************************************
       In CoEvolutionFitness the assignFitness method accepts
       two populations, the fitness of the programs in population
       one will be determined, typically by competing them against
       population two.
      ***********************************************************/
      virtual void assignFitness(GeneticProgram **pop1, GeneticProgram **pop2,
                                 int numIndividuals1, int numIndividuals2) = 0;


};

#endif
