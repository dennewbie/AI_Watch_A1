//
//  ImageManager.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 30/07/22.
//

#ifndef ImageManager_hpp
#define ImageManager_hpp

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>
#include <initializer_list>
#include "constants.hpp"



class ImageManager {
private:
    void saveImage      (std::string imageSavePath, const cv::Mat & imageToSave);
public:
    void loadImage      (std::string imagePath, int loadType, cv::Mat & inputImage);
    void saveImages     (const std::initializer_list <cv::Mat> & images, const std::initializer_list <std::string> & imagePaths);
    void showImages     (const std::initializer_list <cv::Mat> & images, const std::initializer_list <std::string> & windowNames);
    void releaseImages  (const std::initializer_list <cv::Mat> & images);
};

#endif /* ImageManager_hpp */

