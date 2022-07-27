//
//  OpenCV_Manager.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "OpenCV_Manager.hpp"



void OpenCV_Manager::loadImage(std::string imagePath, int loadType, cv::Mat & inputImage) {
    inputImage = cv::imread(imagePath, loadType);
    if (inputImage.empty()) {
        std::cout << "IMAGE NOT FOUND: " << imagePath << "\n";
        CV_Error(LOAD_IMAGE_ERROR, LOAD_IMAGE_SCOPE);
    }
}

void OpenCV_Manager::saveImage (std::string imageSavePath, cv::Mat & imageToSave) {
    if (!(cv::imwrite(imageSavePath, imageToSave))) CV_Error(SAVE_IMAGE_ERROR, SAVE_IMAGE_SCOPE);
}

cv::Mat OpenCV_Manager::realsenseFrameToMat(const rs2::frame & singleFrame) {
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
    const char ** argv = usageManagerInstance->get_argv();
    const char * imagesFolder = argv[imagesFolderOffset];
    FacadeSingleton * facadeSingletonInstance = FacadeSingleton::getInstance();
    if (facadeSingletonInstance == nullptr) CV_Error(FACADE_SINGLETON_NULLPTR_ERROR, FACADE_SINGLETON_NULLPTR_SCOPE);
    RealSenseManager * cameraManager = facadeSingletonInstance->getCameraManager();
    
    for (int nFrame = 0; nFrame < user_nFrame; nFrame++) {
        unsigned long frameID = cameraManager->getFrameID();
        rs2::depth_frame depthFrame = rs2::depth_frame(rs2::frame());
        rs2::frame colorFrame, colorizedDepthFrame;
        cameraManager->getVideoFramesRS(user_nFrame, pipelineStream, depthFrame, colorFrame, colorizedDepthFrame);
        auto cols = depthFrame.get_width();
        auto rows = depthFrame.get_height();
        
        cv::Mat colorImage = realsenseFrameToMat(colorFrame);
        cv::Mat depthImage = realsenseFrameToMat(depthFrame);
        cv::Mat colorizedDepthImage = realsenseFrameToMat(colorizedDepthFrame);
        depthImage *= 1000.0 * scale;
        
        cv::Mat distanceImage = cv::Mat::zeros(rows, cols, CV_32FC1);
        for (int i = 0; i < cols; i++) for (int j = 0; j < rows; j++) distanceImage.at<float>(j, i) = (float) depthFrame.get_distance(i, j);
        
        std::stringstream colorImagePath, distanceImagePath, colorizedDepthImagePath;
        std::stringstream colorImageName, distanceImageName, colorizedDepthImageName;
        
        colorImageName << frameID << "_Color";
        distanceImageName << frameID << "_Distance";
        colorizedDepthImageName << frameID << "_Depth";
        
        colorImagePath << imagesFolder << "rgb/" << colorImageName.str() << ".png";
        distanceImagePath << imagesFolder << "d/" << distanceImageName.str() << ".exr";
        colorizedDepthImagePath << imagesFolder << "depth/" << colorizedDepthImageName.str() << ".png";
//        saveImage(colorImagePath.str(), colorImage);
//        saveImage(distanceImagePath.str(), distanceImage);
//        saveImage(colorizedDepthImagePath.str(), colorizedDepthImage);
        colorImage.release();
        depthImage.release();
        distanceImage.release();
        colorizedDepthImage.release();
    }
}

