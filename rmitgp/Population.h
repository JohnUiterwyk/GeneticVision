#ifndef _POPULATION_H_
#define _POPULATION_H_

/******************************************************************************
 Header file
 Class:        Population 
 Date created: 10/04/2002
 Written by:   Dylan Mawhinney

 Adapted from code originally written by Peter Wilson.

 A population is a collection of genetic programs (individuals) that is
 evolved using genetic operators (crossover mutation etc). 

******************************************************************************/

#include <iostream>
#include <fstream>

#include "GeneticProgram.h"
#include "Mutation.h"
#include "Crossover.h"
#include "Selection.h"
#include "GPConfig.h"
#include "Parsimony.h"

class Parsimony;

class Population 
{
   /*private:*/
   protected:
      GeneticProgram **pop; //The population, and array of pointers to programs

      /*********************************************************************
       The depth limit and the minimum depth for this population.
       Technically there is not limit to how deep the depthLimit can be,
       however if your limit is set too deep you may run out of memory on
       your machine. There are also other factors to consider, such as
       the arity of your functions (are your trees fat or skinny), and
       the population size.
      *********************************************************************/
      int depthLimit;  
      int initdepthLimit;  
      int minDepth;


      //Number of evaluations carried out so far
      long int evaluations;

      //Number of individuals in this population
      int numIndividuals;

      //Used for Decimation
      int initNumIndividuals;
      int numGenerationBeforeDecimation;
      int fallPerGeneration;

      //Should Decimation be performed?
      bool performDecimation;

      //Has the population been sorted yet?
      bool popSorted;

      //The best, worst, and average fitness
      double bestFitness;
      double worstFitness;
      double avgFitness;
      double avgNormFitness;

      double avgDepth;
      double avgSize;
      
      double stdDevSize; // used in covariance-based bloat control strategies - QCS 10.09.2010

      //The return type for all the programs in this population
      int returnType;

      //Below are the member variables for mutation, crossover, and
      //elitism rates.
      double mutationRate;
      int numForMutation;

      double crossoverRate;
      int numForCrossover;

      double elitismRate; 
      int numForElitism;

      //What generation number are we currently processing.
      int generationNumber;

      //The loggingFrequency stores how often to write out 
      //generation files.
      int loggingFrequency;
      bool useCompression;  //Compress gen files

      ofstream logFile;


   /*protected:*/

      GPConfig *config; //The configuration of this Population

      /*****************************************
       Get the population array from this 
       population. Be careful what you do
       with it once you have it.
      *****************************************/
      GeneticProgram** getPopulation() const;

      /*****************************************
       Set the population. Make sure the array
       passed in is the same size as the current
       population. 
      ******************************************/
      void setPopulation(GeneticProgram **newPop, int size);

      /****************************************
       Write a log of the current statistics
      ****************************************/
      virtual void writeLog();

      /***************************
       Compress the file
      ***************************/
      virtual void compressFile(char *fileName);

   public:
      double parscoeff;
      /***********************************
       Constructor, must specify the
       size (number of individuals)
       of the population, a log filename
       and a pointer to a GPConfig object
      ***********************************/
      Population(int size, const char *logFileName, GPConfig *conf);

      /****************************************
       Constructor, must specify the
       size (number of individuals),
	   initSize (initial number of individuals
	   before decimation is performed
       of the population, a log filename
       and a pointer to a GPConfig object
      *****************************************/
      Population(int size, int initSize, const char *logFileName, GPConfig *conf);

	  /******************************
	   Copy Constructor
     ******************************/
      Population(Population &p);

      virtual ~Population();

      /**********************************************
	   Get and Set the number of generation to evolve 
      before decimation
      ***********************************************/
      int getNumGenerationBeforeDecimation() const;
      void setNumGenerationBeforeDecimation(int num);

      /******************************************
       Get an individual program from the
       population.
      ******************************************/
      GeneticProgram* getIndividual(int individual);

