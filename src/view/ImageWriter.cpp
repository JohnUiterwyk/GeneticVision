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
        if(this->enabled)
        {
            for ( std::map<string,cv::Mat>::iterator it=runResult->resultImagesMap.begin() ; it != runResult->resultImagesMap.end(); ++it )
            {
                std::stringstream writePath;
                writePath << this->outputDirectory << it->first << "-gen-" << runResult->generationId << "-result.png";
                cv::imwrite(writePath.str(),it->second);
            }

            for ( std::map<string,cv::Mat>::iterator it=runResult->performanceImagesMap.begin() ; it != runResult->performanceImagesMap.end(); ++it )
            {
                std::stringstream writePath;
                writePath << this->outputDirectory << it->first << "-gen-" << runResult->generationId << "-perf.png";
                cv::imwrite(writePath.str(),it->second);
            }
        }


    }
}