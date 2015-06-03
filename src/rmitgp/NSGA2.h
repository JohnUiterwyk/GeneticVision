#ifndef _NSGA2_H_
#define _NSGA2_H_

/****************************************************************
 * Class: NSGA.h
 * Description: 
 * Written by: Mohammad Nabi Omidvar
 * Date Created: 16 Mar 2011
 ***************************************************************/

#include "GeneticProgram.h"
#include "Population.h"
#include "list.h"

#define INF 1.0e14
#define EPS 1.0e-14
#define E  2.71828182845905
#define PI 3.14159265358979

class NSGA2{

    private:

	public:
		static int checkDominance(GeneticProgram *a, GeneticProgram *b, int numObj);

        static void assignRankAndCrowdingDistance (GeneticProgram **new_pop, int numObj, int popsize);
        static void fillNondominatedSort (GeneticProgram **mixed_pop, GeneticProgram **new_pop, int popsize, int nobj);

        static void crowdingFill (GeneticProgram **mixed_pop, GeneticProgram **new_pop, int count, int front_size, list *elite, int popsize, int nobj);

        static void assignCrowdingDistanceList (GeneticProgram **pop, list *lst, int front_size, int nobj);

        static void assignCrowdingDistanceIndices (GeneticProgram **pop, int c1, int c2, int nobj);

        static void assignCrowdingDistance (GeneticProgram **pop, int *dist, int **obj_array, int front_size, int nobj);

};

#endif
