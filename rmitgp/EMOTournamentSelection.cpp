/******************************************************************************
 Header file
 Class:        EMOTournamentSelection 
 Date created: 25 April 2011
 Written by:   Mohammad Nabi Omidvar

******************************************************************************/

using namespace std;

#include "EMOTournamentSelection.h"
#include "GPConfig.h"
#include "NSGA2.h"
#include "GeneticProgram.h"
#include <cstdlib>

GeneticProgram* EMOTournamentSelection::select(GeneticProgram *ind1, GeneticProgram *ind2, GPConfig *config)
{
    int flag;
    flag = NSGA2::checkDominance (ind1, ind2, config->numObjectives);

    if (flag==1)
    {
        return (ind1);
    }
    if (flag==-1)
    {
		return (ind2);
    }
    if (ind1->getCrowdingDist() > ind2->getCrowdingDist())
    {
        return(ind1);
	}
    if (ind2->getCrowdingDist() > ind1->getCrowdingDist())
    {
		return(ind2);
    }
    //TODO: Is this proper way of generatig a rendom numbers? 
    if ((rand()/(double)RAND_MAX) <= 0.5) 
    {
		return(ind1);
    }
    else
    {
		return(ind2);

    }
}
