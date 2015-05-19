/******************************************************************************
 Header file
 Function:		DynamicDepthLimit.h
 Date created:  30/09/2012
 Written by:    Quentin Serrurier

 Based on the journal article found here:
@article{silva2009dynamic,
  title={Dynamic limits for bloat control in genetic programming and a review of past and current bloat theories},
  author={Silva, S. and Costa, E.},
  journal={Genetic Programming and Evolvable Machines},
  volume={10},
  number={2},
  pages={141--179},
  year={2009},
  publisher={Springer}
}

This is a form of depth limit that dynamically adjusts whenever an overly deep
member of the population is encountered with the best fitness in the population.
In this case, the depth limit increases to match the new individual.

Optional elements also adjust the depth limit downwards where possible and optionally below starting limits.
These options appear to be safe to use in all cases and therefore, I recommend you enable them.

I suggest you implement this feature by adding "#define DDL true" to your FitnessObject header file.
Add the below code to the end of your FitnessObject constructor.

   if(DDL) {
	   conf->activateDDL(this);
	   conf->ddl->setHeavy(true);
	   conf->ddl->setVeryHeavy(true);
   }
******************************************************************************/

#ifndef DYNAMICDEPTHLIMIT_H_
#define DYNAMICDEPTHLIMIT_H_
#include "Population.h"
#include "GPConfig.h"

#include <iostream>


class DynamicDepthLimit {
private:
	GPConfig * config;

	int softLimit; // The soft limit used by the Population class, only soft because this class is in play
	int minDepth; // We don't go below this limit (unless veryHeavy is set)
	int bestFitness; // The best fitness we've seen so far

	bool heavy; // encourages the limit to fall when possible
	bool veryHeavy; // allows the limit to fall below the minDepth
	bool maximiseFitness; // True if greater fitness is better, it's deduced from fitness class best() and worst().

	bool isBetter(double fitness1, double fitness2); // Returns true if fitness1 is better than fitness2 for the given maximise/minimise direction
	bool isBetterOrEqual(double fitness1, double fitness2);

public:
	DynamicDepthLimit(GPConfig* gpc, Fitness * fo) ;
	virtual ~DynamicDepthLimit();

	/*******************************/
	static const bool MAXIMISE_FITNESS;
	static const bool MINIMISE_FITNESS;

	void setDepthLimit(int d);
	void setHeavy(bool _heavy);
	void setVeryHeavy(bool _veryHeavy);
	void setFitnessPolarity(bool _maximiseFitness);
	int getSoftLimit();
	void setBestFitness(double _bestFitness);
	int getDepthLimit(GeneticProgram * gp, int parent1Size, int parent2Size);
	//int getDepthLimit(GeneticProgram * gp, int parentSize); // For mutation


	bool validateDepth(GeneticProgram * gp, int parent1Depth, int parent2Depth);
	//bool doEverything(GeneticProgram * gp, int parentDepth);
	
	//bool doEverything(GeneticProgram * gp, int parent1Depth, int parent2Depth, double bestFitness);
	//bool doEverything(GeneticProgram * gp, int parentDepth, double bestFitness);

	//bool doSomeStuff(GeneticProgram * gp, double bestFitness, double gpFitness, int myLimit);
};

#endif /* DYNAMICDEPTHLIMIT_H_ */

