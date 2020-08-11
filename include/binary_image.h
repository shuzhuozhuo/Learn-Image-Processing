#ifndef BINARY_IMAGE_H
#define BINARY_IMAGE_H

#include "opencv4/opencv2/core.hpp"

namespace binImg{

    cv::Mat binaryImageWithThreshold(const cv::Mat& inputImage, int thresh1, int thresh2, bool isShow);
    cv::Mat binaryImageWithOtus(const cv::Mat& inputImage, bool isShow);
    cv::Mat BinaryImageAdative(const cv::Mat& inputImage, bool isShow, int windowSize, float t);
    void test();

}



#endif // BINARY_IMAGE_H