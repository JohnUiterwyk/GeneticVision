/*************************************************************
 Definition 
 class:        ReturnData 
 Date created: 19/03/2002
 Written by:   Dylan Mawhinney

 See header file for details
**************************************************************/

#include "ReturnData.h"

ReturnData::ReturnData() : typeNum(-1)
{
}

ReturnData::~ReturnData()
{
}

int ReturnData::getTypeNum() const
{
   return typeNum;
}

void ReturnData::setTypeNum(int num)
{
   typeNum = num;
}
