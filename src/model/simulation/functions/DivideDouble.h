#ifndef _DIVIDEDOUBLE_H_
#define _DIVIDEDOUBLE_H_

/******************************************************************************
 Header file
 Class:        DivideDouble 
 Date created: 22/03/2002
 Written by:   Dylan Mawhinney

 DivideDouble is a sub class of Function, it accepts two Doubles as
 arguments and returns argument 0 divided by argument 1. 
******************************************************************************/

class GPConfig;

#include <string>
#include "../../../rmitgp/Function.h"

class DivideDouble : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      DivideDouble(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~DivideDouble();

      static Function* generate(const string &name, GPConfig *conf);

      /********************
       Evaluate function
      ********************/
      virtual void evaluate(ReturnData *out);

      /***********************************
       Copies this function and it's 
       arguments and returns a pointer to
       the new copy.
      ***********************************/
      virtual Node* copy();

   protected:

};

#endif
