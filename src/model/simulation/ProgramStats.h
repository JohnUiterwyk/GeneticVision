//
// Created by John Uiterwyk on 6/30/15.
//

#ifndef GENETICVISION_PROGRAMSTATS_H
#define GENETICVISION_PROGRAMSTATS_H


class ProgramStats {

public:
    ProgramStats();
    double positivePixels;
    double negativePixels;
    double truePositiveCount;
    double falsePositiveCount;
    double trueNegativeCount;
    double falseNegativeCount;

    double getAccuracy();
    double getErrorRate();
    double getTruePositiveRate();
    double getTrueNegativeRate();
    double getFalsePositiveRate();
    double getFalseNegativeRate();

    void add(ProgramStats & statsToAdd);
    void toStdOut();
};


#endif //GENETICVISION_PROGRAMSTATS_H
