/******************************************************************************
 Definition 
 Class:        ReturnDouble
 Date created: 20/03/2002
 Written by:   Dylan Mawhinney

 See header file for details
***************************************************************************/

#include "ReturnDouble.h"

//Initialise static data

const int ReturnDouble::TYPENUM=2;

ReturnDouble::ReturnDouble() : ReturnData(), data(0.0)
{
   initTypeNum();
}

ReturnDouble::~ReturnDouble()
{
}

void ReturnDouble::initTypeNum()
{
   setTypeNum(ReturnDouble::TYPENUM);
} 

void ReturnDouble::setData(double num)
{
   data = num;
}

double ReturnDouble::getData() const
{
   return data;
}
