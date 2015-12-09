#ifndef _MULTDOUBLE_H_
#define _MULTDOUBLE_H_

/******************************************************************************
 Header file
 Class:        MultDouble 
 Date created: 04/08/2002
 Written by:   Dylan Mawhinney

 MultDouble is a sub class of Function, it accepts two Doubles as
 arguments and returns the product of it's two arguments.
******************************************************************************/

class GPConfig;

#include <string>
#include "../../../rmitgp/Function.h"

class MultDouble : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      MultDouble(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~MultDouble();

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
