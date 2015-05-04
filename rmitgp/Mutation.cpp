/******************************************************************************
 Definition file
 Class:        Mutation
 Date created: 12/04/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

using namespace std;

#include "GPConfig.h"

#include "Node.h"
#include "Function.h"

#include "Mutation.h"

#include "ProgramGenerator.h"

void Mutation::mutate(GeneticProgram &gp, GPConfig *config)
{
   Node *tmp=NULL, *newTree=NULL;
   Function *parent=NULL;

   //Get a random node and the parent of that node
   tmp = gp.getRandomNode();
   if(tmp == NULL)
      return;

   parent = dynamic_cast<Function *>(tmp->getParent());

   //Generate a new tree to replace the old one
   newTree = config->programGenerator->createGrowProgram(tmp->getDepth()-1,
                                                config->maxDepth-1,
                                                tmp->getReturnType()); 

   //If parent is not NULL then newTree is not at the root of
   //the tree
   if (parent != NULL)
   {
      int i;
      for (i=0; i<parent->getMaxArgs(); i++)
      {
         if (tmp == parent->getArgN(i))
            break;
      }

      parent->setArgN(i, newTree);
      newTree->setParent(parent);
   }
   else
   {
      gp.setRoot(newTree);
      newTree->setParent(NULL);
   }

   //Delete the old tree
   gp.deleteTree(tmp);
   //Recompute the size and depth
   gp.computeSizeAndDepth();
}

Mutation::~Mutation()
{
}
