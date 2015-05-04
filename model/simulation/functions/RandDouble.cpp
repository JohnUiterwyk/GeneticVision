/******************************************************************************
 Definition file
 Class:        RandDouble
 Date created: 21/03/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdio> //for sprintf
#include <cstring>

using namespace std;

#include "../../../rmitgp/GPConfig.h"

#include "RandDouble.h"
#include "ReturnDouble.h"

RandDouble::RandDouble(GPConfig *conf) :
                           Terminal(ReturnDouble::TYPENUM, "drand", conf),
                           value(config->randomNumGenerator->randReal() * 100.0)
{
}

RandDouble::RandDouble(double initValue, GPConfig *conf) :
                               Terminal(ReturnDouble::TYPENUM, "drand", conf),
                               value(initValue)
{
}

RandDouble::~RandDouble()
{
}

Terminal* RandDouble::generate(const string &name, GPConfig *conf)
{
   double tmpValue;
   string tmpName("drand");
   char copy[20];

   strcpy(copy, name.c_str());

   if (name == "")
      return new RandDouble(conf);
#ifdef OLD_GCC 
   //Older versions of gcc 2.9X shipped with a c++ library which
   //had mistakes in implementation of some methods string::compare 
   //has it's parameters in the wrong order.

   else if (name.compare(tmpName, 0, tmpName.size()) == 0)
#else
   else if (name.compare(0, tmpName.size(), tmpName) == 0)
#endif
   {
      sscanf(copy, "drand%lf", &tmpValue);
      return new RandDouble(tmpValue, conf);
   }

   return NULL;      
}

void RandDouble::evaluate(ReturnData *out)  
{
   if (out->getTypeNum() != (ReturnDouble::TYPENUM))
      throw string("RandDouble::evaluate, incorrect ReturnData type");

   dynamic_cast<ReturnDouble *>(out)->setData(value);
}

void RandDouble::print(string &s)
{
   char str[100]; 

   sprintf(str, "%s%f", getName().c_str(), value);
   s.append(str); 
}

Node* RandDouble::copy()
{
   Node *tmp = new RandDouble(value, config);

   if (tmp == NULL)
      throw string("RandDouble::copy() Error, out of memory");

   return tmp;
}
