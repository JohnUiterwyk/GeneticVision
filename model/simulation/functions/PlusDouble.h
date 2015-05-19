#ifndef _PLUSDOUBLE_H_
#define _PLUSDOUBLE_H_

/******************************************************************************
 Header file
 Class:        PlusDouble 
 Date created: 22/03/2002
 Written by:   Dylan Mawhinney

 PlusDouble is a sub class of Function, it accepts two Doubles as
 arguments and returns the addition of it's two arguments.
******************************************************************************/

class GPConfig;

#include <string>
#include "Function.h"

class PlusDouble : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      PlusDouble(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~PlusDouble();

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
