using namespace std;
/******************************************************************************
 Header file
 Class:        LimitParsimony
 Date created: 15/09/2008
 Written by:   Brian Pinto

 Applies parsimony pressure such that the size of the GP trees is strictly 
 lmited to a given size. All methods are pure virtual, subclasses must
 implement all methods.

******************************************************************************/
#include <float.h>
#include <math.h>
#include "LimitParsimony.h"

//Constructor
LimitParsimony::LimitParsimony( double kFactor, int limit): Parsimony(kFactor)
{
	sizeLimit = limit;
   ck = 1;
}

LimitParsimony::~LimitParsimony()
{
}

double LimitParsimony::desiredFunc(int generation, Population *pop)
{
   if(pop->getAvgSize() >= sizeLimit)
      ck = 0;
   else 
      ck = 1;
   
   if(ck == 0)
      return (double) (sizeLimit);

   return 0.0;
}
