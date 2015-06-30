//
// Created by John Uiterwyk on 6/30/15.
//
#include <iostream>
using namespace std;
#include "ProgramStats.h"

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
