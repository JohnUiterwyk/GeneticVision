using namespace std;
#define _USE_MATH_DEFINES

#include <cmath>
#include "Population.h"
#include "GeneticProgram.h"
#include "Fitness.h"
#include "GPConfig.h"
#include "GPConfig.h"

#include "CovariantTarpeian.h"

CovariantTarpeian::CovariantTarpeian( Fitness * fo )
{
	f_bad = fo->worst();
}

CovariantTarpeian::~CovariantTarpeian()
{
}

double CovariantTarpeian::covariance_double_means(double* X, double* Y, int n, double xbar, double ybar) {
	double cov;
	double sum=0;
	for(int i=0;i<n;i++) {
		sum += (X[i]-xbar) * (Y[i]-ybar);
	}
	cov = (double)sum/n;
	return cov;
}

double CovariantTarpeian::getOptimalPt(Population* pop) {
	/*
	 * Pt = covLF/( thetaGt * ( covGtLF +  (muGt - mu) * (fbarGt - fbad) )  )
	 */

	double mu = pop->getAvgSize(); // This is the mean size of programs in the current generation

	double fbar = pop->getAvgFitness(); // This is the mean fitness of programs in the current generation
	double fbarGt = 0.0; // Average fitness for members with greater than average size
	//double varl = pop->getStdDevSize() * pop->getStdDevSize(); // The variance of program sizes via population->stdDevSize
	double covLF = 0.0; // The covariance of size and fitness in the population at the present time step
	double covGtLF = 0.0; // The covariance of size and fitness for individuals of above average size
	double pt = 0.0; // The optimal probability for applying Tarpeian selection, based on Price's Equation
	int n = pop->getNumIndividuals();
	int numGt = 0; // Number of members with greater than average size
	int sumFGt = 0; // Total of fitnesses for individuals with greater than average size
	int sumSGt = 0; // Sum of greater than average sizes
	double muGt = 0.0; // Mean size for programs of greater than average size
	double phiGt = 0.0; // Proportion of the population that are over size

	// Get the sizes and fitnesses of the population
	//GeneticProgram** gps = pop->getPopulation();
	double * sizes		= new double[n];
	double * fitnesses	= new double[n];
	for(int i=0;i<n;i++) {
		sizes[i] = pop->getIndividual(i)->getSize();
		fitnesses[i] = pop->getIndividual(i)->getFitness();
		if (sizes[i] > mu) {
			numGt++;
			sumFGt+=fitnesses[i];
			sumSGt+=sizes[i];
		}
	}
	fbarGt = (double)sumFGt/numGt;
	muGt = (double)sumSGt/numGt;

	double * gtsizes		= new double[numGt];
	double * gtfitnesses	= new double[numGt];
	int gtloop = 0;
	// Populate the fat subset
	for(int i=0;i<n;i++) {
		//printf("Testing %f against %f\n", sizes[i], mu);
		if (sizes[i] > mu) {
			gtsizes[gtloop] = sizes[i];
			gtfitnesses[gtloop] = fitnesses[i];
			gtloop++;
		}
	}


	// The covariance of size and fitness in the population at the present time step

	/* The covariance functions from gsl_stats should NOT be used, they are not the
	 * same model of covariance as is used in the literature this is based on.
	 * The locally implemented functions here use the same covariance model as the
	 * literature and therefore are preferred.
	 *
	 */

	//covLF = gsl_stats_covariance(sizes, sizeof(double), fitnesses, sizeof(double), 4);
	covLF = covariance_double_means(sizes, fitnesses, n, mu, fbar);
	// The covariance of size and fitness within the above average sized population subset
	//covGtLF = gsl_stats_covariance_m(gtsizes, sizeof(double), gtfitnesses, sizeof(double), numGt, muGt, fbarGt);
	covGtLF = covariance_double_means(gtsizes, gtfitnesses, numGt, muGt, fbarGt);

	phiGt = (double)numGt/n;
	pt = covLF/( phiGt * ( covGtLF +  (muGt - mu) * (fbarGt - f_bad) )  );

	return pt;
}

double CovariantTarpeian::getTarpeianFitness(GPConfig * gpc, GeneticProgram * gp, double avgSize, double pt) {
	if ( (gp->getSize() > avgSize) && (gpc->randomNumGenerator->randReal() < pt) ) {
		return f_bad;
	}
	else return gp->getFitness();
}

void CovariantTarpeian::applyTarpeian(Population *pop, GPConfig * config)
{
	double pt = getOptimalPt(pop);
	for(int i = 0; i < pop->getNumIndividuals(); i++)
	{
		if ((pop->getIndividual(i)->getSize() > pop->getAvgSize()) && (config->randomNumGenerator->randReal() < pt))
			pop->getIndividual(i)->setNormFitness(f_bad);
	}
}
