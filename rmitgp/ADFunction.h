#ifndef _ADFUNCTION_H_
#define _ADFUNCTION_H_

/******************************************************************************
 Header file
 Class:        ADFunction
 Date created: 24/12/2003
 Written by:   Dharma Teja Nanduri

 ADFunction is a function which represents the call to the ADF from 
 the main tree.
******************************************************************************/

#include <string>
#include "Function.h"

class ADFunction : public Function
{
   private:

   public:
      /*************
       Constructor.
      **************/
      ADFunction(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~ADFunction();

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
