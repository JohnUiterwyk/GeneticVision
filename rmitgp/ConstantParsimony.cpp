using namespace std;
/******************************************************************************
 Header file
 Class:        Parsimony
 Date created: 15/09/2008
 Written by:   Brian Pinto

 Applies parsimony pressure such that the size of the trees remains constant.
 All methods are pure virtual, subclasses must implement all methods.
******************************************************************************/
#include <float.h>
#include <math.h>
#include "ConstantParsimony.h"

//Constructor
ConstantParsimony::ConstantParsimony( double kFactor): Parsimony(kFactor)
{
   initmean = -1.0;
}

ConstantParsimony::~ConstantParsimony()
{
}

double ConstantParsimony::desiredFunc(int generation, Population *pop)
{
   if(initmean < 0)
   {
      initmean = pop->getAvgSize();
   }
   return (double) (initmean);
}
