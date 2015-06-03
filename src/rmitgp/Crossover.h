#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

/******************************************************************************
 Header file
 Class:        Crossover 
 Date created: 11/04/2002
 Written by:   Dylan Mawhinney

 The crossover class breeds two genetic programs by exchanging portions
 of their code, to generate two new children.

******************************************************************************/
class GeneticProgram;

#include "GeneticProgram.h"

class Crossover 
{
   private:

   protected:

   public:
      virtual ~Crossover();

      /************************************************
       The crossover function modifies the two
       programs, make sure you have copied them before
       you call this function if you don't want to 
       have your originals modified.
       gp1 and gp2 are the programs to be crossed over.
       numRetries is the maximum number of tries to 
       perform before giving up finding valid crossover
       points. 
      *************************************************/
      virtual void crossover(GeneticProgram &gp1, GeneticProgram &gp2,
                             int numRetries, GPConfig *config);
      virtual void crossoverDDL(GeneticProgram &gp1, GeneticProgram &gp2,
                             int numRetries, GPConfig *config);
};

#endif
