#ifndef _SINPARSIMONY_H_
#define _SINPARSIMONY_H_
using namespace std;

/******************************************************************************
 Header file
 Class:        SinParsimony
 Date created: 15/09/2008
 Written by:   Brian Pinto

 Applies parsimony pressure such that the size of the GP trees varies in a
 sinusoidal manner. 
******************************************************************************/
#include "Population.h"
#include "Parsimony.h"

class Population;
class SinParsimony : public Parsimony
{
   private:
      double initmean;

   protected:

   public:
      //Constructor
      SinParsimony(double k); 
      virtual ~SinParsimony();

      virtual double desiredFunc(int generation, Population *pop);
};

#endif
