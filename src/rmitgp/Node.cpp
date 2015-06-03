/*************************************************************
 Definition 
 class:        Node
 Date created: 18/03/2002
 Written by:   Dylan Mawhinney

 Adapted from code originally written by Peter Wilson.

**************************************************************/

#include <string>
using namespace std;

class GPConfig;
#include "Node.h"
#include "GPConfig.h"

Node::Node(int type, int numArgs, string n, GPConfig *conf) :
                                             returnType(type), parent(NULL),
                                             name(n), maxArgs(numArgs),
                                             config(conf)
{
}

Node::Node(Node &n) :
            returnType(n.returnType), parent(n.parent),
            name(n.name), maxArgs(n.maxArgs),
            config(n.config)
{
}

Node::~Node()
{
}

int Node::getReturnType() const
{
   return returnType;
}

void Node::setDepth(const int d)
{
   depth = d;
}

int Node::getDepth() const
{
   return depth;
}

string Node::getName() const
{
   return name;
}

int Node::getMaxArgs() const
{
   return maxArgs;
}

Node* Node::getParent() const
{
   return parent;
}

Node* Node::getRootNode() const
{
   if(parent==NULL)
      return (Node *)(this);
   else
   {
      return parent->getRootNode();
   }
}

void Node::setParent(Node *n)
{
   parent = n;
}
