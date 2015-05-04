/******************************************************************************
 Definition file
 Class:        ProgramGenerator 
 Date created: 22/04/2002
 Written by:   Dylan Mawhinney

 See header file for details.

******************************************************************************/

#include <string>

using namespace std;

#include <iostream>

#include "GPConfig.h"
#include "Terminal.h"
#include "Function.h"
#include "NodeSet.h"

#include "Function.h"
#include "Terminal.h"

#include "ProgramGenerator.h"

/************************************************
 Depth table creation code was based on code
 originally written by Tom Loveard
************************************************/

ProgramGenerator::ProgramGenerator(GPConfig *conf) : config(conf)
{
   int numFunctions = config->funcSet.size(); 
   int numTerminals = config->termSet.size(); 
   NodeVector<Node>::Element elem;
   int i;

   int maxDepth = config->maxDepth;

   growTable = new NodeVector<Node>[maxDepth];
   fullTable = new NodeVector<Node>[maxDepth];

   for (i=0; i<maxDepth; i++)
   {
      growTable[i].setGPConfig(config);
      fullTable[i].setGPConfig(config);
   }

   //Add in the terminals at the bottom of the tree
   for (i=0; i<numTerminals; i++)
   {
      elem.returnType = config->termSet.getNodeReturnType(i);
      elem.generateFunction = (Node* (*)(const string&, GPConfig *)) 
                                          config->termSet.getGenFunction(i);
      
      growTable[0].addElement(elem);
      fullTable[0].addElement(elem);
   }

   int curDepth=0;

   //grow table creation
   for (curDepth=1; curDepth < maxDepth; curDepth++)
   {
      //Add the terminals
      for (i=0; i<numTerminals; i++)
      {
         elem.returnType = config->termSet.getNodeReturnType(i);
         elem.generateFunction = (Node* (*)(const string&, GPConfig *)) 
                                        config->termSet.getGenFunction(i);
      
         growTable[curDepth].addElement(elem);
      }

      //Add the functions
      for (i=0; i<numFunctions; i++)
      {
         Function* tmpFunc = config->funcSet.getGenFunction(i)("", config);
         bool valid=true;   

         for (int arg=0; arg < tmpFunc->getMaxArgs(); arg++)
         {
            bool found=false;
            int argNReturnType = tmpFunc->getArgNReturnType(arg);

            for (int tSize=0; tSize < growTable[curDepth-1].size(); tSize++)
            {
               Node* tmpNode = growTable[curDepth-1].
                               getElement(tSize)->generateFunction("", config);

               if (argNReturnType == tmpNode->getReturnType())
               {
                  found = true;
                  delete tmpNode;
                  break;
               }
               delete tmpNode;
            }

            if (!found)
            {
               valid = false;
               break;
            }
         }

         if (valid)
         {
            elem.returnType = tmpFunc->getReturnType();
            elem.generateFunction = (Node* (*)(const string&, GPConfig *))
                                           config->funcSet.getGenFunction(i);
            growTable[curDepth].addElement(elem);
         }
         delete tmpFunc;
      }
   }

   //full table creation
   for (curDepth=1; curDepth < maxDepth; curDepth++)
   {
      //Add the functions
      for (i=0; i<numFunctions; i++)
      {
         Function* tmpFunc = config->funcSet.getGenFunction(i)("", config);
         bool valid=true;

         for (int arg=0; arg < tmpFunc->getMaxArgs(); arg++)
         {
            bool found=false;
            int argNReturnType = tmpFunc->getArgNReturnType(arg);

            for (int tSize=0; tSize < fullTable[curDepth-1].size(); tSize++)
            {
               Node* tmpNode = fullTable[curDepth-1].
                               getElement(tSize)->generateFunction("", config);

               if (argNReturnType == tmpNode->getReturnType())
               {
                  found = true;
                  delete tmpNode;
                  break;
               }
               delete tmpNode;
            }

            if (!found)
            {
               valid = false;
               break;
            }
         }

         if (valid)
         {
            elem.returnType = tmpFunc->getReturnType();
            elem.generateFunction = (Node* (*)(const string&, GPConfig*))
                                          config->funcSet.getGenFunction(i);
            fullTable[curDepth].addElement(elem);
         }
         delete tmpFunc;
      }
   }
}

ProgramGenerator::~ProgramGenerator()
{
   delete [] growTable;
   delete [] fullTable;
}

