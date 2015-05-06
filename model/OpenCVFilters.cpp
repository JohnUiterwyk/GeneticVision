//
// Created by John Uiterwyk on 20/04/15.
//

#include "OpenCVFilters.h"

OpenCVFilters::OpenCVFilters()
{

}
cv::Mat OpenCVFilters::Gaussian(cv::Mat input, int x,int y)
{
    x = x % 100 * 2+ 1;
    y = y % 100 * 2+ 1;
    cv::GaussianBlur(input, this->working, cv::Size(x, y), 0, 0);
    return this->working;
}
cv::Mat OpenCVFilters::Sobel(cv::Mat input, int x,int y)
{
    x = x % 2+1;
    y = y % 2+1;

    cv::Sobel(input, this->working, CV_8U, x, y);
    return this->working;
}
cv::Mat OpenCVFilters::Threshold(cv::Mat input, int x,int y)
{
    x = (int)(((double)x/RAND_MAX) * 256);
    cout << x << endl;
    this->working = input  > x;
    return this->working;
}
cv::Mat OpenCVFilters::Bilateral(cv::Mat input, int x,int y)
{

    cv::Mat temp;
    cv::bilateralFilter(input, temp,5,(x%300),(x%300));
    convertScaleAbs( temp, this->working );
    return this->working;
}
cv::Mat OpenCVFilters::Erosion(cv::Mat input, int x,int y)
{

    cv::Mat element;
    int erosion_type = 0;
    int erosion_size = x%21+1;
    if( y%3 == 0){ erosion_type = cv::MORPH_RECT; }
    else if( y%3 == 1 ){ erosion_type = cv::MORPH_CROSS; }
    else if( y%3 == 2) { erosion_type = cv::MORPH_ELLIPSE; }

    element = cv::getStructuringElement( erosion_type,
                                         cv::Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                         cv::Point( erosion_size, erosion_size ) );
    /// Apply the erosion operation
    erode( input, this->working, element );
    return this->working;
}
cv::Mat OpenCVFilters::Laplacian(cv::Mat input, int x,int y)
{

    cv::Mat temp;
    cv::Laplacian(input,temp,CV_16S,x%15*2+1,1,0,cv::BORDER_DEFAULT);
    convertScaleAbs( temp, this->working );
    return this->working;
}
double OpenCVFilters::GetFitnessScore(cv::Mat input, cv::Mat truth)
{
    int size = 90000;

    cv::Mat diff_mat;
    cv::compare(truth, input, diff_mat, cv::CMP_EQ);
    int nonzero = cv::countNonZero(diff_mat);
    double score = 100* (size - (double)nonzero)/size;
    this->working = diff_mat;
    return score;
}
