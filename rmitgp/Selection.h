#ifndef _SELECTION_H_
#define _SELECTION_H_

/******************************************************************************
 Header file
 Class:        Selection 
 Date created: 07/05/2002
 Written by:   Dylan Mawhinney

 The selection class selects an individual from a group of individuals
 for participation in some genetic process. 
******************************************************************************/

#include "GeneticProgram.h"
class GPConfig;

class Selection 
{
   private:

   protected:

   public:
      virtual ~Selection();

      /*********************************************
       The selection method selects an individual
       from the group of individuals passed to it.
      **********************************************/
      virtual int select(GeneticProgram* pop[], int popSize, GPConfig *config);
};

#endif
