#pragma once

/******************************************************************************
 Header file
 Function:		CovariantTarpeian.h
 Date created:  17/09/2012
 Written by:    Quentin Serrurier

 Based on the journal article found here:
 @article{poli2011covariant,
  title={Covariant Tarpeian method for bloat control in genetic programming},
  author={Poli, R.},
  journal={Genetic Programming Theory and Practice VIII},
  pages={71--89},
  year={2011},
  publisher={Springer}
}

	This is a form of bloat control that relies on a dynamic, covariance-based probability of applying fatal fitness adjustment to 
	individuals with greater than average size.
	It can be constant or based on a following function r(t).
	This version has a following function that adjust dynamically based on the covariance of size and fitness in the population.
	It is recommended to use this.

I suggest you implement this feature by adding "#define TARPEIAN true" to your FitnessObject header file.
Add the below code to the end of your FitnessObject constructor.
   if(TARPEIAN) conf->activateTarpeian(this);


******************************************************************************/

#include "Population.h"
#include "Fitness.h"
class Population;

class CovariantTarpeian
{
   private:
      double f_bad;

      double covariance_double_means(double* X, double* Y, int n, double xbar, double ybar);
      double getOptimalPt(Population* pop);
   protected:

   public:
      //Constructor
      CovariantTarpeian( Fitness * fo );
      virtual ~CovariantTarpeian();

      /******************************
      ******************************/



      double getTarpeianFitness(GPConfig * gpc, GeneticProgram * gp, double avgSize, double pt);
      void applyTarpeian(Population *pop, GPConfig * config);
};






