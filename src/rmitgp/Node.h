#ifndef _NODE_H_
#define _NODE_H_

/******************************************************************************
 Header file
 Class:        Node
 Date created: 18/03/2002
 Written by:   Dylan Mawhinney

 Adapted from code originally written by Peter Wilson.

 The Node class is an abstract base class to represent program elements
 in a genetic program. A program element can be a function or a terminal.

 The returnType attribute is the type number of the return type for 
 the current node (see class ReturnData)

 The maxArgs attribute is the maximum number of arguments this 
 node can accept (0 for terminals)

 The depth attribute is the depth of the node in the tree.

 The parent attribute is a pointer to the parent of the node in 
 the program tree.

******************************************************************************/

class GPConfig;

#include <string>
#include <vector>
#include "ReturnData.h"

using namespace std;

class Node
{
   private:
      int returnType; //The type number of the return type for this node
      int depth;      //The depth of this node in the program tree
      Node *parent;   //The parent of this node in the program tree

      string name;    //How this node gets printed out in the program code

   protected:
      int maxArgs;   //The maximum number of arguments this node
                     //can accept

      GPConfig *config; //Configuration object;

   public:
      /******************************************************
        Three argument constructor, requires the type number 
        of the return type of this node, and the number
        of arguments the node accepts. 
      *******************************************************/ 
      Node(int type, int numArgs, string name, GPConfig *conf);

      /*************************************
       Copy Comstructor
       The parent of the old node n is set
       as the parent for the new node.
      *************************************/
      Node(Node &n);

      /*********************
       virtual destructor
      *********************/
      virtual ~Node();

      /***************************************************
       Pure virtual function evaluate
       Must be overriden in derived class.

       Evaluates the node and returns the result through
       the parameter "out".
      ***************************************************/
      virtual void evaluate(ReturnData *out) = 0;

      /************************************
       Gets the return type for this node
      *************************************/
      int getReturnType() const;

      /************************************
       Gets the maximum number of arguments
       this node can accept
      *************************************/
      int getMaxArgs() const;

      /**********************************
       Sets the depth of this node
      **********************************/
      void setDepth(const int d);

      /*********************************
       Gets the depth of this node
      *********************************/
      int getDepth() const;

      /*********************************
       Get the name of this node
      *********************************/
      string getName() const;

      /********************************
       Get the parent of this node
      *********************************/
      Node * getParent() const;

      /********************************
       Get the root node of this tree
      *********************************/
      Node * getRootNode() const;

      /********************************
       Sets the parent of this node
      ********************************/
      void setParent(Node *n);

      /**********************************
       Computes the size of this program
       number of terminals + number of
       functions
      **********************************/
      virtual int computeSize() = 0;

      /************************************
       Computes the depth of this program.
       Returns maximum nested depth 
      ************************************/
      virtual int computeDepth(int curDepth) = 0;

      /*************************************
       Adds the subtree rooted at this node
       to the vector. 
      *************************************/
      virtual void addToVector(vector<Node *> &vec) = 0;

      /*************************************
       Adds the subtree rooted at this node
       to the vector if it returns the type
       typeNum. 
      *************************************/
      virtual void addToVector(vector<Node *> &vec, int typeNum) = 0;

      /*********************************
       Generate a string representation
       of this node
       Must be overridden in the
       derived class.
      *********************************/
      virtual void print(string &s) = 0;

      /****************************************
       Copy the subtree starting at this point
       and return a pointer to the new tree.

       Must be overridden in the derived
       class.
      *****************************************/
      virtual Node* copy() = 0;

};

#endif
