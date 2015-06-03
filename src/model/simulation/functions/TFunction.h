#ifndef TFunction_H_
#define TFunction_H_


#include <string>
#include "../../../rmitgp/Function.h"


template <class TNode, class TReturn>
class TFunction : public Function
{
public:
	TFunction(GPConfig *conf, int nargs) : Function(TReturn::TYPENUM, nargs, TNode::NAME, conf)
	{
	}

	void evaluate(ReturnData *out)
	{
	   if (out->getTypeNum() != TReturn::TYPENUM)
	      throw string("TNode::evaluate, incorrect ReturnData type");

	   for (int i=0; i < maxArgs; i++)
	   {
	      if (getArgNReturnType(i) != getArgN(i)->getReturnType())
	      {
	         throw string("TNode::evaluate Error argument has incorrect return type");
	      }
	   }
	   evaluate_impl(out);
	}


	/***********************************
     Copies this function and it's
     arguments and returns a pointer to
     the new copy.
    ***********************************/
    virtual Node* copy()
    {
       int i;
       Function *tmp = new TNode(config);

       if (tmp == NULL)
          throw string("TNode::copy() Error, out of memory");

       for(i=0; i<getMaxArgs(); i++)
       {
          tmp->setArgN(i, getArgN(i)->copy());
       }

       return dynamic_cast<Node *>(tmp);
    }

    static Function* generate(const string &name, GPConfig *conf)
    {
       if (name == "")
          return new TNode(conf);
       else if (name == TNode::NAME)
          return new TNode(conf);

       return NULL;
    }

protected:
	virtual void evaluate_impl(ReturnData *out) =0;


};

#endif
