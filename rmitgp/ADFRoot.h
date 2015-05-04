#ifndef _ADFROOT_H_
#define _ADFROOT_H_

/******************************************************************************
 Header file
 Class:        ADFRoot
 Date created: 28/12/2003
 Written by:   Dharma Teja Nanduri

 ADFRoot is a function which accepts two argument. First arguement is 
 the ADF and the second is the main tree. It will
 be the root of the tree with ADF.
******************************************************************************/

#include <string>
#include "Function.h"
#include "ADFProgramGenerator.h"

class ADFRoot : public Function
{
   private:
      static int last;
      /* Determines the number of ADFs. Currently there is only support 
         for 1 ADF, but this is present for scalability  */
      int noofADFs;
   public:

     /*************
       Constructor.
      **************/
      ADFRoot(GPConfig *conf, int expectedReturnType);

      /*********************
       virtual destructor
      *********************/
      virtual ~ADFRoot();

      static Function* generate(const string &name, GPConfig *conf);

      /************************************* 
       Adds the subtree rooted at this node
       to the vector. 
      *************************************/
      virtual void addToVector(vector<Node *> &vec);

      /************************************* 
       Adds the subtree rooted at this node
       to the vector if this function 
       returns the type typeNum. 
      *************************************/
      virtual void addToVector(vector<Node *> &vec, int typeNum);

      /********************
       Evaluate function
      ********************/
      virtual void evaluate(ReturnData *out);

      /**********************
         Evaluates the ADF
      **********************/
      virtual void evaluateADF(ReturnData *out);

      /***********************************
       Copies this function and it's
       arguments and returns a pointer to
       the new copy.
      ***********************************/
      virtual Node* copy();

   protected:
};

#endif
