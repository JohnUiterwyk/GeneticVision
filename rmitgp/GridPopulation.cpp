/******************************************************************************
 Definition file
 Class:        GridPopulation 
 Date created: 17/09/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/
#include <cstdlib> //for abs

using namespace std;

#include "GridPopulation.h"
#include "GPConfig.h"

GridPopulation::GridPopulation(int xSize, int ySize, int dist,
                               const char *logFileName, GPConfig *conf)
                    : Population(xSize * ySize, logFileName, conf),
                      width(xSize), height(ySize), neighbourhoodDist(dist),
                      neighbourhoodSize(0), gridPositions(NULL)
{
   int i,j;
   int count=0;

   if ((width > 1) && (height > 1))
   {
      gridPositions = new Point2D[xSize * ySize];

      for (i=0; i<width; i++)
      {
         for (j=0; j<height; j++)
         {
            gridPositions[count].x = i;
            gridPositions[count].y = j; 
            count++;
         }      
      }

      neighbourhoodSize = computeSize(neighbourhoodDist);
      if (neighbourhoodSize > (xSize * ySize))
      {
         cerr << "GridPopulation constructor" << endl
              << "Warning: neighbourhood size is greater than population size!"
              << endl;
      }
      else if ((neighbourhoodDist >= (xSize / 2)) || 
               (neighbourhoodDist >= (ySize / 2)) )  
      {
         cerr << "GridPopulation constructor" << endl
              << "Warning: neighbourhood distance of " << neighbourhoodDist
              << endl
              << "will cause neighbourhood overlap with dimensions " 
              << xSize << "x" << ySize << endl;
      }
   }
   else
      throw string("GridPopulation constructor error size not valid");
}

GridPopulation::~GridPopulation()
{
   delete [] gridPositions;
}

/***********************************************
 This recursive method will compute the number
 of individuals which will be contained in a
 neighbourhood bound by the value (distance).
 For a square grid with city-block distance
 measure this is given by (where D is distance)

 for D > 1
 4D + computerSize(D-1)
 for D == 1
 5
***********************************************/
int GridPopulation::computeSize(int distance) 
{
   if (distance < 1)
      throw string("GridPopulation::computeSize error invalid distance");

   if (distance == 1)
      return 5; 
   else
      return (distance * 4) + computeSize(distance - 1);   
}

bool GridPopulation::isElite(GeneticProgram *program, GeneticProgram **best,
                         int numToCheck)
{
   int i;
   
   for (i=0; i<numToCheck; i++)
   {
      if (program == best[i])
         return true;
   }

   return false;
}


bool GridPopulation::evolve(int numGenerations)
{
   int i=0;
   for (; i<numGenerations; i++)
   {
      assignFitness();  //Evaluate the programs and assign their fitness values
      computeStatistics(); //Calculate some statistics for the population
      writeLog();          //Write some information to the log file
 
      //If the solution has been found quit and return true to
      //indicate success
      if (config->fitnessObject->solutionFound(getPopulation(),
                                               getNumIndividuals()))
      {
         return true;
      }

      nextGeneration();
   }

   return false;
}

