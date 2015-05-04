#ifndef _CONSTANTPARSIMONY_H_
#define _CONSTANTPARSIMONY_H_
using namespace std;

/******************************************************************************
 Header file
 Class:        ConstantParsimony
 Date created: 15/09/2008
 Written by:   Brian Pinto

 Applies parsimony pressure such that the average size of the GP trees
 remains constant.
******************************************************************************/
#include "Population.h"
#include "Parsimony.h"

class Population;
class ConstantParsimony : public Parsimony
{
   private:
      double initmean;

   protected:

   public:
      //Constructor
      ConstantParsimony(double k); 
      virtual ~ConstantParsimony();

      virtual double desiredFunc(int generation, Population *pop);
};

#endif
