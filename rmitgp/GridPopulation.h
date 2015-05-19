#ifndef _GRIDPOPULATION_H_
#define _GRIDPOPULATION_H_

/******************************************************************************
 Header file
 Class:        GridPopulation 
 Date created: 17/09/2002
 Written by:   Dylan Mawhinney

 A population is a collection of genetic programs (individuals) that is
 evolved using genetic operators (crossover mutation etc). 

 This is an example of a grid population, which is a form of fine grained
 parallelism.

 Individuals are mapped to a position on the grid, individuals can only
 breed/interact with other individuals who are close to them on the grid.

******************************************************************************/

class GPConfig;

#include <iostream>
#include <fstream>

#include "Population.h"

//GridPopulation is a Population
class GridPopulation : public Population 
{
   private:
      class Point2D
      {
         public:
         int x;
         int y;
      };

      int width;    //Width of the grid
      int height;   //Height of the grid

      int neighbourhoodDist;  //Individuals must be within this distance
                              //of each other to be able to interact
      int neighbourhoodSize;  //The maximum number of individuals in the
                              //neighbourhood

      Point2D *gridPositions; //The positions of each program in the grid

   protected:

      //Computes the size of the neighbourhood
      //given the neighbourhood distance.
      virtual int computeSize(int distance);

      //Determines if the program passed in is one of the
      //programs to be retained through elitism
      virtual bool isElite(GeneticProgram *program, GeneticProgram **best,
                         int numToCheck);

   public:

      /*****************************************************************
       Constructor
       Must pass the width, height, and neighbourhood distance, along
       with the log filename and the config object.
      *****************************************************************/
      GridPopulation(int xSize, int ySize, int dist, const char *logFileName,
                     GPConfig *conf);

      virtual ~GridPopulation();

      //Do the next generation
      virtual void nextGeneration();

      //Evolve for N generations
      virtual bool evolve(int numGenerations);

      //Get the neighbours which are in the neighbourhood of (individual)
      //and place them into the array (dest), place the indexes of
      //the neighbours in the array (numbers). The arrays must have been
      //previously allocated to store at least (neighbourhoodSize) 
      //individuals.
      //Returns the number of individuals in the neighbourhood which is
      //gauranteed to be <= neighbourhoodSize
      virtual int getNeighbours(int individual, int *numbers, GeneticProgram **dest);

      //Returns true if neighbour is a neighbour of point
      virtual bool inNeighbourhood(Point2D &point, Point2D &neighbour);

};

#endif
