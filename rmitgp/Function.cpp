/******************************************************************************
 Definition file
 Class:        Function 
 Date created: 20/03/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <cstdlib>
#include <string>
using namespace std;

class GPConfig;
#include "Function.h"
#include "GPConfig.h"

//Constructor
Function::Function(int type, int numArgs, string n, GPConfig *conf) :
               Node(type, numArgs, n, conf), args(NULL), argReturnTypes(NULL)
{
   //If the number of arguments this function accepts is greater than zero
   //then we need to allocate the space to store pointers to the arguments
   //and to store their return types. 
   if (numArgs > 0)
   {   
      args = new Node* [numArgs];   
      argReturnTypes = new int [numArgs];

      if (args == NULL || argReturnTypes == NULL)
         throw string("Out of memory");

      for(int i=0; i<numArgs; i++)
      {
         args[i] = NULL;  
         argReturnTypes[i] = -1;
      } 
   }
}

//Destructor
Function::~Function() 
{
   if (args != NULL)
      delete [] args;

   if (argReturnTypes != NULL)
      delete [] argReturnTypes;
}

//Set the Nth argument
void Function::setArgN(int N, Node *n) 
{
   if (N >= maxArgs || N < 0)
      throw string("Function::setArgN, Invalid argument number");

   if (n == NULL)
      throw string("Function::setArgN, Node is NULL");
   
   if (n->getReturnType() != argReturnTypes[N])
      throw string("Function::setArgN, Incorrect return type"); 

   args[N] = n;
   n->setParent(this); 
}

//Get the Nth argument
Node* Function::getArgN(int N) const
{
   if (N >= maxArgs || N < 0)
      throw string("Function::getArgN, Invalid argument number");

   return args[N];
}

//Set the return type of the Nth argument
void Function::setArgNReturnType(int N, int type)
{
   if (N >= maxArgs || N < 0)
      throw string("Function::setArgNReturnType, Invalid argument number");

   if (type <= 0)
      throw string("Function::setArgNReturnType, Invalid return type");

   argReturnTypes[N] = type;
}

//Get the return type of the Nth argument
int Function::getArgNReturnType(int N) const
{
   if (N >= maxArgs || N < 0)
      throw string("Function::getArgNReturnType, Invalid argument number");

   return argReturnTypes[N];
}

//Recursively compute the size of the subtree rooted at this
//function by calling computeSize for each argument
int Function::computeSize()
{
   int size=0;

   for(int i=0; i<maxArgs; i++)
   {
      size += args[i]->computeSize();
   }

   return size + 1;
}

//Recursively compute the depth of the subtree rooted at this
//function by calling computeDepth for each argument.
int Function::computeDepth(int curDepth)
{
   setDepth(curDepth + 1);

   int retDepth = 0;
   int maxDepth = 0;

   for (int i=0; i<maxArgs; i++)
   {
      if ((retDepth = args[i]->computeDepth(getDepth())) > maxDepth)
         maxDepth = retDepth;
   }

   return maxDepth + 1;
}

//Adds the current node to the vector
void Function::addToVector(vector<Node *> &vec)
{
   vec.push_back(this);

   for (int i=0; i<maxArgs; i++)
   {
      args[i]->addToVector(vec);
   }
}

//Adds the current node to the vector iff this function returns
//the type typeNum
void Function::addToVector(vector<Node *> &vec, int typeNum)
{
   if (getReturnType() == typeNum)
      vec.push_back(this);

   for (int i=0; i<maxArgs; i++)
   {
      args[i]->addToVector(vec, typeNum);
   }
}

//Print this function to the string s
void Function::print(string &s)
{
   s.append("(" + getName());

   for (int i = 0; i < maxArgs; i++)
   {
      s.append(" ");
      args[i]->print(s); 
   }

   s.append(")");
}
