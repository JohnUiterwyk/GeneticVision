//
// Created by John Uiterwyk on 26/04/15.
// adapted from code by Stack Overflow user Loki Astari:
// http://stackoverflow.com/questions/1120140/
//

#ifndef GENETICVISION_CSVITERATOR_H
#define GENETICVISION_CSVITERATOR_H
#include <string>
#include <vector>

using namespace std;
class CSVParser
{
    private:
        string csvFilePath;
        string csvString;
        vector<vector<string> > data;

    public:
        CSVParser(const string& csvFilePath);
        vector< vector<string> > parse();
        vector< vector<string> > getData();




        /*********************
         virtual destructor
        *********************/
        virtual ~CSVParser();

};


#endif //GENETICVISION_CSVITERATOR_H
