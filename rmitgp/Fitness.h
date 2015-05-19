#ifndef _FITNESS_H_
#define _FITNESS_H_

/******************************************************************************
 Header file
 Class:        Fitness 
 Date created: 04/05/2002
 Written by:   Dylan Mawhinney

 The Fitness class is the class the evaluates the genetic programs
 in the population and assigns their fitness.
 All methods are pure virtual, subclasses must implement all methods.
******************************************************************************/
class GPConfig;

#include "GeneticProgram.h"

class Fitness 
{
   private:

   protected:
      GPConfig *config;

   public:
      //Constructor
      Fitness(GPConfig *conf); 
      virtual ~Fitness();

      /******************************
       Initialise the fitness class
      ******************************/
      virtual void initFitness() = 0;
    
      /*********************************************
       assignFitness evaluates a population of programs
       and assigns their raw fitnesses. 

       Pure virtual function. This class must be
       subclassed and evaluate must be implemented
       in the subclass.
      **********************************************/
      virtual void assignFitness(GeneticProgram* pop[], int popSize) = 0;

      /************************************************
       isBetter and isWorse return true if the first
       program is better or worse (respectively) than
       the second program.
      ************************************************/
      virtual bool isBetter(GeneticProgram* gp1, GeneticProgram* gp2) = 0;
      virtual bool isWorse(GeneticProgram* gp1, GeneticProgram* gp2) = 0;
      virtual bool isEqual(GeneticProgram* gp1, GeneticProgram* gp2) = 0;

      /******************************************************
       best() returns a double represnting the best possible  
       fitness attainable.
       worst() returns a double representing the worst
       possible fitness attainable.
      *******************************************************/
      virtual double best() = 0;
      virtual double worst() = 0;

      /************************************************
       solutionFound returns true if the solution has
       been found, false otherwise.

       Pure virtual function. The class must be 
       subclassed and solutionFound must be
       implemented in the subclass.
      **********************************************/
      virtual bool solutionFound(GeneticProgram* pop[], int popSize) = 0;
};

#endif
