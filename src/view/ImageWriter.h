//
// Created by John Uiterwyk on 6/8/15.
//

#ifndef GENETICVISION_IMAGEWRITER_H
#define GENETICVISION_IMAGEWRITER_H

#include "../AppConfig.h"
#include "../model/simulation/RunResult.h"

namespace GeneticVision
{
    class ImageWriter {
    public:
        ImageWriter(AppConfig *appConfig);
        void update(RunResult *runResult);
    private:
        int writeFrequency;
        string outputDirectory;
        bool enabled;
    };

}


#endif //GENETICVISION_IMAGEWRITER_H
