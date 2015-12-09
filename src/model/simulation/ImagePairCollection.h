//
// Created by John Uiterwyk on 6/8/15.
//

#ifndef GENETICVISION_IMAGEPAIRCOLLECTION_H
#define GENETICVISION_IMAGEPAIRCOLLECTION_H

#include <vector>
#include <string>
#include "../ImagePair.h"
#include "../../util/json/json.h"

using namespace std;
namespace GeneticVision
{
    class ImagePairCollection {
    public:
        ImagePairCollection();


        bool isValidImageType(string &filename);

        bool isMaskImage(string &filename);

        string getImagKey(string &filename);

        int getTrainTestSplit(vector<ImagePair> &trainVector, vector<ImagePair> &testVector, double split, int seed);
        void addPair(ImagePair pair);
        int loadFromJson(const Json::Value &images, string & rootPath);

        int loadFromDirectory(string directoryPath);

        vector<ImagePair> &getVector() { return collection; }
        map<string, ImagePair> &getMap() { return imagePairMap; }

        unsigned long size(){ return collection.size(); }


    private:
        vector<ImagePair > collection;
        map<string, ImagePair> imagePairMap;
    };
}


#endif //GENETICVISION_IMAGEPAIRCOLLECTION_H