      /*******************************************
       Get and set the current generation number
      *******************************************/
      int getGenerationNumber() const;
      void setGenerationNumber(int num);

      /*********************
       Set the depth limit
       and minimum depth
      *********************/
      void setDepthLimit(int d);
      void setinitDepthLimit(int d);
      void setMinDepth(int d);

      /*****************************
       Generate initial population
      ******************************/
      virtual void generateInitialPopulation(); 

      /****************************************
       Check the rates for mutation crossover
       and elitism.
      ****************************************/
      virtual void correctRates();

      /******************************************
       Assign fitness for the current population
      ******************************************/
      virtual void assignFitness();

      /****************************************
       Sort the population based on fitness.
      *****************************************/
      virtual void sortPopulation();

      /******************************************
       Evolve this population for numGenerations
       generations.
       Returns true if the solution was found.
      *******************************************/
      virtual bool evolve(int numGenerations);

      /**************************
       Do the next generation
      **************************/
      virtual void nextGeneration(); 

      /*********************************
       Adjust fitnesses.
       Overide this method if you need
       to adjust the raw fitnesses in
       any way (eg for selection).
      **********************************/ 
      virtual void adjustFitness();

      /**********************************************
       Set and get the number of individuals in this
       population.  WARNING, see implementation of
       setNumIndividuals for details of the side
       effects of resizing a population.
      **********************************************/
      virtual void setNumIndividuals(int num);
      int getNumIndividuals() const;

      /***********************************
       Set and get the return type of
       the programs in this population.
      ***********************************/
      void setReturnType(int type);
      int getReturnType() const;

      /************************************
       Mutation rates
      ************************************/
      void setMutationRate(double rate);
      double getMutationRate(); 
      void setNumForMutation(int num);
      int getNumForMutation();

      /************************************
       Crossover rates
      ************************************/
      void setCrossoverRate(double rate);
      double getCrossoverRate(); 
      void setNumForCrossover(int num);
      int getNumForCrossover();

      /************************************
       Elitism rates
      ************************************/
      void setElitismRate(double rate);
      double getElitismRate(); 
      void setNumForElitism(int num);
      int getNumForElitism();

      /****************************************
       Get the best and worst of a population
      ****************************************/
      virtual GeneticProgram* getBest();
      virtual GeneticProgram* getWorst();

      /****************************************
       How often to write the population out
       to a file. A value of 1 will write the
       population out every generation. A value
       of 10 will do every 10th generation etc
       Default is 1
      *****************************************/
      void setLogFrequency(int freq);
      int getLogFrequency() const;

      /****************************************
       Set to true to compress the generation
       files when written to disk
       Only works under unix type systems
      ****************************************/
      void compressGenerationFiles(bool value);

      /***************************************
       Get the value of the compress files
       flag.
      ***************************************/
      bool getCompressFiles() const;

      /***********************************************
       writeToFile will write the current generation
       out to a file in the current directory where
       the file name is of the form gen_XXXXXX.gen,
       and XXXXXX is the generation number.
      ************************************************/
      virtual void writeToFile();

      /***********************************************
       Compute statistics such as average fitness
      ***********************************************/
      virtual void computeStatistics( );

      /***********************************************
       Accessors for average fitness and size data members
      ***********************************************/
      double getAvgFitness();
      double getAvgNormFitness();
      double getAvgSize();
      double getAvgDepth();

      /* Get the standard deviation of the size of members of the population
	   * (which is also the population standard deviation but that's a coincidence) - QCS 10.09.2010
	   */
      double getStdDevSize() const;
      
//      double getBestFitness(); // 2012.09.23 QCS Used for DynOpEq

      /***************************************************
       readFromFile will read a population in from a file
      ***************************************************/
      virtual void readFromFile(char *fileName);

      //Sort the population
      void qSort (GeneticProgram **individuals, int left, int right);

      friend ostream& operator << (ostream& o, Population& p);
      friend istream& operator >> (istream& i, Population& p);
};

#endif
