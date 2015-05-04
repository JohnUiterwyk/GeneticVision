#ifndef _RANDDOUBLE_H_
#define _RANDDOUBLE_H_

/******************************************************************************
 Header file
 Class:        RandDouble
 Date created: 21/03/2002
 Written by:   Dylan Mawhinney

 RandDouble is a derived class of , it represents a random double 
 valued terminal. It's value is determined at time of construction.
 
***************************************************************************/

class GPConfig;

#include <string>
#include "../../../rmitgp/Terminal.h"

class RandDouble : public Terminal 
{
   private:
      double value; //The data for this class 

   public:
      RandDouble(GPConfig *conf);
      explicit RandDouble(double initValue, GPConfig *conf);
      virtual ~RandDouble();

      static Terminal* generate(const string &name, GPConfig *conf);

      virtual void evaluate(ReturnData *out);  
      virtual void print(string &s);

      /**********************************
       Copies this terminal and returns
       a pointer to the copy.
      **********************************/
      virtual Node* copy();
   protected:

};

#endif
