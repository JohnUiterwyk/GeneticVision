//
// Created by John Uiterwyk on 6/8/15.
//

#include <opencv2/highgui/highgui.hpp>
#include <iomanip>
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
            if(runResult->performanceImagesMap.size() > 0)
            {

                for ( std::map<string,cv::Mat>::iterator it=runResult->performanceImagesMap.begin() ; it != runResult->performanceImagesMap.end(); ++it )
                {
                    std::stringstream writePath;
                    writePath << this->outputDirectory << it->first << "-gen-" << setfill('0') << setw(6) << runResult->generationId << ".png";
                    cv::imwrite(writePath.str(),it->second);
                }

            }else
            {
                for ( std::map<string,cv::Mat>::iterator it=runResult->resultImagesMap.begin() ; it != runResult->resultImagesMap.end(); ++it )
                {
                    std::stringstream writePath;
                    writePath << this->outputDirectory << it->first << "-gen-" << setfill('0') << setw(6) << runResult->generationId << ".png";
                    cv::imwrite(writePath.str(),it->second);
                }
            }
        }


    }
}