#ifndef _EMOTOURNAMENTSELECTION_H_
#define _EMOTOURNAMENTSELECTION_H_

/******************************************************************************
 Header file
 Class:        EMOTournamentSelection 
 Date created: 25 April 2011
 Written by:   Mohammad Nabi Omidvar

******************************************************************************/

#include "GeneticProgram.h"
#include "Selection.h"

class GPConfig;

class EMOTournamentSelection
{
    private:

    protected:

    public:
        /*********************************************
          The selection method selects an individual
          from the group of individuals passed to it.
         **********************************************/
        static GeneticProgram *select(GeneticProgram* ind1, GeneticProgram *ind2, GPConfig *config);
};

#endif
