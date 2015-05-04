
#include "ReturnKernel.h"

//Initialise static data

ReturnKernel::ReturnKernel()
{
	data = Mat::zeros(1, 1, CV_32F);
}

ReturnKernel::~ReturnKernel()
{
}
