/*
 * DynamicDepthLimit.cpp
 *
 *  Created on: 30/09/2012
 *      Author: q
 */

#include "DynamicDepthLimit.h"

const bool DynamicDepthLimit::MAXIMISE_FITNESS = true;
const bool DynamicDepthLimit::MINIMISE_FITNESS = false;

bool DynamicDepthLimit::isBetter(double fitness1, double fitness2) {
	if (maximiseFitness) {
		if (fitness1 > fitness2) return true;
	} else {
		if (fitness1 < fitness2) return true;
	}
	return false;
}

bool DynamicDepthLimit::isBetterOrEqual(double fitness1, double fitness2) {
	if (maximiseFitness) {
		if (fitness1 >= fitness2) return true;
	} else {
		if (fitness1 <= fitness2) return true;
	}
	return false;
}

DynamicDepthLimit::DynamicDepthLimit(GPConfig* gpc, Fitness * fo) : config(gpc) {
	softLimit = gpc->maxDepth;
	minDepth = gpc->minDepth;
	bestFitness = -1;
	/* This is we infer whether we are maximising or minimising fitness, based on
	 * the reimplementation of these functions in the application specific
	 * subclass of FitnessObject.
	 */
	maximiseFitness = (fo->best() > fo->worst());
}

DynamicDepthLimit::~DynamicDepthLimit() {
	// TODO Auto-generated destructor stub
	// Nothing to do.
}

void DynamicDepthLimit::setDepthLimit(int d) {
	softLimit = d;
}

void DynamicDepthLimit::setHeavy(bool _heavy) {
	heavy = _heavy;
}

void DynamicDepthLimit::setVeryHeavy(bool _veryHeavy) {
	veryHeavy = _veryHeavy;
}


void DynamicDepthLimit::setFitnessPolarity(bool _maximiseFitness) {
	maximiseFitness = _maximiseFitness;
}

int DynamicDepthLimit::getSoftLimit() {
	return softLimit;
}

void DynamicDepthLimit::setBestFitness(double _bestFitness) {
	if (bestFitness == -1) {
		bestFitness = _bestFitness;
		return;
	}
	if (isBetter(_bestFitness,bestFitness)) bestFitness = _bestFitness;
}

int DynamicDepthLimit::getDepthLimit(GeneticProgram * gp, int parent1Size, int parent2Size) {
	// Set the limit to the greatest of the current soft limit or the two parents' sizes.
	int myLimit = softLimit;
	if (parent1Size > myLimit) myLimit = parent1Size;
	if (parent2Size > myLimit) myLimit = parent2Size;

	return myLimit;
}

bool DynamicDepthLimit::validateDepth(GeneticProgram * gp, int parent1Depth, int parent2Depth) {
	bool retVal = false;
	// Set the limit to the greatest of the current soft limit or the two parents' sizes.
	int myLimit = getDepthLimit(gp, parent1Depth, parent2Depth);

	// Calculate the fitness
	config->fitnessObject->assignFitness(&gp, 1);
	double gpFitness = gp->getFitness();

	int gpDepth = gp->getDepth();
	// If we're smaller then check for bestFitness and see if we can reduce the limit
	if (gpDepth <= myLimit) {
		retVal = true;
		if (isBetter(gpFitness,bestFitness)) {
			bestFitness = gpFitness;
			// See if we can reduce the depth limit at all
			if (veryHeavy || (heavy && (gpDepth > minDepth) ) ) softLimit = gpDepth;
		}
	} // if we're larger, then see if we're the fittest and if so, do the things
	else if ( (gpDepth > softLimit) && (isBetter(gpFitness,bestFitness)) ) {
		// Set the limit to be the depth of the new best individual
		softLimit = gpDepth;
		bestFitness = gpFitness;
		retVal = true;
	}

	return retVal;
}

