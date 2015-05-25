//
// Created by John Uiterwyk on 26/04/15.
//

#ifndef GENETICVISION_MODEL_H
#define GENETICVISION_MODEL_H
#import "ImagePair.h"
#include "simulation/GpSimulation.h"
#import <string>
#import <vector>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
namespace GeneticVision
{
    class Model {
    public:

        /*************
         Constructor.
        **************/
        Model();
        void loadImages(const string& imageSetPath);
        void initSimulation();
        void tickSmulation();
        vector <ImagePair> getImagePairCollection();
        vector <cv::Mat> getTrainingImages();
        vector <cv::Mat> getGroundTruthImages();

        vector <ImagePair> imagePairs;
        vector <cv::Mat> trainingImages;
        vector <cv::Mat> groundTruthImages;

    private:
        vector< vector<string> > imageSetData;
        GpSimulation * gpSimulation;

    };
}


#endif //GENETICVISION_MODEL_H
