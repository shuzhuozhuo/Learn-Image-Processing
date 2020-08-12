#include <iostream>
#include <assert.h>
#include "opencv4/opencv2/core/core.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/core/hal/interface.h"
#include "binary_image.h"
#include "tools.h"
#include "math.h"



cv::Mat binImg::binaryImageWithThreshold(const cv::Mat& inputImage, int thresh1, int thresh2=255, bool isShow=false){

    assert(inputImage.dims == 2);

    cv::Mat mask;
    cv::Mat binary_image;
    cv::bitwise_and(inputImage > thresh1, inputImage < thresh2, mask);
    mask.convertTo(binary_image, CV_8U);

    if(isShow){
        tools::showImage("ImageThresh", binary_image);
    }

    return binary_image;
}

cv::Mat binImg::binaryImageWithOtus(const cv::Mat& inputImage, bool isShow=false){

    assert(inputImage.dims == 2);

    float max_std = -1;
    cv::Mat mask;
    cv::Mat temp_binary_image;
    cv::Mat binary_image;

    cv::Scalar sum_one, sum_zero;
    float mean_one_pixels, mean_zero_pixels, class_std;

    int total_pixels = inputImage.total();
    float weight_one, weight_zero, pixels_mean;

    for(int thresh = 0; thresh < 256; thresh++){

        temp_binary_image = binImg::binaryImageWithThreshold(inputImage, thresh);
        mask = temp_binary_image / 255;

        sum_one = cv::sum(mask);
        sum_zero = cv::sum( 1 - mask );

        if(sum_one(0) == 0 || sum_zero(0)==0){
            continue; // mask is pure color.
        }

        weight_one = sum_one(0) / total_pixels;
        weight_zero = sum_zero(0) / total_pixels;

        mean_one_pixels = cv::sum(temp_binary_image.mul(mask))(0) / sum_one(0);
        mean_zero_pixels = cv::sum(temp_binary_image.mul(1 - mask))(0) / sum_zero(0);
    
        pixels_mean = weight_one * mean_one_pixels + weight_zero * mean_zero_pixels;

        class_std = weight_one * pow((mean_one_pixels - pixels_mean), 2) +
                        weight_zero * pow((mean_zero_pixels - pixels_mean), 2);

        if(class_std > max_std){
            max_std = class_std;
            binary_image = temp_binary_image;
        }
    }

    if(max_std < 0){
        inputImage.copyTo(binary_image); // reture pure color image directly
    }

    if(isShow) tools::showImage("ImageOtus", binary_image);

    return binary_image;
}


cv::Mat binImg::BinaryImageAdative(const cv::Mat& inputImage, bool isShow=false, int windowSize=9, float t=0.15){
    assert(windowSize % 2 == 1);
    
    cv::Size img_size = inputImage.size();

    int width, height, left, right, top, bottom, count, interal_value;
    int radius = (windowSize - 1) / 2;
    width = img_size.width; height = img_size.height;

    cv::Mat inter_mat;
    cv::Mat binary_image(height, width, CV_8UC1);

    cv::integral(inputImage, inter_mat, -1);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            
            top = (i - radius) > 0 ? i - radius + 1 :  1;
            bottom = (i + radius) <= height ? i + radius : height;
            
            left = (j - radius) > 0 ? j - radius + 1 : 1;
            right = (j + radius) <= width - 1 ? j + radius : width - 1;

            count = (bottom - top) * (right - left);
            // printf("Left: %d, Right: %d, Top: %d, Bottom: %d", left, right, top, bottom);
            // printf("inter_mat.at<float>(bottom, right) %d", inter_mat.at<int>(bottom, right));
            interal_value = inter_mat.at<int>(bottom, right) - inter_mat.at<int>(top - 1, right)
                     - inter_mat.at<int>(bottom, left - 1 ) + inter_mat.at<int>(top - 1, left - 1);

            // printf("interal_value * (1- t) %d \n", interal_value);
            // printf("inputImage.at<uint8_t>(i, j) * count %d\n", inputImage.at<uint8_t>(i, j) * count);

            if(inputImage.at<uint8_t>(i, j) * count > interal_value * (1- t)){
                binary_image.at<uint8_t>(i, j) = 0;
            }
            else binary_image.at<uint8_t>(i, j) = 255;
        }
    }

    if(isShow) tools::showImage("Adative", binary_image);
    return binary_image;


}



void binImg::test(){
    char image_path[] = "/home/pi/Pictures/good_label.png";
    cv::Mat image = cv::imread(image_path);

    cv::Mat gray;

    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // binImg::binaryImageWithThreshold(gray, 128, 255, true);
    binImg::binaryImageWithOtus(gray, true);
    binImg::BinaryImageAdative(gray, true, 7, 0.25);

    cv::Mat cv_binary;
    cv::adaptiveThreshold(gray, cv_binary, 255.0, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 3, 5);
    tools::showImage("cvbin", cv_binary);


    }

