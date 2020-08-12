#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include "opencv4/opencv2/core.hpp"

namespace tools{

    void showImage(std::string windowName, cv::Mat image);
    void printScalar(const cv::Scalar& vec);
    void printMatU(const cv::Mat& inputImage);
    void printMatD(const cv::Mat& inputImage);
}

#endif