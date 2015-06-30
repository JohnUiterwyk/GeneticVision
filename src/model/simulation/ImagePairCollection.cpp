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
                string testImage = rootPath + images[index].get("source", "").asString();
                string truthImage = rootPath + images[index].get("target", "").asString();
                //cout << testImage << endl;
                //cout << truthImage << endl;

                result[index].loadSourceImage(testImage);
                result[index].loadTargetImage(truthImage);
                // Iterates over the sequence elements.
            }


        cout << "Loaded " << result.size() << " image pairs from the json config" << endl;
        this->collection.insert( this->collection.end(), result.begin(), result.end() );
        return (int)result.size();

    }


    int ImagePairCollection::loadFromDirectory(string directoryPath)
    {
        string tempFilename;
        DIR *directory;
        struct dirent * directoryEntry;

        // open the directory and scan in all the files
        directory = opendir (directoryPath.c_str());
        if (directory != NULL)
        {
            while ((directoryEntry = readdir (directory)))
            {
                // get the filename
                tempFilename = string(directoryEntry->d_name);

                // check if it is a supported type
                if(this->isValidImageType(tempFilename))
                {
                    // get the key for the filename
                    string key = this->getImagKey(tempFilename);

                    // if the key is not in the map, create a new image pair and add to the map
                    if(imagePairMap.find(key) == imagePairMap.end())
                    {
                        imagePairMap.insert(std::make_pair(key, ImagePair()));
                        imagePairMap[key].setFilenameKey(key);
                    }

                    // load the file into the correct variable
                    if(this->isMaskImage(tempFilename))
                    {
                        imagePairMap[key].loadTargetImage(directoryPath + "/" + tempFilename);
                    }else{
                        imagePairMap[key].loadSourceImage(directoryPath + "/" + tempFilename);

                    }
                }else
                {
                    // ignore invlaid images
                    //cout << " is not a valid image." <<  endl;
                }
            }
            (void) closedir (directory);
        }
        else
        {
            cerr << "Couldn't open the directory " << directoryPath << endl;
        }

        // loop through the map, if a pair has a training and ground truth, it is valid, and add it to collection
        int count = 0;
        for ( std::map<string,ImagePair>::iterator it=imagePairMap.begin() ; it != imagePairMap.end(); ++it )
        {
            if(it->second.isPairValid())
            {
                count++;
                this->collection.push_back(it->second);
            }
        }
        cout << "Loaded " << count << " image pairs from the directory: " << directoryPath << endl;
        return (int)count;

    }
}
