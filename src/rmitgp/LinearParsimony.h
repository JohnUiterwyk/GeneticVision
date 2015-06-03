#ifndef _LINEARPARSIMONY_H_
#define _LINEARPARSIMONY_H_
using namespace std;

/******************************************************************************
 Header file
 Class:        LinearParsimony
 Date created: 15/09/2008
 Written by:   Brian Pinto

 Applies parsimony pressure such that the size of the GP trees has a linear
 growth.
******************************************************************************/
#include "Population.h"
#include "Parsimony.h"

class Population;
class LinearParsimony : public Parsimony
{
   private:
      double initmean;

   protected:

   public:
      //Constructor
      LinearParsimony(double k); 
      virtual ~LinearParsimony();

      virtual double desiredFunc(int generation, Population *pop);
};

#endif
