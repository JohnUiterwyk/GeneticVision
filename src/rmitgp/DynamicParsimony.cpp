using namespace std;
#define _USE_MATH_DEFINES

#include <string>
#include <math.h>
#include <gsl/gsl_statistics_double.h>
#include <gsl/gsl_statistics_int.h>
#include "Population.h"
#include "GeneticProgram.h"

#include "DynamicParsimony.h"


double rFunction (int t, double amplitude, double period, double muz);

double getParsimonyCoefficient (Population * pop, double amplitude, double runLength, double muz) {
/*	r(t+1)
 * 	mu(t)
 *	fbar
 * 	var(l)
 * 	cov(l,f)
 *
 *  amplitude is the amplitude of the sine wave used as the r function, we subtract the ground level of the sine-wave (muz) to get the relative amplitude
 *  runLength is the half-period of the sine wave.
 *  muz is the mean tree size in nodes at time step zero (after the initial growth function),
 * it is used as the centre amplitude or ground level of the sine wave.
 */

	// ct = (cov(l,f) - (r(t+1)-mu(t)) * fbar)/ (var(l) - (r(t+1)-mu(t)) * mu(t) );
	
	
	double ct;
	double mut = pop->getAvgSize(); // This is mu(t) which is the mean size of programs at time t
	double fbar = pop->getAvgFitness(); // This is the mean fitness of programs at time t

	int n = pop->getNumIndividuals();
	
	double varl = pop->getStdDevSize() * pop->getStdDevSize(); // The variance of program sizes via population->stdDevSize

	// Get the sizes and fitnesses of the population
	GeneticProgram** gps = pop->getPopulation();
	double * sizes		= new double[n];
	double * fitnesses	= new double[n];
	
	for(int i=0;i<n;i++) {
		sizes[i] = gps[i]->getSize();
		fitnesses[i] = gps[i]->getFitness();
	}

	// The covariance of size and fitness in the population at the present time step
	double covlf = gsl_stats_covariance_m(sizes, sizeof(int), fitnesses, sizeof(double), n, mut, fbar);


	int t = pop->getGenerationNumber();

	// The 'r function' which is the function that we desire the population size to follow
	double r = rFunction((t+1), (amplitude-muz), runLength, muz);
	// 10k ramped descending: 10000 - (30 * t);

	ct = ( ( covlf - (r - mut) ) * fbar ) / ( ( varl - (r - mut) ) * mut );


	return ct;
}

double rFunction (int t, double amplitude, double period, double muzero) {
	// r = A * sin(t/P/pi) +mu(0) where A = amplitude, P = half period and mu(0) sets the ground level
   
	return (amplitude * sin(t/period * M_PI) + muzero);
}
