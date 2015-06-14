//
// Created by John Uiterwyk on 6/8/15.
//

#include <opencv2/highgui/highgui.hpp>
#include "ImageWriter.h"
namespace GeneticVision
{

    ImageWriter::ImageWriter(AppConfig *appConfig) :
    enabled(false)
    {
        if(appConfig->isSaveResultImagesEnabled())
        {
            this->enabled = true;
            this->outputDirectory = appConfig->getImagesOutputPath();
            this->writeFrequency = appConfig->getLogFrequency();
        }

    }

    void ImageWriter::update(RunResult *runResult)
    {
        if(this->enabled && (runResult->generationId % this->writeFrequency == 0 || runResult->generationId == 1))
        {
            for ( std::map<string,cv::Mat>::iterator it=runResult->resultMap.begin() ; it != runResult->resultMap.end(); ++it )
            {
                std::stringstream writePath;
                writePath << this->outputDirectory << it->first << "-gen-" << runResult->generationId << ".png";
                cv::imwrite(writePath.str(),it->second);
            }
        }


    }
}