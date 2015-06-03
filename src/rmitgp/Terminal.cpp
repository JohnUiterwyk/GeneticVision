/******************************************************************************
 Definition file
 Class:        Terminal 
 Date created: 21/03/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

#include <string>
using namespace std;

class GPConfig;
#include "Terminal.h"
#include "GPConfig.h"

Terminal::Terminal(int type, string n, GPConfig *conf) : Node(type, 0, n, conf)
{
}

Terminal::~Terminal()
{
}

int Terminal::computeSize()
{
   return 1;
}

int Terminal::computeDepth(int curDepth)
{
   setDepth(curDepth + 1);
   return 1;
}

void Terminal::addToVector(vector<Node *> &vec)
{
   vec.push_back(this);
}

void Terminal::addToVector(vector<Node *> &vec, int typeNum)
{
   if (getReturnType() == typeNum)
      vec.push_back(this);
}

void Terminal::print(string &s)
{
   s.append(getName());  
}
