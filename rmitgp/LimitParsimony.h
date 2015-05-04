#ifndef _LIMITPARSIMONY_H_
#define _LIMITPARSIMONY_H_
using namespace std;

/******************************************************************************
 Header file
 Class:        LimitParsimony
 Date created: 15/09/2008
 Written by:   Brian Pinto

 Applies parsimony pressure such that the size of the GP trees is strictly
 limited to a given size.
******************************************************************************/
#include "Population.h"
#include "Parsimony.h"

class Population;
class LimitParsimony : public Parsimony
{
   private:
      int ck;
		int sizeLimit;
   protected:

   public:
      //Constructor
      LimitParsimony(double k, int limit); 
      virtual ~LimitParsimony();

      virtual double desiredFunc(int generation, Population *pop);
};

#endif
