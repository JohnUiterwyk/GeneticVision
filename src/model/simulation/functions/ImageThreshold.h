//
// Created by John Uiterwyk on 5/19/15.
//

#ifndef GENETICVISION_IMAGETHRESHOLD_H
#define GENETICVISION_IMAGETHRESHOLD_H


#include "../../../rmitgp/Function.h"
#include <opencv2/core/core.hpp>

class ImageThreshold : Function
{
private:
public:
    ImageThreshold(GPConfig *config);

    virtual ~ImageThreshold();

    static Function* generate(const string &name, GPConfig *config);

    virtual void evaluate(ReturnData *out);

    virtual Node* copy();

protected:

};


#endif //GENETICVISION_IMAGETHRESHOLD_H
