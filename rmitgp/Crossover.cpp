/******************************************************************************
 Definition file
 Class:        Crossover 
 Date created: 22/04/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

using namespace std;

#include "Node.h"
#include "Function.h"

class GPConfig;

#include "GPConfig.h"
#include "Crossover.h"


void Crossover::crossover(GeneticProgram &gp1, GeneticProgram &gp2, 
                          int numRetries, GPConfig *config)
{

	if (config->ddl != NULL) return crossoverDDL(gp1, gp2, numRetries, config);
	// Multiple exit points from functions are bad and you shouldn't do this unless you're as smart as I am - QCS 20121011

   //point1 and point2 are the points in the trees of gp1 and gp2
   //where we will perform crossover
   Node
      *point1=NULL,
      *point2=NULL;

   //parent1 and parent2 are the parent nodes in the trees of point1
   //and point2, they will be NULL if point1 or point2 are the root of
   //the tree
   Function
      *parent1=NULL,
      *parent2=NULL;

   bool valid=false;

   int pos1=-1, pos2=-1;

   int depth1, depth2;
   int count=0;
  
/* Computing size and depth shouldn't really be necessary but it might
 * pay to make sure and it's not too much overhead to do once.  It was
 * moved here from inside the while loop below. - QCS 20121012
 */
   gp1.computeSizeAndDepth();
   gp2.computeSizeAndDepth();


   //The following loop will continually try to find two valid crossover
   //points by selecting a node from each of the trees. It will try up
   //to {numRetries} times before giving up which will leave the 
   //trees unchanged.
   while (!valid) 
   {
      count++;
      point1 = point2 = NULL;

      if (count >= numRetries)
         return;

      //Get a random point in the tree of gp1
      point1 = gp1.getRandomNode();

      if (point1 == NULL) //Can't find valid node
         continue;

      parent1 = dynamic_cast<Function *>(point1->getParent());

      //Get a random point in the tree which has the same return
      //type as point1
      point2 = gp2.getRandomNode(point1->getReturnType());
     
      //If there is no such node with the same return type then stop
      //and try again. 
      if (point2 == NULL) //Can't find valid node
         continue;
  
      parent2 = dynamic_cast<Function *>(point2->getParent());

      depth1 = point1->getDepth() -1; 
      depth2 = point2->getDepth() -1;

      //Here we check that the crossover will produce trees which
      //do not violate the maximum depth
      if (((depth1 + point2->computeDepth(0)) <= config->maxDepth) &&
          ((depth2 + point1->computeDepth(0)) <= config->maxDepth))
      {
         valid = true;
      }
   }


   //If we get to this point we have a valid pair of nodes to perform
   //crossover with


   //Here we find which child position point1 is in it's
   //parent node. 
   if (parent1 != NULL)
   {
      for (pos1=0; pos1<parent1->getMaxArgs(); pos1++)
      {
         if (point1 == parent1->getArgN(pos1))
            break;
      }
   }

   //Here we find which child position point2 is in it's
   //parent node. 
   if (parent2 != NULL)
   {
      for (pos2=0; pos2<parent2->getMaxArgs(); pos2++)
      {
         if (point2 == parent2->getArgN(pos2))
            break;
      }
   }

   if (pos1 >= 0)
   {
      //If point1 was not at the root of the tree
      //replace point1 with point2
      //update point2s parent node
      parent1->setArgN(pos1, point2);
      point2->setParent(parent1);
      gp1.computeSizeAndDepth();
   }
   else
   {
      //If point1 was at the root then make point2
      //the new root of gp1
      gp1.setRoot(point2);
      point2->setParent(NULL);
   }

   if (pos2 >= 0)
   {
      //If point1 was not at the root of the tree
      //replace point1 with point2
      //update point2s parent node
      parent2->setArgN(pos2, point1);
      point1->setParent(parent2);
      gp2.computeSizeAndDepth();
   }
   else
   {
      //If point1 was at the root then make point2
      //the new root of gp1
      gp2.setRoot(point1);
      point1->setParent(NULL);
   }

   //Force the updated programs to update their size and depth
   //information
   //gp1.computeSizeAndDepth();
   //gp2.computeSizeAndDepth();
   // These were moved inside the reparenting above because setRoot already does this - QCS 20121012
}

Crossover::~Crossover()
{
}

