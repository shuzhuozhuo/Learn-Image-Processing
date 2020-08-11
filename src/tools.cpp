#include "opencv4/opencv2/core.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include <string>
#include "tools.h"

void tools::showImage(std::string windowName, cv::Mat image){

    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::imshow(windowName, image);
    cv::waitKey(0);

}

void tools::printScalar(const cv::Scalar& vec){

    printf("Scalar Value is %f %f %f %f \n", vec(0), vec(1), vec(2), vec(3));

}