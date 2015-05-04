/******************************************************************************
 Definition file
 Class:        GeneticProgram 
 Date created: 26/03/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

#include "Function.h"
#include "Terminal.h"

#include "NodeSet.h"

#include "Util.h"

class GPConfig;
#include "GPConfig.h"
#include "GeneticProgram.h"

GeneticProgram::GeneticProgram(GPConfig *conf) : config(conf), programID(0),
                                                 fitness(0.0), depth(0),
                                                 size(0), returnType(-1),
                                                 root(NULL), range("")
{
    objValues = new double[conf->numObjectives];
}

GeneticProgram::GeneticProgram(GeneticProgram &g) :
                                  config(new GPConfig(*(g.config))), programID(g.programID),
                                  fitness(g.fitness),
                                  adjustFitness(g.adjustFitness),
                                  parsimonyFitness(g.parsimonyFitness), 
                                  normalizedFitness(g.normalizedFitness), 
                                  depth(g.depth),
                                  size(g.size), returnType(g.returnType),
                                  root(g.root->copy()), range(g.range)
{
}

GeneticProgram::~GeneticProgram() 
{
   deleteTree(root);
   root = NULL;
}

void GeneticProgram::setProgramID(int id)
{
   programID = id;
}

int GeneticProgram::getProgramID() const
{
   return programID;
}   

//The evaluate method evaluates(executes) this program
void GeneticProgram::evaluate(ReturnData *out)
{
   if (root == NULL)
      throw string("GeneticProgram::evaluate Error root node is NULL");

   if (out->getTypeNum() != root->getReturnType())
   {
      throw string("GeneticProgram::evaluate() Error return type of root node does not match return type of out");
   }

   root->evaluate(out);
}

//Sets the root of the tree to point to the new tree value.
//If the old tree is no longer to be used it must be deleted
//explicitly by calling deleteTree() below.
void GeneticProgram::setRoot(Node *value)
{
   root = value;

   if (root != NULL)
      computeSizeAndDepth();
}

Node * GeneticProgram::getRoot()
{
   return root;
}

//Delete the current tree.
void GeneticProgram::deleteTree()
{
   deleteTree(root);
   root = NULL;
}

//Recursively deletes the tree whose root is pointed to by theRoot.
void GeneticProgram::deleteTree(Node *theRoot)
{
   Node *tmp;

   if (theRoot == NULL)
     return;

   /*If theRoot is a function delete the children first*/
   if (theRoot->getMaxArgs() > 0)
   {
      for (int i=0; i< theRoot->getMaxArgs(); i++)
      {
         tmp = dynamic_cast<Function *>(theRoot)->getArgN(i);
         deleteTree(tmp);
      }  
   }

   /*Delete this node*/
   delete theRoot;
}

int GeneticProgram::getDepth() const
{
   return depth;
}

int GeneticProgram::getSize() const
{
   return size;
}

void GeneticProgram::computeSizeAndDepth()
{
   if (root == NULL)
      throw string("GeneticProgram::computeSizeAndDepth Error, root is null");

   size = root->computeSize(); 
   depth = root->computeDepth(0);
}

//Gets a random node from the program tree
Node* GeneticProgram::getRandomNode()
{
   vector<Node *> nodeList;

   root->addToVector(nodeList); 

   if (nodeList.size() != 0)
   { 
      int index = config->randomNumGenerator->randNum() % nodeList.size(); 
      return nodeList[index];
   }
   else
      return NULL;
}

//Get a random node from the program tree that returns typeNum
Node* GeneticProgram::getRandomNode(int typeNum)
{
   vector<Node *> nodeList;
   int index;

   root->addToVector(nodeList, typeNum);

   if (nodeList.size() != 0)
   {
      index = config->randomNumGenerator->randNum() % nodeList.size(); 
      return nodeList[index];
   }
   else
      return NULL;
}

void GeneticProgram::print(string &s)
{
   if (root == NULL)
      throw string("GeneticProgram::print Error root node is NULL");

   root->print(s);
}

void GeneticProgram::setReturnType(int type)
{
   returnType = type;
}

int GeneticProgram::getReturnType() const
{
   return returnType;
}

void GeneticProgram::setFitness(double f)
{
   //If we get a fitness < 0 then there is a problem
   //this is usually caused by a double overflowing and
   //wrapping to a negative value
   if (f < 0.0)
   {
      cerr << "GeneticProgram::setFitness : Warning: Fitness overflow " 
           << f << endl;
   }
   else  
      fitness = f;
   	   setNormFitness(1.0 / (1.0 + f)); // QCS 20121021
}

