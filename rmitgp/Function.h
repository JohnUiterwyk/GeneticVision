#ifndef _FUNCTION_H_
#define _FUNCTION_H_

/******************************************************************************
 Header file
 Class:        Function 
 Date created: 20/03/2002
 Written by:   Dylan Mawhinney

 The Function class is a sub class of class Node.
 A function is a program element which accepts some number of arguments 
******************************************************************************/

class GPConfig;

#include <string>
#include <vector>
#include "Node.h"

class Function : public Node
{
   private:
      Node **args;
      int *argReturnTypes;

   public:
      /***************************************************
       Constructor, first parameter is the return type
       of the function, second parameter is the number
       of arguments this function accepts, third parameter
       is the name of the function. Fourth parameter is
       the configuration object for this function.
      ****************************************************/ 
      Function(int type, int numArgs, string n, GPConfig *conf);

      /********************
       Copy Constructor
      ********************/
      //Function(Function &f);
      
      /*********************
       virtual destructor
      *********************/
      virtual ~Function();

      /**************************************************
       Sets the argument number N where N is in the range
       0-(maxArgs-1) to be the node n
      ***************************************************/
      void setArgN(int N, Node *n); 

      /***********************************************
       Returns a pointer to node N, where N is in the
       range 0 - (maxArgs-1)
      ***********************************************/
      Node* getArgN(int N) const;

      /***********************************************
       Sets the return type of child N, where N is
       in the range 0 - (maxArgs-1) to be type.
      ***********************************************/
      void setArgNReturnType(int N, int type);

      /********************************************
       Gets the return type of child N.
      ********************************************/
      int getArgNReturnType(int N) const;

      /*****************************************
       Pure virtual functions from class Node
      *****************************************/
      virtual int computeSize();
      virtual int computeDepth(int curDepth);

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

      /**********************************
       Prints this function to a string
      **********************************/
      virtual void print(string &s);

   protected:

};

#endif
