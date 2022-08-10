//
//  ImageManager.hpp
//  AI Watch A1
//
//  Created by Denny Caruso on 30/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

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



/**
 * @brief ImageManager class is a general-purpose class useful for operations on images such as loading, 
 * saving, showing and releasing attached memory.
 */
class ImageManager {
private:
    /**
     * @brief Saves a single image.
     * @param imageSavePath The path where to save the image.
     * @param imageToSave The image to save.
     */
    void saveImage      (std::string imageSavePath, const cv::Mat & imageToSave);
public:
    /**
     * @brief Loads a single image.
     * @param imagePath The path where the image has been saved on disk.
     * @param loadType How to load the image.
     * @param inputImage A reference to a cv::Mat object.
     */
    void loadImage      (std::string imagePath, int loadType, cv::Mat & inputImage);
    /**
     * @brief Saves multiple images.
     * @param images The images to save.
     * @param imagePaths The paths where to save the images.
     */
    void saveImages     (const std::initializer_list <cv::Mat> & images, const std::initializer_list <std::string> & imagePaths);
    /**
     * @brief Shows multiple images.
     * @param images  The images to show.
     * @param windowNames The window names in which images will be shown.
     */
    void showImages     (const std::initializer_list <cv::Mat> & images, const std::initializer_list <std::string> & windowNames);
    /**
     * @brief Releases multiple images.
     * @param images The images to release.
     */
    void releaseImages  (const std::initializer_list <cv::Mat> & images);
};

#endif /* ImageManager_hpp */

