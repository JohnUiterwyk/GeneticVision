//
// Created by John Uiterwyk on 5/19/15.
//

#ifndef GENETICVISION_OPENCVFUNCTION_H
#define GENETICVISION_OPENCVFUNCTION_H

#include "../../../rmitgp/Function.h"
#include <opencv2/core/core.hpp>

class OpenCVFunction : Function {
private:
public:
    OpenCVFunction(GPConfig *config);

    virtual ~OpenCVFunction();

    static Function* generate(const string &name, GPConfig *config);

    virtual void evaluate(ReturnData *out);

    virtual Node* copy();

protected:
    virtual void evaluate_impl(ReturnData *out) =0;
};


#endif //GENETICVISION_OPENCVFUNCTION_H
