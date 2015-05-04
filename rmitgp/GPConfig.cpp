/******************************************************************************
 Header file
 Class:        GPConfig 
 Date created: 13/09/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <cstdlib>

using namespace std;

#include "GPConfig.h"
#include "NodeSet.h"
#include "ProgramGenerator.h"

/* Modified by Mohammad to initialize the number of objectives to one */
GPConfig::GPConfig() : numObjectives(1), minDepth(0), maxDepth(0), 
                       funcSet(this), termSet(this),
                       randomNumGenerator(NULL), 
                       crossoverOperator(NULL), mutationOperator(NULL),
                       selectionOperator(NULL), fitnessObject(NULL),
                       programGenerator(NULL), parsimonypres(NULL), tarpeian(NULL) // QCS 20120917
                       , ddl(NULL) // QCS 20121012
{
}

/* Copy Constructor
   Makes a complete copy of the function set and the terminal set too */
GPConfig::GPConfig(GPConfig &c) : 
                       minDepth(c.minDepth), maxDepth(c.maxDepth),
                       funcSet(this), termSet(this),
                       randomNumGenerator(c.randomNumGenerator),
                       crossoverOperator(c.crossoverOperator), mutationOperator(c.mutationOperator),
                       selectionOperator(c.selectionOperator), fitnessObject(c.fitnessObject),
                       programGenerator(c.programGenerator),
                       parsimonypres(c.parsimonypres), tarpeian(c.tarpeian) // QCS 2012091
                       , ddl(c.ddl) //  QCS 20121012
{
   int i;
   Node *tmp;
   if (c.funcSet.size() > 0)
   {
      for (i=0;i<c.funcSet.size();i++)
      {
         tmp = c.funcSet.getNodeByNumber(i);
         funcSet.addNodeToSet(tmp->getReturnType(),c.funcSet.getGenFunction(i));
      }
   }

   if (c.termSet.size() > 0)
   {
      for (i=0;i<c.termSet.size();i++)
      {
         tmp = c.termSet.getNodeByNumber(i);
         termSet.addNodeToSet(tmp->getReturnType(),c.termSet.getGenFunction(i));
      }
   }
}

GPConfig::~GPConfig()
{
   cleanUpObjects();
}

//Initialises the random number generator, the crossover operator,
//the mutation operator, and the selection operator to the standard
//base objects.
void GPConfig::defaultInit()
{
   randomNumGenerator = new Random();
   crossoverOperator = new Crossover();
   mutationOperator = new Mutation();
   selectionOperator = new Selection(); 
}

//Delete any objects which were allocated.
void GPConfig::cleanUpObjects()
{
   if (randomNumGenerator != NULL)
   {
      delete randomNumGenerator;
      randomNumGenerator = NULL;
   }

   if (programGenerator != NULL)
   {
      delete programGenerator;
      programGenerator = NULL;
   }

   if (crossoverOperator != NULL)
   {
      delete crossoverOperator;
      crossoverOperator = NULL;
   }

   if (mutationOperator != NULL)
   {
      delete mutationOperator;
      mutationOperator = NULL;
   }

   if (selectionOperator != NULL)
   {
      delete selectionOperator;      
      selectionOperator = NULL;      
   }

   if (fitnessObject != NULL)
   {
      delete fitnessObject;
      fitnessObject = NULL;
   }

   if (parsimonypres != NULL)
   {
      delete parsimonypres;
      parsimonypres = NULL;
   }

   // QCS 20120919
   if (tarpeian != NULL)
   {
	   delete tarpeian;
	   tarpeian = NULL;
   }

   // QCS 20120930
   if (ddl != NULL)
   {
	   delete ddl;
	   ddl = NULL;
   }
}

void GPConfig::activateTarpeian(Fitness * fo) {
	cout << "Activating Tarpeian" << endl;
	tarpeian = new CovariantTarpeian(fo);
}

void GPConfig::activateDDL(Fitness * fo) {
	cout << "Activating Dynamic Depth Limit" << endl;
	ddl = new DynamicDepthLimit(this, fo);
}

