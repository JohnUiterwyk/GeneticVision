//
// Created by John Uiterwyk on 25/04/15.
//

#include "GeneticVisionApp.h"
#include <string>
#include "model/ImagePair.h"
#include "view/OpenCVWindow.h"

#ifdef CV_HIGHGUI_ENABLED
#include <opencv2/highgui/highgui.hpp>
#endif


namespace GeneticVision
{

    GeneticVisionApp::GeneticVisionApp(const string& jsonConfigFilePath)
    {


//        JSONValue *value = JSON::Parse(contents.c_str());
//        if (value == NULL)
//        {
//            cout << "Example code failed to parse, did you change it?" << endl;
//        } else
//        {
//            JSONObject root;
//            if (value->IsObject() == false)
//            {
//                cout << "The root element is not an object, did you change the example?" << endl;
//            }
//            else
//            {
//                root = value->AsObject();
//
//                // Retrieving a string
//                if (root.find(L"hello") != root.end() && root[L"hello"]->IsString())
//                {
//                    wcout << root[L"hello"]->AsString().c_str() << endl;
//                }
//
//                // Retrieving a string
//                if (root.find(L"count") != root.end() && root[L"count"]->IsNumber())
//                {
//                    cout << root[L"count"]->AsNumber() << endl;
//                }
//
//            }
//        }
//
        bool guiEnabled = false;
        #ifdef CV_HIGHGUI_ENABLED
            guiEnabled = true;
        #endif
        this->model.init(this->appConfig);


        if(guiEnabled)
        {

        }
        this->model.initSimulation();
        bool solutionFound = false;
        do
        {
            solutionFound = this->model.tickSmulation();
        }while(solutionFound == false);
        waitKey(0);
    }

    GeneticVisionApp::~GeneticVisionApp() {

    }
}
