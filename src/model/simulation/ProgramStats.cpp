//
// Created by John Uiterwyk on 6/30/15.
//
#include <iostream>
#include <sstream>

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
string ProgramStats::toString()
{
    std::stringstream stringstream;
    stringstream << "Accuracy: " << getAccuracy() << endl;
    stringstream << "Error Rate: " << getErrorRate() << endl;
    stringstream << "True Positive Rate: " << getTruePositiveRate() << endl;
    stringstream << "False Positive Rate: " << getFalsePositiveRate() << endl;
    stringstream << "True Negative Rate: " << getTrueNegativeRate() << endl;
    stringstream << "False Negative Rate: " << getFalseNegativeRate() << endl;
    return stringstream.str();
}
