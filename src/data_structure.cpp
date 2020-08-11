#include "opencv4/opencv2/core/core.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include <opencv4/opencv2/core/hal/interface.h>
#include "data_structure.h"
#include "tools.h"
// using namespace cv;



void dataStructure::defineAnMat(){

    cv::Mat m(256, 256, CV_8UC3, cv::Scalar(0, 0, 255));

    tools::showImage("Image", m);
}


void dataStructure::getMatrixValue(){

    cv::Mat m = cv::Mat::eye(10, 10, CV_32FC1);
    
    float value = m.at<float>(2,2);

    printf("Value is %f\n", value);

    cv::Mat m1 = cv::Mat::eye(10, 10, CV_32FC3);
    
    cv::Vec3f value_list = m1.at<cv::Vec3f>(2,2);

    printf("value_list[0] is %f\n", value_list[0]);
    printf("value_list[1] is %f\n", value_list[1]);
    printf("value_list[2] is %f\n", value_list[2]);


}

void dataStructure::test(){
    // defineAnMat();
    getMatrixValue();
}


