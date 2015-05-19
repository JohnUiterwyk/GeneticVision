#ifndef _GPCONFIG_H_
#define _GPCONFIG_H_

/******************************************************************************
 Header file
 Class:        GPConfig 
 Date created: 13/09/2002
 Written by:   Dylan Mawhinney

 The GPConfig is a class which contains a configuration for a particular
 run. Basically it stores pointer to objects which can be customized
 by the user. For example, the user could choose to write their own
 random number generator. To do this they would make a subclass of the
 Random class, create an instance of their new class and set the 
 randomNumGenerator member below to point to the new instance.
 That way any classes that need a random number would use the
 randomNumGenerator to generate random numbers. 
******************************************************************************/

#include "Random.h"
//#include "ProgramGenerator.h"
#include "Crossover.h"
#include "Mutation.h"
#include "Selection.h"
#include "Fitness.h"
#include "NodeSet.h"
#include "Parsimony.h"
#include "CovariantTarpeian.h" // QCS 20120917
#include "DynamicDepthLimit.h" // QCS 20120930

class DynOpEq;
class ProgramGenerator;
class Parsimony;
class DynamicDepthLimit;

class GPConfig
{
   private:

   protected:

   public:

      int numObjectives;

      //The minimum and maximum depth for this configuration
      int minDepth;
      int maxDepth;
     
      //The sets of available functions and terminals
      FuncSet funcSet;
      TermSet termSet;

      Random *randomNumGenerator;          
      Crossover *crossoverOperator; 
      Mutation *mutationOperator;
      Selection *selectionOperator;
      Fitness *fitnessObject;
      ProgramGenerator *programGenerator;

      Parsimony *parsimonypres; //Added for parsimony pressure functionality
      CovariantTarpeian * tarpeian; // Added for Tarpeian Selection functionality - QCS 20120917
      DynamicDepthLimit * ddl; // Added to support dynamic depth limiting - QCS 20120930

      GPConfig();

      /*******************
       Copy Constructor
      *******************/
      GPConfig(GPConfig &c);

      virtual ~GPConfig();

      //This function does a default initialisation of the objects
      //above, it's usefull if you haven't used your own customized versions
      //of operators and just want the default ones.
      //DOES NOT set programGenerator or fitnessObject.
      virtual void defaultInit();

      /*Deletes all the objects above*/
      void cleanUpObjects();

      void activateTarpeian(Fitness * fo);
      void activateDDL(Fitness * fo);
};

#endif
