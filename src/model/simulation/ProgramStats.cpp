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
double ProgramStats::getAccuracy(float truePositiveWeight , float trueNegativeWeight ) {

    return (truePositiveCount*truePositiveWeight + trueNegativeCount* trueNegativeWeight) / (positivePixels* truePositiveWeight + negativePixels* trueNegativeWeight);
}


double ProgramStats::getErrorRate(float truePositiveWeight, float trueNegativeWeight) {
    return 1 - getAccuracy(truePositiveWeight,trueNegativeWeight);
}

double ProgramStats::getNormalisedErrorRate()
{
    return 1 - (getTruePositiveRate() * 0.5 + getTrueNegativeRate() * 0.5);
}
double ProgramStats::getTruePositiveRate() {
    return truePositiveCount/positivePixels;
}

double ProgramStats::getTrueNegativeRate() {
    return trueNegativeCount/negativePixels;
}

double ProgramStats::getFalsePositiveRate() {
    return falsePositiveCount/negativePixels;
}

double ProgramStats::getFalseNegativeRate() {
    return falseNegativeCount/positivePixels;
}
double ProgramStats::getTotalPixelCount() {
    return (positivePixels + negativePixels);
}
void ProgramStats::add(ProgramStats & statsToAdd, float weight)
{
    this->positivePixels += statsToAdd.positivePixels * weight;
    this->negativePixels += statsToAdd.negativePixels* weight;
    this->truePositiveCount += statsToAdd.truePositiveCount* weight;
    this->falsePositiveCount += statsToAdd.falsePositiveCount* weight;
    this->trueNegativeCount += statsToAdd.trueNegativeCount* weight;
    this->falseNegativeCount += statsToAdd.falseNegativeCount* weight;
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
