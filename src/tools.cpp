#include "opencv2/core.hpp"
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

void tools::printMatU(const cv::Mat& inputImage){
    assert(inputImage.dims == 2);
    cv::Size size = inputImage.size();
    int width, height;
    width = size.width; height = size.height;

    for(int i = 0; i < height; i++){
        printf("\n");
        for(int j = 0; j < width; j++){
            
            printf("%d ", inputImage.at<unsigned char>(i, j));
            
        }
    }
}

void tools::printMatD(const cv::Mat& inputImage){
    assert(inputImage.dims == 2);
    cv::Size size = inputImage.size();
    int width, height;
    width = size.width; height = size.height;

    for(int i = 0; i < height; i++){
        printf("\n");
        for(int j = 0; j < width; j++){
            
            printf("%d ", inputImage.at<int>(i, j));
            
        }
    }
}