void ProgramGenerator::generateInitialPopulation(GeneticProgram* pop[],
                                             int numIndividuals,
                                             int minSize,
                                             int maxSize, int expectedSize,
                                             int expectedReturnType)
{
   Node *tmp;
   int indivPerSize=0;
   int tmpSize=minSize-1;
   int indiv=0;
	
   int sizeSteps = (maxSize - 1) - tmpSize;
   int sizeIncrement=0;
   int numIndividualsForRamping = numIndividuals/2;

   if (minSize > maxSize)
      throw string("ProgramGenerator::generateInitialPopulation error minSize is greater than maxSize");

   if (sizeSteps <= 0)
   {
      sizeIncrement = 0;
      indivPerSize = numIndividualsForRamping;
   }   
   else if ((numIndividualsForRamping / sizeSteps) > 1)
   {
      //If there are more individuals than size steps
      //then we can use every size from minSize to maxSize
      sizeIncrement = 1;
      indivPerSize = numIndividualsForRamping / sizeSteps;
   }
   else
   {
      //If we have less individuals than we have steps
      //then we can't use all the sizes when ramping
      indivPerSize = 1;
      sizeIncrement = sizeSteps / numIndividualsForRamping;
      if ((sizeSteps % numIndividualsForRamping) > 0)
         sizeIncrement++;
   }

   for (indiv=0; indiv < numIndividualsForRamping; indiv++)
   {
      if((indiv % indivPerSize) == 0)
      {
         tmpSize += sizeIncrement;
         if (tmpSize >= maxSize)
            tmpSize = (maxSize-1);
      }

      try
      {
         tmp = createGrowProgram(0, tmpSize, pop[indiv]->getReturnType());
      }
      catch (const string & error)
      {
         if((tmpSize += sizeIncrement) >= maxSize)
            tmpSize = (maxSize - 1); 

         indiv--;
         continue;
      }
 
      pop[indiv]->setRoot(tmp);

   }

   tmpSize = minSize-1;

   for (; indiv<numIndividuals; indiv++)
   {
      if((indiv % indivPerSize) == 0)
      {
         tmpSize += sizeIncrement;
         if (tmpSize >= maxSize)
            tmpSize = (maxSize-1);
      }

      try
      {
         tmp = createFullProgram(0, tmpSize, pop[indiv]->getReturnType());
         pop[indiv]->setRoot(tmp);

      }
      catch (const string & error)
      {
         if (tmpSize >= (maxSize-1))
         {
            string newError ("ProgramGenerator::generateInitialPopulation ");
            newError.append("Unrecoverable error\n");
            newError.append("Unable to generate program. Check depth limits ");
            newError.append("and for insufficient terminals and functions\n");
            throw newError; 
         }

         if((tmpSize += sizeIncrement) >= maxSize)
            tmpSize = (maxSize - 1); 

         indiv--;
         continue;
      }
   }
}

Node * ProgramGenerator::createFullProgram(int curDepth, int maxDepth,
                                           int expectedReturnType)
{
   int depth;
   Node *node = NULL;

   depth = maxDepth - curDepth;
   if (depth < 0)
   {
      depth = 0;
   }

   node = fullTable[depth].getRandomTypedElement(expectedReturnType);

   if (node == NULL)
   {
      cerr << "Warning, unable to create Full program for this set of "
           << "Functions and Terminals" << endl;
      return createGrowProgram(curDepth, maxDepth, expectedReturnType);
   }

   if (node->getMaxArgs() > 0)
   {
      Function *func = dynamic_cast<Function *>(node);

      for(int i=0; i<func->getMaxArgs(); i++)
      {
         func->setArgN(i, createFullProgram(curDepth +1, maxDepth, 
                                             func->getArgNReturnType(i)));
      }
   }

   return node;
}

Node* ProgramGenerator::createGrowProgram(int curDepth, int maxDepth, 
                                          int expectedReturnType)
{
   int i;
   int depth;
   Node *node; 

   depth = maxDepth - curDepth;
   if (depth < 0)
   {
      depth = 0;
   }

   node = growTable[depth].getRandomTypedElement(expectedReturnType);

   if (node == NULL)
      throw string("ProgramGenerator::createGrowProgram getRandomNode returned NULL");
  
   if (node->getMaxArgs() > 0)
   {
      Function *func = dynamic_cast<Function *>(node);

      for (i=0; i<node->getMaxArgs(); i++)
      {
         func->setArgN(i, createGrowProgram(curDepth +1, maxDepth, 
                                             func->getArgNReturnType(i)));
      }
   }
   return node;
}
