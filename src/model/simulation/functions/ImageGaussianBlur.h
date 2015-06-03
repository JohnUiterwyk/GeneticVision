//
// Created by John Uiterwyk on 5/19/15.
//

#ifndef GENETICVISION_IMAGEGAUSSIANBLUR_H
#define GENETICVISION_IMAGEGAUSSIANBLUR_H


#include "../../../rmitgp/Function.h"
#include <opencv2/core/core.hpp>

class ImageGaussianBlur  : Function {
private:
public:
    ImageGaussianBlur(GPConfig *config);

    virtual ~ImageGaussianBlur();

    static Function* generate(const string &name, GPConfig *config);

    virtual void evaluate(ReturnData *out);

    virtual Node* copy();

protected:

};


#endif //GENETICVISION_IMAGEGAUSSIANBLUR_H
