//
//  OpenCV_Manager.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "OpenCV_Manager.hpp"



cv::Mat OpenCV_Manager::realsenseFrameToMat (const rs2::frame & singleFrame) {
    rs2::video_frame videoFrame = singleFrame.as<rs2::video_frame>();
    const int frameWidth = videoFrame.get_width(), frameHeight = videoFrame.get_height();
    
    switch (singleFrame.get_profile().format()) {
        case RS2_FORMAT_BGR8:
            return cv::Mat(cv::Size(frameWidth, frameHeight), CV_8UC3, (void *) singleFrame.get_data(), cv::Mat::AUTO_STEP);
        case RS2_FORMAT_RGB8: {
            cv::Mat rgbFrame = cv::Mat(cv::Size(frameWidth, frameHeight), CV_8UC3, (void *) singleFrame.get_data(), cv::Mat::AUTO_STEP);
            cv::cvtColor(rgbFrame, rgbFrame, cv::COLOR_RGB2BGR);
            return rgbFrame;
        }
        case RS2_FORMAT_Z16:
            return cv::Mat(cv::Size(frameWidth, frameHeight), CV_16UC1, (void *) singleFrame.get_data(), cv::Mat::AUTO_STEP);
        case RS2_FORMAT_Y8:
            return cv::Mat(cv::Size(frameWidth, frameHeight), CV_8UC1, (void *) singleFrame.get_data(), cv::Mat::AUTO_STEP);
        default:
            throw std::runtime_error("Frame format is not supported yet!");
            break;
    }
}

void OpenCV_Manager::getVideoFramesCV (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale) {
    UsageManager * usageManagerInstance = UsageManager::getInstance();
    if (usageManagerInstance == nullptr) CV_Error(USAGE_MANAGER_NULLPTR_ERROR, USAGE_MANAGER_NULLPTR_SCOPE);
    char ** argv = * usageManagerInstance->get_argv();
    const char * imagesFolder = argv[imagesFolderOffset];
    FacadeSingleton * facadeSingletonInstance = FacadeSingleton::getInstance();
    if (facadeSingletonInstance == nullptr) CV_Error(FACADE_SINGLETON_NULLPTR_ERROR, FACADE_SINGLETON_NULLPTR_SCOPE);
    RealSenseManager * cameraManager = facadeSingletonInstance->getCameraManager();
    ImageManager * imageManager = facadeSingletonInstance->getImageManager();
    
    for (unsigned int nFrame = 0; nFrame < user_nFrame; nFrame++) {
        unsigned int frameID = cameraManager->getFrameID();
        rs2::depth_frame depthFrame = rs2::depth_frame(rs2::frame());
        rs2::frame colorFrame, colorizedDepthFrame;
        cameraManager->getVideoFramesRS(user_nFrame, pipelineStream, depthFrame, colorFrame, colorizedDepthFrame);
        int cols = depthFrame.get_width(), rows = depthFrame.get_height();

        cv::Mat colorImage = realsenseFrameToMat(colorFrame), distanceImage = cv::Mat::zeros(rows, cols, CV_32FC1);
        cv::Mat depthImage = realsenseFrameToMat(depthFrame), colorizedDepthImage = realsenseFrameToMat(colorizedDepthFrame);
        depthImage *= 1000.0 * scale;

        for (int i = 0; i < cols; i++) for (int j = 0; j < rows; j++) distanceImage.at <float> (j, i) = (float) depthFrame.get_distance(i, j);

        std::stringstream colorImagePath, distanceImagePath, colorizedDepthImagePath;
        colorImagePath <<           imagesFolder << "rgb/" <<   frameID << "_Color.png";
        distanceImagePath <<        imagesFolder << "d/" <<     frameID << "_Distance.exr";
        colorizedDepthImagePath <<  imagesFolder << "depth/" << frameID << "_Depth.png";
        imageManager->saveImages( { colorImage, distanceImage, colorizedDepthImage },
                                 { colorImagePath.str(), distanceImagePath.str(), colorizedDepthImagePath.str() } );
        imageManager->releaseImages( { colorImage, depthImage, distanceImage, colorizedDepthImage } );
    }
}

