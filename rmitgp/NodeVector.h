#ifndef _NODEVECTOR_H_
#define _NODEVECTOR_H_

/******************************************************************************
 Header file
 Class:        NodeVector 
 Date created: 03/07/2002
 Written by:   Dylan Mawhinney

 A vector class for Nodes
******************************************************************************/

#include <string>

class GPConfig;

template <class Type>
class NodeVector 
{
   public:
      class Element
      {
         public:
         int returnType;
         Type* (*generateFunction)(const string &, GPConfig *); 
      };

   private:
      GPConfig *config;
      Element* store; 
      int curSize;

      virtual void resize()
      {
         if (store == NULL)
         {
            curSize++;
            store = new Element [curSize];
         }
         else
         {
            Element *tmpStore = new Element [curSize + 1]; 
            int i;

            for (i=0; i<curSize; i++)
               tmpStore[i] = store[i];

            delete [] store;
            store = tmpStore;
            curSize++;
         }
      }

   public:
      NodeVector() : config(NULL), store(NULL), curSize(0)
      {
      }

      virtual ~NodeVector()
      {
         if (store != NULL)
         {
            delete [] store;
            store = NULL;
            curSize = -1;
         }
      }

      /****************************************************
       This is an unfortunate necessity due to limitations
       in g++ in initialising arrays of these objects.
       I wanted to pass this as a constructor argument.
      ****************************************************/
      virtual void setGPConfig(GPConfig *conf)
      {
         config = conf;
      }

      virtual void addElement(Element elem)
      {
         resize();
         store[curSize - 1] = elem;
      }

      virtual Element* getElement(int pos)
      {
         if ((pos >= 0) && (pos < curSize))
            return &(store[pos]);
         else
            return NULL;
      }

      virtual Type* getRandomElement()
      {
         int pos = config->randomNumGenerator->randNum() % curSize;

         if ((pos >= 0) && (pos < curSize))
            return store[pos].generateFunction("", config);
         else
            return NULL;
      }

      virtual Type* getRandomTypedElement(int returnType)
      {
         Element *tmpStore= NULL;
         Type *ret = NULL;
         int tmpSize=0;
         int pos;
         int i;

         tmpStore = new Element [curSize];

         for (i=0; i<curSize; i++)
         {
            if (store[i].returnType == returnType)
            {
               tmpStore[tmpSize++] = store[i];
            }
         }

         if (tmpSize != 0)
         {
            pos = config->randomNumGenerator->randNum() % tmpSize;
            ret = tmpStore[pos].generateFunction("", config);
         }

         delete [] tmpStore;

         return ret;
      }

      virtual int size() const
      {
         return curSize;
      }
};

#endif
