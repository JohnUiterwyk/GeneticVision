/******************************************************************************
 Definition file
 Class:        PlusDouble 
 Date created: 22/03/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>

using namespace std;

#include "PlusDouble.h"
#include "ReturnDouble.h"

PlusDouble::PlusDouble(GPConfig *conf) :
                          Function(ReturnDouble::TYPENUM, 2, "d+", conf)
{
   for (int i=0; i < maxArgs; i++)
   {
      setArgNReturnType(i, ReturnDouble::TYPENUM);   
   }
}

PlusDouble::~PlusDouble()
{
}

Function* PlusDouble::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new PlusDouble(conf);
   else if (name == "d+")
      return new PlusDouble(conf);

   return NULL;     
}

void PlusDouble::evaluate(ReturnData *out)
{
   if (out->getTypeNum() != ReturnDouble::TYPENUM)
      throw string("PlusDouble::evaluate, incorrect ReturnData type");

   for (int i=0; i < maxArgs; i++)
   {
      if (getArgNReturnType(i) != getArgN(i)->getReturnType())
      {
         throw string("PlusDouble::evaluate Error argument has incorrect return type");
      }
   }

   ReturnDouble r1, r2;

   getArgN(0)->evaluate(&r1); 
   getArgN(1)->evaluate(&r2);

   double result = r1.getData() + r2.getData();

   dynamic_cast<ReturnDouble *>(out)->setData(result); 
}

Node* PlusDouble::copy()
{
   int i;
   Function *tmp = new PlusDouble(config);

   if (tmp == NULL)
      throw string("PlusDouble::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   { 
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
