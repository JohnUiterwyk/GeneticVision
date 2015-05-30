//
// Created by John Uiterwyk on 5/28/15.
//

#include <fstream>
#include <streambuf>
#include <iostream>
#include "util/json/json.h"
#include "AppConfig.h"

void GeneticVision::AppConfig::loadConfigFile(const string *filepath) {
            std::ifstream in("data/easy-square/easy-square-config.json");
        std::string contents((std::istreambuf_iterator<char>(in)),
                             std::istreambuf_iterator<char>());

        // For info about Json reader see
        // see http://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html
        Json::Value root;
        Json::Reader reader;
        reader.parse(contents, root);
        cout << root.get("hello", "error" ).asString() << endl;

}
