//
// Created by John Uiterwyk on 26/04/15.
//

#include "CSVParser.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

CSVParser::CSVParser(const string &csvFilePath)
{
    this->csvFilePath = csvFilePath;
    std::ifstream fileStream(this->csvFilePath);
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    this->csvString = buffer.str();
}
CSVParser::~CSVParser() {

}
vector< vector<string> > CSVParser::parse()
{

    bool inQuote(false);
    bool newLine(false);
    string field;
    this->data.clear();
    vector<string> line;

    string::const_iterator aChar = this->csvString.begin();
    while (aChar != this->csvString.end())
    {
        switch (*aChar)
        {
            case '"':
                newLine = false;
                inQuote = !inQuote;
                break;

            case ',':
                newLine = false;
                if (inQuote == true)
                {
                    field += *aChar;
                }
                else
                {
                    line.push_back(field);
                    field.clear();
                }
                break;

            case '\n':
            case '\r':
                if (inQuote == true)
                {
                    field += *aChar;
                }
                else
                {
                    if (newLine == false)
                    {
                        line.push_back(field);
                        this->data.push_back(line);
                        field.clear();
                        line.clear();
                        newLine = true;
                    }
                }
                break;

            default:
                newLine = false;
                field.push_back(*aChar);
                break;
        }

        aChar++;
    }

    if (field.size()) {
        line.push_back(field);
    }

    if (line.size()) {
        this->data.push_back(line);
    }
    return this->data;
}

vector< vector<string> > CSVParser::getData()
{
    return this->data;
}