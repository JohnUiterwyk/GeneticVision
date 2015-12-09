/******************************************************************************
 Definition file
 Class:        MinusDouble 
 Date created: 04/08/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>

using namespace std;

#include "MinusDouble.h"
#include "../types/ReturnDouble.h"

MinusDouble::MinusDouble(GPConfig *conf) :
                            Function(ReturnDouble::TYPENUM, 2, "minus_double", conf)
{
   for (int i=0; i < maxArgs; i++)
   {
      setArgNReturnType(i, ReturnDouble::TYPENUM);   
   }
}

MinusDouble::~MinusDouble()
{
}

Function* MinusDouble::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new MinusDouble(conf);
   else if (name == "minus_double")
      return new MinusDouble(conf);

   return NULL;     
}

void MinusDouble::evaluate(ReturnData *out)
{
   if (out->getTypeNum() != ReturnDouble::TYPENUM)
      throw string("MinusDouble::evaluate, incorrect ReturnData type");

   for (int i=0; i < maxArgs; i++)
   {
      if (getArgNReturnType(i) != getArgN(i)->getReturnType())
      {
         throw string("MinusDouble::evaluate Error argument has incorrect return type");
      }
   }

   ReturnDouble r1, r2;

   getArgN(0)->evaluate(&r1); 
   getArgN(1)->evaluate(&r2);

   double result = r1.getData() - r2.getData();

   dynamic_cast<ReturnDouble *>(out)->setData(result); 
}

Node* MinusDouble::copy()
{
   int i;
   Function *tmp = new MinusDouble(config);

   if (tmp == NULL)
      throw string("MinusDouble::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   { 
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
