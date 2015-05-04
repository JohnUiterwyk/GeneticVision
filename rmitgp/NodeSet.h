#ifndef _NODESET_H_
#define _NODESET_H_

/******************************************************************************
 Header file
 Class:        FuncSet TermSet
 Date created: 23/04/2002
 Written by:   Dylan Mawhinney
 
 The FuncSet and TermSet classes are based on code originally
 written by Peter Wilson.

 The FuncSet and TermSet classes store a set of nodes (terminals and
 functions). 
******************************************************************************/

#include "Function.h"
#include "Terminal.h"

template <class Type> class NodeVector;

class FuncSet
{
   private:
      typedef Function* (*funcGen)(const string&, GPConfig *);

      GPConfig *config;
      NodeVector<Function> *theSet;

   public:
      FuncSet(GPConfig *conf);
      ~FuncSet();

      void addNodeToSet(int returnType,
            Function* (*generateFunction)(const string&, GPConfig *));
      Function* getRandomNode();
      Function* getRandomNode(int returnType);
      Node* getNodeByName(const string &name);
      Node* getNodeByNumber(int position);
      int getNodeReturnType(int position);
      funcGen getGenFunction(int position);

      int size() const; 
};

class TermSet
{
   private:
      typedef Terminal* (*termGen)(const string&, GPConfig *);

      GPConfig *config;
      NodeVector<Terminal> *theSet;

   public:
      TermSet(GPConfig *conf);
      ~TermSet();

      void addNodeToSet(int returnType,
              Terminal* (*generateFunction)(const string&, GPConfig *));
      Terminal* getRandomNode();
      Terminal* getRandomNode(int returnType);
      Node* getNodeByName(const string &name);
      Node* getNodeByNumber(int position);
      int getNodeReturnType(int position);
      termGen getGenFunction(int position);

      int size() const; 
};

#endif
