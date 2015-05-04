/******************************************************************************
 Definition file
 Class:        ADFunction
 Date created: 24/12/2003
 Written by:   Dharma Teja Nanduri

 See header file for details
******************************************************************************/

#include <string>
using namespace std;

#include "GPConfig.h"
#include "ADFunction.h"
#include "ADFRoot.h"

ADFunction::ADFunction(GPConfig *conf) : Function(conf->funcSet.getNodeReturnType(0), 0, "ADFunction", conf)
{
}

ADFunction::~ADFunction()
{
}

Function* ADFunction::generate(const string &name, GPConfig *conf)
{
   if (name == "" || name == "ADFunction")
      return new ADFunction(conf);

   return NULL;     
}

void ADFunction::evaluate(ReturnData *out)
{
   ADFRoot * tmpRoot = dynamic_cast<ADFRoot *>(Node::getRootNode());
   tmpRoot->evaluateADF(out);
}

Node* ADFunction::copy()
{
   Function *tmp = new ADFunction(config);

   if (tmp == NULL)
      throw string("ADFunction::copy() Error, out of memory");

   for(int i=0; i<getMaxArgs(); i++)
   {
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
