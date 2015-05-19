#ifndef _RETURNDOUBLE_H_
#define _RETURNDOUBLE_H_

/******************************************************************************
 Header file
 Class:        ReturnDouble
 Date created: 20/03/2002
 Written by:   Dylan Mawhinney

 ReturnDouble is a derived class of ReturnData, it represents a double 
 returned from a GP node (see Node class).
 
***************************************************************************/

#include "../../../rmitgp/ReturnData.h"

class ReturnDouble : public ReturnData
{
   private:
      double data; //The data for this class 

      /***********************************************
       This method sets the typeNum to be the typeid
       of the class. 
      ************************************************/ 
      virtual void initTypeNum(); 

   public:
      static const int TYPENUM;

      ReturnDouble();
      virtual ~ReturnDouble();

      /************************
       Set the data to be num
      ************************/
      void setData(double num);
     
      /****************************
       Get the data of this class 
      ****************************/
      double getData() const;
     
   protected:

};

#endif
