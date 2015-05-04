using namespace std;
/******************************************************************************
 Header file
 Class:        SinParsimony
 Date created: 15/09/2008
 Written by:   Brian Pinto

 Applies parsimony pressure such that the size of the GP trees varies in a
 sinusoidal manner. All methods are pure virtual, subclasses must implement all
 methods.
******************************************************************************/
#include <float.h>
#include <math.h>
#include "SinParsimony.h"

//Constructor
SinParsimony::SinParsimony( double kFactor): Parsimony(kFactor)
{
   initmean = -1.0;
}

SinParsimony::~SinParsimony()
{
}

double SinParsimony::desiredFunc(int generation, Population *pop)
{
   if(initmean < 0)
   {
      initmean = pop->getAvgSize();
   }
   return (double) ((30 * sin( (double)(generation / 80))) + initmean);
}
