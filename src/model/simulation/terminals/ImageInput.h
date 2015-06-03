//
// Created by John Uiterwyk on 5/19/15.
//

#ifndef GENETICVISION_IMAGEINPUT_H
#define GENETICVISION_IMAGEINPUT_H


#include "../../../rmitgp/Terminal.h"
#include <opencv2/core/core.hpp>

class ImageInput : public Terminal {
private:
    static cv::Mat value; // data for terminal

public:
    ImageInput(GPConfig * config);
    virtual ~ImageInput();
    static Terminal* generate(const string &name, GPConfig *config);

    virtual void evaluate(ReturnData *out);
    virtual Node* copy();

    static void setValue(cv::Mat value);

protected:
};


#endif //GENETICVISION_IMAGEINPUT_H
