//
//  ImageManager.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 30/07/22.
//

#include "ImageManager.hpp"



void ImageManager::saveImage (std::string imageSavePath, const cv::Mat & imageToSave) {
    if (!(cv::imwrite(imageSavePath, imageToSave))) CV_Error(SAVE_IMAGE_ERROR, SAVE_IMAGE_SCOPE);
}



void ImageManager::loadImage(std::string imagePath, int loadType, cv::Mat & inputImage) {
    inputImage = cv::imread(imagePath, loadType);
    if (inputImage.empty()) {
        std::cout << "IMAGE NOT FOUND: " << imagePath << "\n";
        CV_Error(LOAD_IMAGE_ERROR, LOAD_IMAGE_SCOPE);
    }
}

void ImageManager::saveImages (const std::initializer_list <cv::Mat> & images, const std::initializer_list <std::string> & imagePaths) {
    auto imagesIterator = images.begin();
    auto imagePathsIterator = imagePaths.begin();
    for (unsigned char i = 0; i < images.size(); i++) {
        saveImage(* imagePathsIterator, * imagesIterator);
        imagePathsIterator++;
        imagesIterator++;
    }
}

void ImageManager::showImages (const std::initializer_list <cv::Mat> & images, const std::initializer_list <std::string> & windowNames) {
    auto imagesIterator = images.begin();
    auto windowNamesIterator = windowNames.begin();
    for (unsigned char i = 0; i < images.size(); i++) {
        cv::imshow(* windowNamesIterator, * imagesIterator);
        windowNamesIterator++;
        imagesIterator++;
    }
    cv::waitKey(1);
}

void ImageManager::releaseImages (const std::initializer_list <cv::Mat> & images) {
    for (auto singleImage : images) singleImage.release();
}