void GridPopulation::nextGeneration()
{
   int i;
   int indiv1, indiv2;
   int bestIndex=0;
   int *indexes;

   GeneticProgram **demePop;
   GeneticProgram **nextPop;
   GeneticProgram **bestIndividuals;
   GeneticProgram *temporaryProgram=NULL;

   if ((getGenerationNumber() % getLogFrequency()) == 0)
      writeToFile();

   indexes = new int[neighbourhoodSize];
   demePop = new GeneticProgram* [neighbourhoodSize];
   nextPop = new GeneticProgram* [getNumIndividuals()];
   bestIndividuals = new GeneticProgram* [getNumIndividuals()];

   //Store and sort the best individuals based on their fitness.
   for (i=0; i<getNumIndividuals(); i++)
   {
      bestIndividuals[i] = getIndividual(i);
   }
   qSort(bestIndividuals, 0, getNumIndividuals()-1);

   correctRates();

   adjustFitness();
 
   /****************************************************
    Here we are going to every individual in the grid
    and replacing it with an individual from the
    neighbourhood.
   
    We then do a crossover with a probability of 
    crossoverRate.

    We then do a mutation with a probability of
    mutationRate.
   ****************************************************/
   for (i=0; i < getNumIndividuals(); i++)
   {
      //Keep the best N for elitism
      if ((bestIndex < getNumForElitism()) &&
          isElite(getIndividual(i), bestIndividuals, getNumForElitism()))
      {
         nextPop[i] = getIndividual(i)->copy();
         bestIndex++;
         continue;
      }

      //This function gets the neighbours for individual
      //i and stores them in demePop, their indexes are
      //stored in indexes, it returns the number of neighbours
      //found 
      int numNeighbours = getNeighbours(i, indexes, demePop); 

      //Select an individual from the neighbourhood
      indiv1 = config->selectionOperator->select(demePop, numNeighbours,
                                                 config);

      //Copy that individual
      nextPop[i] = getIndividual(indiv1)->copy();

      double randomNumber = config->randomNumGenerator->randReal();

      //Perform a crossover with probability getCrossoverRate()
      if (randomNumber < getCrossoverRate())
      {
         indiv2 = config->selectionOperator->select(demePop, numNeighbours,
                                                    config);

         temporaryProgram = getIndividual(indexes[indiv2])->copy();
         config->crossoverOperator->crossover(*(nextPop[i]),
                                              *temporaryProgram,
                                              100,
                                              config);
         delete temporaryProgram;
      }
      //Perform a mutation with probability getMutationRate()
      else if (randomNumber < getMutationRate() + getCrossoverRate())
      {
         config->mutationOperator->mutate(*(nextPop[i]), config);
      }
   }

   setPopulation(nextPop, getNumIndividuals());
   setGenerationNumber(getGenerationNumber() + 1); 

   delete [] indexes;
   delete [] demePop;
   delete [] nextPop;
   delete [] bestIndividuals;
}


//Get the neighbours of individual and places them in the array (dest).
//The indexes of the neighbours are placed in the array (indexes).

int GridPopulation::getNeighbours(int individual, int *indexes,
                                     GeneticProgram **dest)
{
   int i;
   int pos=0;

   for (i=0; (i < getNumIndividuals()) && (pos < neighbourhoodSize); i++)
   {
      if (inNeighbourhood(gridPositions[individual], gridPositions[i]))
      {
         indexes[pos] = i;
         dest[pos++] = getIndividual(i); 
      }
   }

   return pos;
}

bool GridPopulation::inNeighbourhood(Point2D &point, Point2D &neighbour)
{
   int distance = 0;

   //This code (while being a little messy) calculates the distance
   //between two points, taking into consideration the toriodal nature
   //of the grid

   if (point.x > neighbour.x)
   {
      if ((point.x - neighbour.x) < abs(point.x - (neighbour.x + width)))
         distance = point.x - neighbour.x;
      else
         distance = abs(point.x - (neighbour.x + width));
   }
   else
   {
      if ((neighbour.x - point.x) < abs(neighbour.x - (point.x + width)))
         distance = neighbour.x - point.x;
      else
         distance = abs(neighbour.x - (point.x + width));
   }

   if (point.y > neighbour.y)
   {
      if ((point.y - neighbour.y) < abs(point.y - (neighbour.y + height)))
         distance += point.y - neighbour.y;
      else
         distance += abs(point.y - (neighbour.y + height));
   }
   else
   {
      if ((neighbour.y - point.y) < abs(neighbour.y - (point.y + height)))
         distance += neighbour.y - point.y;
      else
         distance += abs(neighbour.y - (point.y + height));
   }

   if (distance <= neighbourhoodDist)
      return true;

   return false;
}
