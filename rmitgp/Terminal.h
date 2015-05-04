#ifndef _TERMINAL_H_
#define _TERMINAL_H_

/******************************************************************************
 Header file
 Class:        Terminal 
 Date created: 21/03/2002
 Written by:   Dylan Mawhinney

 A terminal is a sub class of class Node.

 It is still an abstract class as it does not implement the evaluate 
 function.

 It is a program element that accepts no arguments (a leaf node). 
******************************************************************************/
class GPConfig;

#include <vector>
#include "Node.h"

class Terminal : public Node 
{
   private:

   protected:

   public:
      /***************************************************
        One argument constructor, requires the type number 
        of the return type for this Terminal, the 
        name of this terminal, and the configuration
        object.
      ****************************************************/ 
      Terminal(int type, string n, GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Terminal();

      /***************************************
       Pure virtual functions from Node class
      ***************************************/
      virtual int computeSize();
      virtual int computeDepth(int curDepth);

      /************************************* 
       Adds the subtree rooted at this node
       to the vector. 
      *************************************/
      virtual void addToVector(vector<Node *> &vec);

      /************************************* 
       Adds the subtree rooted at this node
       to the vector if this terminal
       return the type typeNum. 
      *************************************/
      virtual void addToVector(vector<Node *> &vec, int typeNum);

      /********************************
       Print the terminal to a string
      ********************************/
      virtual void print(string &s);
};

#endif
