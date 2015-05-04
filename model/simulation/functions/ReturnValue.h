#ifndef _ReturnValue_H_
#define _ReturnValue_H_

#include "../../../rmitgp/ReturnData.h"

#define TYPENUM_MAT (4)
#define TYPENUM_IMAGE (5)
#define TYPENUM_ReturnKernel (6)

template <class T, class TType>
class ReturnValue : public ReturnData
{
private:
   public:

	ReturnValue() : ReturnData()
	{
		initTypeNum();
	}


      void setData(T num)
      {
      	data = num;
      }


      T getData() const
      {
      	return data;
      }
     
   protected:
	   T data;
	  virtual void initTypeNum()
	  {
		  setTypeNum(TType::TYPENUM);
	  };



};


#endif
