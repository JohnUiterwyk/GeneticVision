#ifndef _Mean_H_
#define _Mean_H_


class GPConfig;

#include <string>
#include "TFunction.h"
#include "../types/ReturnDouble.h"

class Mean : public TFunction<Mean, ReturnDouble>
{
   private:

   public:
      /*************
       Constructor.
      **************/
      Mean(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Mean();

      static const string NAME;

   protected:
   	virtual void evaluate_impl(ReturnData *out);

};


#endif
