/******************************************************************************
 Definition file
 Class:        Fitness 
 Date created: 16/09/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

using namespace std;

class GPConfig;
#include "GPConfig.h"
#include "Fitness.h"

Fitness::Fitness(GPConfig *conf) : config(conf)
{
}

Fitness::~Fitness()
{
}
