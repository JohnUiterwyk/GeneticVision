using namespace std;
/******************************************************************************
 Header file
 Class:        Parsimony
 Date created: 15/09/2008
 Written by:   Brian Pinto

 The Parsiomony class evaluates the parsimony coefficient for fitness
 evaluations used in fitness calculations..
 All methods are pure virtual, subclasses must implement all methods.
******************************************************************************/
#include <float.h>
//#include <math.h>
#include <cmath> // - Use modern library QCS 03092012
#include <limits.h>
#include <string.h>
#include <typeinfo>
#include "Parsimony.h"

//Constructor
Parsimony::Parsimony( double kFactor): k(kFactor)
{
}

Parsimony::~Parsimony()
{
}


double Parsimony::coVarFitness(Population *pop)
{
   int x;
   double y;
   double coVar;
   double meanX;
   
   memset(&coVar, 0, sizeof(double));
   memset(&meanX, 0, sizeof(double));
   memset(&meanY, 0, sizeof(double));
   memset(&y, 0, sizeof(double));
   memset(&x, 0, sizeof(int));

   meanX = pop->getAvgSize();
   meanY = pop->getAvgNormFitness();

   for(int i = 0; i < pop->getNumIndividuals(); i++)
   {
      pop->getIndividual(i)->computeSizeAndDepth();
      x = pop->getIndividual(i)->getSize();
      y = pop->getIndividual(i)->getNormFitness();
      coVar += ( ((x - meanX) * (y - meanY)) / pop->getNumIndividuals());
   }
   return coVar;
}


void Parsimony::setYArray(Population *pop, double **y)
{
   memset(&meanY, 0, sizeof(double));
   *y = new double [pop->getNumIndividuals()];
   
   for(int i = 0; i < pop->getNumIndividuals(); i++)
   {
      pop->getIndividual(i)->computeSizeAndDepth();
      (*y)[i] = pow(pop->getIndividual(i)->getSize(), k);

      meanY += (*y)[i];
   }

   meanY = (double) (meanY / pop->getNumIndividuals());
}


double Parsimony::coVarLength(Population *pop)
{
   int x;
   double coVar;
   double meanX;
   double *y;
   
   memset(&coVar, 0, sizeof(double));
   memset(&meanX, 0, sizeof(double));
   memset(&meanY, 0, sizeof(double));
   memset(&y, 0, sizeof(double *));
   memset(&x, 0, sizeof(int));

   meanX = pop->getAvgSize();
   setYArray(pop, &y);
   
   for(int i = 0; i < pop->getNumIndividuals(); i++)
   {
      //Uncomment if setYarray is not used or does not call computeSizeAndDepth
      //pop->getIndividual(i)->computeSizeAndDepth();
      x = pop->getIndividual(i)->getSize();
      coVar += ((x - meanX) * ((y[i]) - meanY));
      
   }
   coVar = coVar / pop->getNumIndividuals();
   delete [] y;
   return coVar;
}


double Parsimony::desiredFunc(int generation, Population *pop)
{
   return (double) 0.0;
}


double Parsimony::evalCoefficient(Population *pop, int option)
{
   double a, b;
   double desired;

   if(option == 0){
      a =  coVarFitness(pop);
      b = coVarLength(pop);
   }
   else
   {
      memset(&desired, 0, sizeof(double));

      desired = desiredFunc(pop->getGenerationNumber() + 1, pop) - pop->getAvgSize();
   
      a = (coVarFitness(pop) - (desired * pop->getAvgNormFitness()));
      b = (coVarLength(pop) - (desired * meanY));
   }
    //cout<< "f : "<< a << "L : "<< b << endl << flush;  
   if( a != 0 and b != 0)
      return a / b;
   else
      return 0;
}

void Parsimony::applyParsimony(Population *pop)
{
   double parsimonycoeff;
   double penalty;

   memset(&parsimonycoeff, 0, sizeof(double));

	int option=0;
	if(strcmp(typeid(*this).name(), "Parsimony")!=0 )
	   option = 1;

   parsimonycoeff = evalCoefficient(pop, option);
   //parsimonycoeff = (parsimonycoeff * 100) / DBL_MAX;
   pop->parscoeff = parsimonycoeff;
   
   for(int i = 0; i < pop->getNumIndividuals(); i++)
   {
      memset(&penalty, 0, sizeof(double));
      penalty = parsimonycoeff * pop->getIndividual(i)->getSize();
      
      if( !isnan(penalty) )
      {
         if((pop->getIndividual(i)->getNormFitness() - penalty ) <= 1.0 && 
                    (pop->getIndividual(i)->getNormFitness() - penalty ) >= 0 )
            pop->getIndividual(i)->setNormFitness(
                           pop->getIndividual(i)->getNormFitness() - penalty );
         else
            pop->getIndividual(i)->setNormFitness(
                                       pop->getIndividual(i)->getNormFitness());
      }
      else
         pop->getIndividual(i)->setNormFitness(
                                       pop->getIndividual(i)->getNormFitness());
   }
}
