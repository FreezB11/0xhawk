#pragma once
/*!
    @file image.h
    @details This file contains the support function written on top of opencv 
            for image processing.and training
*/
#include <opencv2/opencv.hpp>
#include <hawk/matrix.h>

namespace HAWK{
    namespace IMG{

template<typename Scalar = double>
Tensor<Scalar> load(const char* filename, int chn){
    cv::Mat img = cv::imread(filename, cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        throw std::runtime_error("Could not open or find the image");
    }
    int r = img.rows;
    int c = img.cols;
    
    matrix data(r, c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            // normalize [0,255] -> [0,1]
            data(i, j) = static_cast<double>(img.at<uint8_t>(i, j)) / 255.0; // Normalize to [0, 1]
        }
    }

    Tensor<Scalar> tensor(data);
    return tensor; 
}


    }
}