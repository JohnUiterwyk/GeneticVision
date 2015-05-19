/******************************************************************************
 Definition file
 Class:        NodeSet 
 Date created: 23/04/2002
 Written by:   Dylan Mawhinney
 
 The NodeSet class is based on code originally written by Peter Wilson.

 See header file for details.
******************************************************************************/

#include <string>

using namespace std;

#include "GPConfig.h"
#include "NodeVector.h"

FuncSet::FuncSet(GPConfig *conf) : config(conf), theSet(NULL)
{
   theSet = new NodeVector<Function>();
   theSet->setGPConfig(config);
}

TermSet::TermSet(GPConfig *conf) : config(conf), theSet(NULL)
{
   theSet = new NodeVector<Terminal>();
   theSet->setGPConfig(config);
}

FuncSet::~FuncSet()
{
   delete theSet;
}

TermSet::~TermSet()
{
   delete theSet;
}

void FuncSet::addNodeToSet(int returnType,
                  Function *(*generateFunction)(const string&, GPConfig *))
{
   NodeVector<Function>::Element elem;
   elem.returnType = returnType;
   elem.generateFunction = generateFunction;

   theSet->addElement(elem);
}

void TermSet::addNodeToSet(int returnType,
                  Terminal *(*generateFunction)(const string&, GPConfig *))
{
   NodeVector<Terminal>::Element elem;
   elem.returnType = returnType;
   elem.generateFunction = generateFunction;

   theSet->addElement(elem);
}

Function* FuncSet::getRandomNode()
{
   return theSet->getRandomElement();
}

Terminal* TermSet::getRandomNode()
{
   return theSet->getRandomElement();
}

Function* FuncSet::getRandomNode(int returnType)
{
   return theSet->getRandomTypedElement(returnType);
}

Terminal* TermSet::getRandomNode(int returnType)
{
   return theSet->getRandomTypedElement(returnType);
}

Node* FuncSet::getNodeByName(const string &name)
{
   Node *newNode;
   int i;

   for (i=0; i<theSet->size(); i++)
   {
      newNode = theSet->getElement(i)->generateFunction(name, config);   

      if (newNode != NULL)
      {
         return newNode;
      } 
   }      

   string error("FuncSet::getNodeByName Error could not build function for token ");
   error.append(name);
   throw error;

   return NULL;
}

Node* TermSet::getNodeByName(const string &name)
{
   Node *newNode;
   int i;

   for (i=0; i<theSet->size(); i++)
   {
      newNode = theSet->getElement(i)->generateFunction(name, config); 

      if (newNode != NULL)
      {
         return newNode;
      } 
   }      

   string error("TermSet::getNodeByName Error could not build terminal for token ");
   error.append(name);
   throw error;

   return NULL;
}

Node* FuncSet::getNodeByNumber(int position)
{
   Node *newNode;

   if(theSet->size() > position)
   {
      newNode = theSet->getElement(position)->generateFunction("", config);
      if (newNode != NULL)
      {
         return newNode;
      } 
   }

   string error("FuncSet::getNodeByNumber Error could not build function for the token");
   throw error;

   return NULL;
}

Node* TermSet::getNodeByNumber(int position)
{
   Node *newNode;

   if(theSet->size() > position)
   {
      newNode = theSet->getElement(position)->generateFunction("", config);
      if (newNode != NULL)
      {
         return newNode;
      } 
   }

   string error("TermSet::getNodeByNumber Error could not build function for the token");
   throw error;

   return NULL;
}

int FuncSet::getNodeReturnType(int position)
{
   NodeVector<Function>::Element *elem = theSet->getElement(position);
 
   if (elem != NULL)
      return elem->returnType;
   else
      return -1;
}

int TermSet::getNodeReturnType(int position)
{
   NodeVector<Terminal>::Element *elem = theSet->getElement(position);

   if (elem != NULL)
      return elem->returnType;
   else
      return -1;
}

FuncSet::funcGen FuncSet::getGenFunction(int position)
{
   NodeVector<Function>::Element *elem = theSet->getElement(position);

   if (elem != NULL)
      return elem->generateFunction;
   else
      return NULL;
}

TermSet::termGen TermSet::getGenFunction(int position)
{
   NodeVector<Terminal>::Element *elem = theSet->getElement(position);

   if (elem != NULL)
      return elem->generateFunction;
   else
      return NULL;
}

int FuncSet::size() const
{
   return theSet->size();
}

int TermSet::size() const
{
   return theSet->size();
}
