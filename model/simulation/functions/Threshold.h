#ifndef _Threshold_H_
#define _Threshold_H_


class GPConfig;

#include <string>
#include "TFunction.h"
#include "ReturnImage.h"

class Threshold : public TFunction<Threshold, ReturnImage>
{
   private:

   public:
      /*************
       Constructor.
      **************/
      Threshold(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Threshold();

      static const string NAME;

   protected:
   	virtual void evaluate_impl(ReturnData *out);

};


#endif
