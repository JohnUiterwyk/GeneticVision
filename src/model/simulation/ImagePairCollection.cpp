//
// Created by John Uiterwyk on 6/8/15.
//

#include <iostream>
#include <dirent.h>
#include "ImagePairCollection.h"
using namespace std;
namespace GeneticVision
{
    ImagePairCollection::ImagePairCollection(){};
    bool ImagePairCollection::isValidImageType(string & filename)
    {
        string extension;
        if(filename.length() > 3)
        {
            extension = filename.substr(filename.length()-4,4);
        }else
        {
            extension = filename;
        }

        return extension == ".png"
               || extension == ".jpg"
               || extension == ".bmp"
               || extension == ".tif";

    }
    bool ImagePairCollection::isMaskImage(string & filename)
    {
        return (filename.find("-mask.") != string::npos);
    }

    string ImagePairCollection::getImagKey(string & filename)
    {
        if(this->isMaskImage(filename))
        {
            return filename.substr(0,filename.length()-9);
        } else
        {
            return  filename.substr(0,filename.length()-4);
        }
    }

    /**
     * loadImagesFromJson processess a list of objects that define a test image and the truthImage
     */
    int ImagePairCollection::loadFromJson(const Json::Value &images, string & rootPath)
    {
        vector<ImagePair> result;

            // if size > 0, images is a json object
            result.resize(images.size());

            for (int index = 0; index < images.size(); ++index)
            {
                string testImage = rootPath + images[index].get("test", "").asString();
                string truthImage = rootPath + images[index].get("truth", "").asString();
                //cout << testImage << endl;
                //cout << truthImage << endl;

                result[index].loadTrainingImage(testImage);
                result[index].loadGroundTruth(truthImage);
                // Iterates over the sequence elements.
            }


        cout << "Loaded " << result.size() << " image pairs" << endl;
        this->collection.insert( this->collection.end(), result.begin(), result.end() );
        return (int)result.size();

    }
    int ImagePairCollection::loadFromDirectory(string & path)
    {
        vector<ImagePair> result;

        string tempFilename;
        DIR *directory;
        struct dirent * directoryEntry;
        directory = opendir (path.c_str());
        if (directory != NULL)
        {
            while ((directoryEntry = readdir (directory)))
            {
                tempFilename = string(directoryEntry->d_name);
                cout << tempFilename;
                if(this->isValidImageType(tempFilename))
                {
                    if(this->isMaskImage(tempFilename))
                    {
                        cout << " is a valid mask image with key " << this->getImagKey(tempFilename) <<   endl;
                    } else{
                        cout << " is a valid train image with key " << this->getImagKey(tempFilename) <<   endl;
                    }
                } else
                {
                    cout << " is not a valid image." <<  endl;

                }
            }
            (void) closedir (directory);
        }
        else
        {
            cerr << "Couldn't open the directory " << path << endl;
        }
        cout << "Loaded " << result.size() << " image pairs" << endl;
        this->collection.insert( this->collection.end(), result.begin(), result.end() );
        return (int)result.size();

    }
}
