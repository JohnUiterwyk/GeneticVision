#ifndef _RETURNDATA_H_
#define _RETURNDATA_H_

/******************************************************************************
 Header file
 Class:        ReturnData 
 Date created: 19/03/2002
 Written by:   Dylan Mawhinney

 The ReturnData class is an abstract base class used by Genetic Program
 nodes to return data to their parent node. (See class Node)

 The typeNum is the typeID of the class and is used to uniquely 
 identify the return type (and argument types) of functions and
 terminals.

 Any derived class should include any data members needed to store the
 return data, and methods to get and set the data members. 

 The derived class should also override the setTypeNum method and set
 the typeNum to be the typeid of the new class.

 See class ReturnInt and ReturnDouble for examples. 
***************************************************************************/

class ReturnData
{
   private:
      int typeNum; //The typeid of the class

      /***********************************************
       This method sets the typeNum to be the typeid
       of the class. It should be implemented by
       any derived class.
      ************************************************/ 
      virtual void initTypeNum() = 0;

   public:

      ReturnData();
      virtual ~ReturnData();

      /*****************************************
       Returns the typeNum of this class
      *****************************************/ 
      int getTypeNum() const;

   protected:
      /*************************
       Sets the typeNum to num 
      **************************/
      void setTypeNum(int num);
};

#endif
