#ifndef _StdDev_H_
#define _StdDev_H_


class GPConfig;

#include <string>
#include "TFunction.h"
#include "../types/ReturnDouble.h"

class StdDev : public TFunction<StdDev, ReturnDouble>
{
   private:

   public:
      /*************
       Constructor.
      **************/
      StdDev(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~StdDev();

      static const string NAME;

   protected:
   	virtual void evaluate_impl(ReturnData *out);

};


#endif