double GeneticProgram::getFitness() const
{
   return fitness;
}

void GeneticProgram::setNormFitness(double f)
{
   normalizedFitness = f;
}

double GeneticProgram::getNormFitness() const
{
   return normalizedFitness;
}

void GeneticProgram::setParsFitness(double f)
{
   parsimonyFitness = f;
}

double GeneticProgram::getParsFitness() const
{
   return parsimonyFitness;
}

void GeneticProgram::setAdjFitness(double f)
{
   adjustFitness = f;
}

double GeneticProgram::getAdjFitness() const
{
   return adjustFitness;
}

//The copy method will create a new genetic
//program which is a copy of the current program
GeneticProgram* GeneticProgram::copy()
{
   GeneticProgram *tmp = new GeneticProgram(config);
   
   Node *rootTmp;

   tmp->setFitness(fitness);
   tmp->setAdjFitness(adjustFitness);
   tmp->setRange(range); 	/* Added by Feng/Geoff Lee 3/12/2012. Used for Dynamic Selection coding.  */
   tmp->setReturnType(returnType);

   if (root != NULL)
   {
      rootTmp = root->copy();
      tmp->setRoot(rootTmp);
      tmp->computeSizeAndDepth();
   }
   else
   {
      cerr << "**** Warning GeneticProgram::copy() ******\n"
           << "Copying program will NULL root\n";

      tmp->setRoot(NULL);
   }
   for (int i = 0;i<config->numObjectives;i++)
    {
		tmp->setObjectiveValue(i,objValues[i]);
	}
   return tmp;
}

/*********************************************************
 parseProgram based on function parseTree originally
 written by Peter Wilson
*********************************************************/
void GeneticProgram::parseProgram(string &programString)
{
   Node *tmpRoot = NULL;
   string::iterator si = programString.begin();

   tmpRoot = buildTree(programString, si);

   deleteTree();  
   setRoot(tmpRoot);
}

Node* GeneticProgram::buildTree(string &programString, string::iterator &si)
{
   Node *tmpRoot = NULL;
   Node *arg = NULL;

   string token = getToken(programString, si);

   int count=0;

   try
   {
      if (token == "")
      {
         /*End of program*/
      }
      else if (token == "(")   //Start of function
      {
         token = getToken(programString, si); 
         tmpRoot = config->funcSet.getNodeByName(token); 

         while (lookAtToken(programString, si) != ")")
         {
            arg = buildTree(programString, si);
            dynamic_cast<Function *>(tmpRoot)->setArgN(count, arg); 
            count++;
         }
         token = getToken(programString, si);
      }
      else //Must be terminal
      {
         tmpRoot = config->termSet.getNodeByName(token); 
      }
   }

   //If we get an error it will usually be because of a terminal
   //or function being missing from the nodesets.
   catch (string &err)
   {
      string errString(err);
      errString.append("\nGeneticProgram::parseProgram\nError program: ");
      errString.append(programString); 
      errString.append("\nToken: "); 
      errString.append(token); 

      throw errString;
   }

   return tmpRoot;
}


void GeneticProgram::setObjectiveValue(int objIndex, double value){
    objValues[objIndex] = value;
}

double GeneticProgram::getObjectiveValue(int objIndex){
    return objValues[objIndex];
}


void GeneticProgram::setCrowdingDist(double dist){
    crowdingDist = dist;
}

double GeneticProgram::getCrowdingDist(){
    return crowdingDist;
}


void GeneticProgram::setRank(int rank){
    fitness = rank;
}

int GeneticProgram::getRank(){
    return fitness;
}

void GeneticProgram::setRange(string r) 	/* Added by Feng/Geoff Lee 3/12/2012. Used for Dynamic Selection coding.  */
{
	range = r;
	//cout << "**" << range << endl;
}

void GeneticProgram::setRange(char *r) 	/* Added by Feng/Geoff Lee 3/12/2012. Used for Dynamic Selection coding.  */
{
	range = r;
	//cout << "**" << range << endl;
}

void GeneticProgram::printRange(string &s) 	/* Added by Feng/Geoff Lee 3/12/2012. Used for Dynamic Selection coding.  */
{
	//cout << "^^^" << range << endl;
	s = range;
	//cout << "***" << s << endl;
}
