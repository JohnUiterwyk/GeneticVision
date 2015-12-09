/*****************************************************************************
 Definition file
 Class:        DivideDouble 
 Date created: 04/08/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>

using namespace std;

#include "DivideDouble.h"
#include "../types/ReturnDouble.h"

#include <float.h>

DivideDouble::DivideDouble(GPConfig *conf) :
                          Function(ReturnDouble::TYPENUM, 2, "divide_double", conf)
{
   for (int i=0; i < maxArgs; i++)
   {
      setArgNReturnType(i, ReturnDouble::TYPENUM);   
   }
}

DivideDouble::~DivideDouble()
{
}

Function* DivideDouble::generate(const string &name, GPConfig *conf)
{
   if (name == "")
      return new DivideDouble(conf);
   else if (name == "divide_double")
      return new DivideDouble(conf);

   return NULL;     
}

void DivideDouble::evaluate(ReturnData *out)
{
   if (out->getTypeNum() != ReturnDouble::TYPENUM)
      throw string("DivideDouble::evaluate, incorrect ReturnData type");

   for (int i=0; i < maxArgs; i++)
   {
      if (getArgNReturnType(i) != getArgN(i)->getReturnType())
      {
         throw string("DivideDouble::evaluate Error argument has incorrect return type");
      }
   }

   ReturnDouble r1, r2;

   getArgN(0)->evaluate(&r1); 
   getArgN(1)->evaluate(&r2);

   double result;
   if (r2.getData() != 0.0)
      result = r1.getData() / r2.getData();
   else
      result = DBL_MAX / 2.0; 

   dynamic_cast<ReturnDouble *>(out)->setData(result); 
}

Node* DivideDouble::copy()
{
   int i;
   Function *tmp = new DivideDouble(config);

   if (tmp == NULL)
      throw string("DivideDouble::copy() Error, out of memory");

   for(i=0; i<getMaxArgs(); i++)
   { 
      tmp->setArgN(i, getArgN(i)->copy());
   }

   return dynamic_cast<Node *>(tmp);
}
