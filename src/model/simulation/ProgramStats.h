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

    double getAccuracy(double truePositiveWeight = 1, double trueNegativeWeight = 1);
    double getErrorRate(double truePositiveWeight = 1, double trueNegativeWeight = 1);
    double getTruePositiveRate();
    double getTrueNegativeRate();
    double getFalsePositiveRate();
    double getFalseNegativeRate();
    double getNormalisedErrorRate();
    double getTotalPixelCount();


    void add(ProgramStats & statsToAdd, double weight = 1);
    string toString();
};


#endif //GENETICVISION_PROGRAMSTATS_H
