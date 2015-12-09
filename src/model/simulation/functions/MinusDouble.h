#ifndef _MINUSDOUBLE_H_
#define _MINUSDOUBLE_H_

/******************************************************************************
 Header file
 Class:        MinusDouble 
 Date created: 04/08/2002
 Written by:   Dylan Mawhinney

 MinusDouble is a sub class of Function, it accepts two Doubles as
 arguments and returns the difference between it's two arguments.
******************************************************************************/
class GPConfig;

#include <string>
#include "../../../rmitgp/Function.h"

class MinusDouble : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      MinusDouble(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~MinusDouble();

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
