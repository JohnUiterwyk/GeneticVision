//
// Created by John Uiterwyk on 6/30/15.
//
#include <iostream>
using namespace std;
#include "ProgramStats.h"

ProgramStats::ProgramStats():
positivePixels(0),
negativePixels(0),
truePositiveCount(0),
falsePositiveCount(0),
trueNegativeCount(0),
falseNegativeCount(0)
{ }
double ProgramStats::getAccuracy() {

    return (truePositiveCount + trueNegativeCount) / (positivePixels + negativePixels);
}


double ProgramStats::getErrorRate() {
    return (falsePositiveCount + falseNegativeCount)/(positivePixels + negativePixels);
}

double ProgramStats::getTruePositiveRate() {
    return truePositiveCount/(truePositiveCount+falseNegativeCount);
}

double ProgramStats::getTrueNegativeRate() {
    return trueNegativeCount/(trueNegativeCount+falsePositiveCount);
}

double ProgramStats::getFalsePositiveRate() {
    return falsePositiveCount/(falsePositiveCount+trueNegativeCount);
}

double ProgramStats::getFalseNegativeRate() {
    return falseNegativeCount/(truePositiveCount+falseNegativeCount);
}

void ProgramStats::add(ProgramStats & statsToAdd)
{
    this->positivePixels += statsToAdd.positivePixels;
    this->negativePixels += statsToAdd.negativePixels;
    this->truePositiveCount += statsToAdd.truePositiveCount;
    this->falsePositiveCount += statsToAdd.falsePositiveCount;
    this->trueNegativeCount += statsToAdd.trueNegativeCount;
    this->falseNegativeCount += statsToAdd.falseNegativeCount;
}
void ProgramStats::toStdOut()
{

    cout << "Postive Pixels: " << positivePixels << endl;
    cout << "Negative Pixels: " << negativePixels << endl << endl;

    cout << "True Positive Count: " << truePositiveCount << endl;
    cout << "False Positive Count: " << falsePositiveCount << endl;
    cout << "True Negative Count: " << trueNegativeCount << endl;
    cout << "False Negative Count: " << falseNegativeCount << endl << endl;

    cout << "True Positive Rate: " << getTruePositiveRate() << endl;
    cout << "False Positive Rate: " << getFalsePositiveRate() << endl;
    cout << "True Negative Rate: " << getTrueNegativeRate() << endl;
    cout << "False Negative Rate: " << getFalseNegativeRate() << endl << endl;


    cout << "Accuracy: " << getAccuracy() << endl;
    cout << "Misclassification Rate: " << getErrorRate() << endl;
}
