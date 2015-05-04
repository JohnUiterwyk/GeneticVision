#ifndef _TTerminal_H_
#define _TTerminal_H_

/******************************************************************************
 Header file
 Class:        TTerminal 
 Date created: 04/08/2002
 Written by:   Dylan Mawhinney

 TTerminal is a variable terminal. 
***************************************************************************/

class GPConfig;

#include <string>
#include "../../../rmitgp/Terminal.h"

template <class TData, class TReturn, class TNode>
class TTerminalBase : public Terminal
{
private:

   public:
	TTerminalBase(GPConfig *conf) : Terminal(TReturn::TYPENUM, TNode::NAME, conf)
	{
	}
	virtual ~TTerminalBase() {}

	static Terminal* generate(const string &name, GPConfig *conf)
	{
	   if (name == "")
	      return new TNode(conf);
	   if (name.find(TNode::NAME)==0)
	   {
		   TNode* result=new TNode(conf);
		   result->parse(name);
		   return result;
	   }
	   return NULL;
	}

	virtual void parse(const string &name) {	}

	virtual Node* copy()
	{
	   Node *tmp = new TNode(config);

	   if (tmp == NULL)
	      throw string("TTerminal::copy() Error, out of memory");

	   return tmp;
	}

};

template <class TData, class TReturn, class TNode>
class TTerminal : public TTerminalBase<TData, TReturn, TNode>
{
public:
	TTerminal(GPConfig *conf) : TTerminalBase<TData, TReturn, TNode>(conf)
	{
	}
	virtual ~TTerminal() {}
	static void setValue(TData v)
	{
	   value = v;
	}
	virtual void evaluate(ReturnData *out)
	{
	   if (out->getTypeNum() != (TReturn::TYPENUM))
	      throw string("TTerminal::evaluate, incorrect ReturnData type");

	   dynamic_cast<TReturn*>(out)->setData(value);
	}


   protected:
	   static TData value; //The data for this class

};


template<class TData, class TReturn, class TNode> TData TTerminal<TData, TReturn, TNode>::value;

template <class TData, class TReturn, class TNode>
class TTerminalNonStatic : public TTerminalBase<TData, TReturn, TNode>
{
public:
	TTerminalNonStatic(GPConfig *conf) : TTerminalBase<TData, TReturn, TNode>(conf)
	{
	}
	TTerminalNonStatic(GPConfig *conf, TData val) : TTerminalBase<TData, TReturn, TNode>(conf), value(val)
	{
	}
	virtual ~TTerminalNonStatic() {}
	void setValue(TData v)
	{
	   value = v;
	}
	virtual void evaluate(ReturnData *out)
	{
	   if (out->getTypeNum() != (TReturn::TYPENUM))
	      throw string("TTerminal::evaluate, incorrect ReturnData type");

	   dynamic_cast<TReturn*>(out)->setData(value);
	}

	virtual Node* copy()
	{
		TNode *tmp = (TNode*)TTerminalBase<TData, TReturn, TNode>::copy();

	   tmp->value = this->value;

	   return tmp;
	}

   protected:
	   TData value; //The data for this class

};



#endif