void OpenCV_Manager::showSkeletonsCV (unsigned int user_nFrame) {
    FacadeSingleton * facadeSingletonInstance = FacadeSingleton::getInstance();
    if (facadeSingletonInstance == nullptr) CV_Error(FACADE_SINGLETON_NULLPTR_ERROR, FACADE_SINGLETON_NULLPTR_SCOPE);
    RealSenseManager * cameraManager = facadeSingletonInstance->getCameraManager();
    OutputManagerJSON * outputManagerJSON = (OutputManagerJSON *) facadeSingletonInstance->getOutputManager();
    UsageManager * usageManagerInstance = facadeSingletonInstance->getUsageManager();
    if (usageManagerInstance == nullptr) CV_Error(USAGE_MANAGER_NULLPTR_ERROR, USAGE_MANAGER_NULLPTR_SCOPE);
    ImageManager * imageManager = facadeSingletonInstance->getImageManager();
    char ** argv = * usageManagerInstance->get_argv(), * imagesFolder = argv[imagesFolderOffset], * outputFolder = argv[outputFolderOffset];
    unsigned int frameID = cameraManager->getFrameID(), currentImageID;
    Json::Value currentJSON;
    
    for (unsigned int nFrame = 0; nFrame < user_nFrame; nFrame++) {
        std::stringstream inputJsonFilePath, skeletonImagePath, colorImagePath, distanceImagePath, colorizedDepthImagePath, skeletonOnlyImagePath, outputJsonFilePath;
        currentImageID = frameID - user_nFrame + nFrame;
        inputJsonFilePath << outputFolder << "op/" << nFrame << "_keypoints.json";
        
        if (outputManagerJSON->loadJSON(inputJsonFilePath.str(), currentJSON)) {
            Json::Value people = outputManagerJSON->getValueAt("people", currentJSON);
            colorImagePath << imagesFolder << "rgb/" << currentImageID << "_Color.png";
            distanceImagePath << imagesFolder << "d/" << currentImageID << "_Distance.exr";
            colorizedDepthImagePath << imagesFolder << "depth/" << currentImageID << "_Depth.png";
            
            cv::Mat colorImage, colorizedDepthImage;
            imageManager->loadImage(colorImagePath.str(), cv::IMREAD_COLOR, colorImage);
            cv::Mat distanceImage = cv::Mat(colorImage.rows, colorImage.cols, CV_32FC1);
            imageManager->loadImage(distanceImagePath.str(), cv::IMREAD_ANYCOLOR | cv::IMREAD_ANYDEPTH, distanceImage);
            imageManager->loadImage(colorizedDepthImagePath.str(), cv::IMREAD_COLOR, colorizedDepthImage);
            imageManager->showImages( { colorImage, colorizedDepthImage }, { "Frame No Skeleton", "Frame Colorized Depth" } );
            cv::Mat skeletonOnlyImage = cv::Mat::zeros(colorImage.rows, colorImage.cols, colorImage.type());
            
            outputManagerJSON->createJSON(people, colorImage, distanceImage, skeletonOnlyImage, currentImageID, outputFolder);
            
            imageManager->showImages( { skeletonOnlyImage, colorImage }, { "Frame Skeleton Background Cut", "Frame Skeleton" } );
            skeletonOnlyImagePath << imagesFolder << "sk/" << currentImageID << "_sk.png";
            skeletonImagePath << imagesFolder << "skeleton/" << currentImageID << "_Skeleton.png";
            imageManager->saveImages( { colorImage, skeletonOnlyImage }, { skeletonImagePath.str(), skeletonOnlyImagePath.str() } );
            imageManager->releaseImages( { colorImage, distanceImage, colorizedDepthImage, skeletonOnlyImage } );
        }
    }
}
