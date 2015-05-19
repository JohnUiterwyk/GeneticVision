#ifndef _MUTATION_H_
#define _MUTATION_H_

/******************************************************************************
 Header file
 Class:        Mutation
 Date created: 11/04/2002
 Written by:   Dylan Mawhinney

 The Mutation class is a class which mutates individual genetic programs.
 This particular example uses classic single point mutation, which
 selects the mutation point at random, deletes the subtree rooted at 
 that point, and replaces that subtree with a newly generated tree. 

******************************************************************************/

class GPConfig;
#include "GeneticProgram.h"

class Mutation 
{
   private:

   protected:

   public:
      virtual ~Mutation();

      /*********************************************
       The mutate method modifies the original 
       genetic program, make sure you have cloned
       this individual first before you call this
       method.
      **********************************************/
      virtual void mutate(GeneticProgram &gp, GPConfig *conf);
};

#endif