void Crossover::crossoverDDL(GeneticProgram &parentGP1, GeneticProgram &parentGP2,
                          int numRetries, GPConfig *config)
{
	int count=0;

	parentGP1.computeSizeAndDepth();
	parentGP2.computeSizeAndDepth();
	int parent1Size = parentGP1.getDepth(); // Saved for use with DDL - 20121008 QCS
	int parent2Size = parentGP2.getDepth(); // These are the sizes of the unchanged parent GPs.

	bool valid = false;

	//The following loop will continually try to find two valid crossover
	//points by selecting a node from each of the trees. It will try up
	//to {numRetries} times before giving up which will leave the
	//trees unchanged.

	while (!valid) {

		//point1 and point2 are the points in the trees of gp1 and gp2
		//where we will perform crossover
		Node
		*point1=NULL,
		*point2=NULL;

		//parent1 and parent2 are the parent nodes in the trees of point1
		//and point2, they will be NULL if point1 or point2 are the root of
		//the tree
		Function
		*parentNode1=NULL,
		*parentNode2=NULL;

		int pos1=-1, pos2=-1;

		int depth1, depth2;

		GeneticProgram * childGP1 = new GeneticProgram (parentGP1);
		GeneticProgram * childGP2 = new GeneticProgram (parentGP2);
		count++;
		point1 = point2 = NULL;

		if (count >= numRetries)
			return;

		//Get a random point in the tree of gp1
		point1 = childGP1->getRandomNode();

		if (point1 == NULL) //Can't find valid node
			continue;

		parentNode1 = dynamic_cast<Function *>(point1->getParent());

		//Get a random point in the tree which has the same return
		//type as point1
		point2 = childGP2->getRandomNode(point1->getReturnType());

		//If there is no such node with the same return type then stop
		//and try again.
		if (point2 == NULL) //Can't find valid node
			continue;

		parentNode2 = dynamic_cast<Function *>(point2->getParent());

		depth1 = point1->getDepth() -1;
		depth2 = point2->getDepth() -1;

		//Here we would normally check that the crossover will produce trees which
		//do not violate the maximum depth however if DDL is active then we don't mind oversized trees at this point.

		//Here we find which child position point1 is in it's
		//parent node.
		if (parentNode1 != NULL)
		{
			for (pos1=0; pos1<parentNode1->getMaxArgs(); pos1++)
			{
				if (point1 == parentNode1->getArgN(pos1)) break;
			}
		}

		//Here we find which child position point2 is in it's
		//parent node.
		if (parentNode2 != NULL)
		{
			for (pos2=0; pos2<parentNode2->getMaxArgs(); pos2++)
			{
				if (point2 == parentNode2->getArgN(pos2)) break;
			}
		}

		if (pos1 >= 0)
		{
			//If point1 was not at the root of the tree
			//replace point1 with point2
			//update point2s parent node
			parentNode1->setArgN(pos1, point2);
			point2->setParent(parentNode1);
		}
		else
		{
			//If point1 was at the root then make point2
			//the new root of gp1
			childGP1->setRoot(point2);
			point2->setParent(NULL);
		}

		if (pos2 >= 0)
		{
			//If point1 was not at the root of the tree
			//replace point1 with point2
			//update point2s parent node
			parentNode2->setArgN(pos2, point1);
			point1->setParent(parentNode2);
		}
		else
		{
			//If point1 was at the root then make point2
			//the new root of gp1
			childGP2->setRoot(point1);
			point1->setParent(NULL);
		}

		//Force the updated programs to update their size and depth
		//information
		childGP1->computeSizeAndDepth();
		childGP2->computeSizeAndDepth();

		// Now test for DDL size validity
		if (config->ddl->validateDepth(childGP1, parent1Size, parent2Size) && config->ddl->validateDepth(childGP2, parent1Size, parent2Size)) {
			// Swap the child GP trees into the parents.
			point1 = childGP1->getRoot();
			point2 = childGP2->getRoot();
			childGP1->setRoot(parentGP1.getRoot());
			childGP2->setRoot(parentGP2.getRoot());
			parentGP1.setRoot(point1);
			parentGP2.setRoot(point2);

			delete (childGP1);
			delete (childGP2);

			valid = true;
		}
		else {
			delete (childGP1);
			delete (childGP2);
		}
	}
}
