//
// Created by John Uiterwyk on 12/2/15.
//

#ifndef GENETICVISION_IMAGEFILTER2D_H
#define GENETICVISION_IMAGEFILTER2D_H


#include "../../../rmitgp/Function.h"
#include <opencv2/core/core.hpp>

class ImageFilter2D  : Function {
private:
public:
    ImageFilter2D(GPConfig *config);

    virtual ~ImageFilter2D();

    static Function* generate(const string &name, GPConfig *config);

    virtual void evaluate(ReturnData *out);

    virtual Node* copy();

protected:

};

#endif //GENETICVISION_IMAGEFILTER2D_H
