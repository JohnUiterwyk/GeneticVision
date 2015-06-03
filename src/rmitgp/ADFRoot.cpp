/******************************************************************************
 Definition file
 Class:        ADFRoot
 Date created: 28/12/2003
 Written by:   Dharma Teja Nanduri

 See header file for details
******************************************************************************/

#include <string>
using namespace std;

#include "GPConfig.h"
#include "ADFRoot.h"

int ADFRoot::last = 0;

ADFRoot::ADFRoot(GPConfig *conf, int expectedReturnType): Function(expectedReturnType, 2, "ADFRoot", conf)
{
   int i;
   for (i=0; i < maxArgs; i++)
   {
      setArgNReturnType(i, expectedReturnType);   
   }
   noofADFs = 1;
}

ADFRoot::~ADFRoot()
{
}

Function* ADFRoot::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "ADFRoot")
      return new ADFRoot(conf, conf->funcSet.getNodeReturnType(0));

   return NULL;     
}

/* This method evaluates the main sub-tree or the result producing branch */
void ADFRoot::evaluate(ReturnData *out)
{
   getArgN(1)->evaluate(out); 
}

/* This method evaluates the ADF */
void ADFRoot::evaluateADF(ReturnData *out)
{
   getArgN(0)->evaluate(out); 
}

Node* ADFRoot::copy()
{
   int i;
   Function *tmp = new ADFRoot(config, getReturnType());

   if (tmp == NULL)
      throw string("ADFRoot::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   {
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}

//Adds the current node to the vector
void ADFRoot::addToVector(vector<Node *> &vec)
{
   ADFRoot::last = (ADFRoot::last + 1) % 2;
   getArgN(ADFRoot::last)->addToVector(vec);
}

//Adds the current node to the vector if this function returns
//the type typeNum
void ADFRoot::addToVector(vector<Node *> &vec, int typeNum)
{
   getArgN(ADFRoot::last)->addToVector(vec, typeNum);
}

