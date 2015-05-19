//
// Created by John Uiterwyk on 5/19/15.
//

#include "OpenCVFunction.h"
#include "../types/ReturnImage.h"
#include "../types/ReturnDouble.h"

OpenCVFunction::OpenCVFunction(GPConfig *config):
        Function(ReturnImage::TYPENUM, 2, "cv_gaussian", config)
{

}

OpenCVFunction::~OpenCVFunction() {

}

Function *OpenCVFunction::generate(const string &name, GPConfig *config) {
    return nullptr;
}

void OpenCVFunction::evaluate(ReturnData *out) {

}

Node *OpenCVFunction::copy() {
    return nullptr;
}
