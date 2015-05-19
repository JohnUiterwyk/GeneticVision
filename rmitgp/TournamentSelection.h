#ifndef _TOURNAMENTSELECTION_H_
#define _TOURNAMENTSELECTION_H_

/******************************************************************************
 Header file
 Class:        TournamentSelection 
 Date created: 21/06/2002
 Written by:   Dylan Mawhinney

 The tournament selection class is an implementation of the
 tournament selection operator as described in (Insert paper)
******************************************************************************/

#include "GeneticProgram.h"
#include "Selection.h"

class GPConfig;

class TournamentSelection : public Selection
{
   private:
      int tournSize;
      int *group;

   protected:

   public:
      /***************************************
       Must supply the tournament size to the
       constructor. The tournament size must
       be less than or equal to the number of
       individuals in the population.
      ***************************************/
      TournamentSelection(int tournamentSize);

      void setTournamentSize(int size);

      /*********************************************
       The selection method selects an individual
       from the group of individuals passed to it.
      **********************************************/
      virtual int select(GeneticProgram* pop[], int popSize, GPConfig *config);
};

#endif
