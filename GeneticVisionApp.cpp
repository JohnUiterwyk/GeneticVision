//
// Created by John Uiterwyk on 25/04/15.
//

#include "GeneticVisionApp.h"
#include <iostream>
#include "util/csv/CSVParser.h"
#include "model/ImagePair.h"

namespace GeneticVision
{

    GeneticVisionApp::GeneticVisionApp(const string& imageSetPath, int guiEnabled)
    {
        this->guiEnabled = guiEnabled;
        this->imageSetPath = imageSetPath;
        cout << guiEnabled << " : " << imageSetPath << endl;

        vector< vector<string> > imageSetData;

        CSVParser csvParser(imageSetPath+"image-set.txt");
        csvParser.parse();
        imageSetData = csvParser.getData();

        vector <ImagePair> imagePairs(imageSetData.size());

        for(std::vector<vector<string>>::size_type i = 0; i != imageSetData.size(); i++)
        {
            vector<string> line = imageSetData[i];
            imagePairs[i].loadFromFilePath(imageSetPath+line[0],imageSetPath+line[1]);

        }
    }

    GeneticVisionApp::~GeneticVisionApp() {

    }
}