void OpenCV_Manager::showSkeleton (unsigned int user_nFrame, Json::Value & currentJSON) {
    UsageManager * usageManagerInstance = UsageManager::getInstance();
    if (usageManagerInstance == nullptr) CV_Error(USAGE_MANAGER_NULLPTR_ERROR, USAGE_MANAGER_NULLPTR_SCOPE);
    const char ** argv = usageManagerInstance->get_argv();
    const char * imagesFolder = argv[imagesFolderOffset];
    const char * outputFolder = argv[outputFolderOffset];
    FacadeSingleton * facadeSingletonInstance = FacadeSingleton::getInstance();
    if (facadeSingletonInstance == nullptr) CV_Error(FACADE_SINGLETON_NULLPTR_ERROR, FACADE_SINGLETON_NULLPTR_SCOPE);
    RealSenseManager * cameraManager = facadeSingletonInstance->getCameraManager();
    unsigned long frameID = cameraManager->getFrameID(), currentImageID;
    
    for (int nFrame = 0; nFrame < user_nFrame; nFrame++) {
        std::stringstream inputJsonFilePath, skeletonImagePath, colorImagePath, distanceImagePath, colorizedDepthImagePath, skeletonOnlyImagePath, outputJsonFilePath;
        currentImageID = frameID - user_nFrame + nFrame;
        inputJsonFilePath << outputFolder << "op/" << currentImageID << "_Color_keypoints.json";

        OutputManagerJSON * outputManagerJSON = (OutputManagerJSON *) FacadeSingleton::getInstance()->getOutputManager();
        if (outputManagerJSON->loadJSON(inputJsonFilePath.str(), currentJSON)) {
            Json::Value people = outputManagerJSON->getValueAt("people", currentJSON);
            colorImagePath << imagesFolder << "rgb/" << currentImageID << "_Color.png";
            distanceImagePath << imagesFolder << "d/" << currentImageID << "_Distance.exr";
            colorizedDepthImagePath << imagesFolder << "depth/" << currentImageID << "_Depth.png";
            
            cv::Mat colorImage, colorizedDepthImage;
            loadImage(colorImagePath.str(), cv::IMREAD_COLOR, colorImage);
            cv::Mat distanceImage = cv::Mat(colorImage.rows, colorImage.cols, CV_32FC1);
            loadImage(distanceImagePath.str(), cv::IMREAD_ANYCOLOR | cv::IMREAD_ANYDEPTH, distanceImage);
            loadImage(colorizedDepthImagePath.str(), cv::IMREAD_COLOR, colorizedDepthImage);
            cv::imshow("Frame No Skeleton", colorImage);
            cv::imshow("Frame Colorized Depth", colorizedDepthImage);
            cv::Mat skeletonOnlyImage = cv::Mat::zeros(colorImage.rows, colorImage.cols, colorImage.type());
            
            for (Json::Value::ArrayIndex i = 0; i < people.size(); i++) {
                Json::Value singlePerson = outputManagerJSON->getValueAt("pose_keypoints_2d", i, people);
                Skeleton singlePersonSkeleton = Skeleton(colorImage, distanceImage, skeletonOnlyImage, singlePerson);
                singlePersonSkeleton.drawSkeleton();
                
                outputManagerJSON->makeOutputString(* singlePersonSkeleton.getSkeletonPoints3D());
                outputJsonFilePath << outputFolder << "movement/frame" << nFrame << "_person" << i << "_" << JSON_FILE_PATH;
                outputManagerJSON->saveJSON(std::string(outputJsonFilePath.str()));
                outputJsonFilePath.str(std::string());
                outputJsonFilePath.clear();
                
                // kafka send
            }
            
            cv::imshow("Frame Skeleton Background Cut", skeletonOnlyImage);
            cv::imshow("Frame Skeleton", colorImage);
            skeletonOnlyImagePath << imagesFolder << "sk/" << currentImageID << "_sk.png";
            skeletonImagePath << imagesFolder << "skeleton/" << currentImageID << "_Skeleton.png";
            saveImage(skeletonImagePath.str(), colorImage);
            saveImage(skeletonOnlyImagePath.str(), skeletonOnlyImage);
            colorImage.release();
            distanceImage.release();
            colorizedDepthImage.release();
            skeletonOnlyImage.release();
            int key = cv::waitKey(1);
            // if ESC is pressed
            if (key == ESC_KEY) break;
        }
    }
}
