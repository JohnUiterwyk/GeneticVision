#ifndef _PARSIMONY_H_
#define _PARSIMONY_H_
using namespace std;

/******************************************************************************
 Header file
 Class:        Parsimony
 Date created: 15/09/2008
 Written by:   Brian Pinto

 The Parsiomony class evaluates the parsimony coefficient for fitness
 evaluations used in fitness calculations.
 All methods are pure virtual, subclasses must implement all methods.
******************************************************************************/
#include "Population.h"

class Population;
class Parsimony 
{
   private:
      double meanY;
      double k;

   protected:

   public:
      //Constructor
      Parsimony(double k); 
      virtual ~Parsimony();

      /******************************
      ******************************/
      double coVarFitness(Population *pop);
      
      double coVarLength(Population *pop);

      virtual double desiredFunc(int generation, Population *pop);

      double evalCoefficient(Population *pop, int option);
      
      void setYArray(Population *pop, double **y);

      void applyParsimony(Population *pop);
};

#endif
