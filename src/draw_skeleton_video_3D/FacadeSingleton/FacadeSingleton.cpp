//
//  FacadeSingleton.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 20/07/22.
//

#include "FacadeSingleton.hpp"



FacadeSingleton * FacadeSingleton::sharedInstance { nullptr };
std::mutex FacadeSingleton::singletonMutex;



void FacadeSingleton::setCameraManager (RealSenseManager * cameraManager) {
    this->cameraManager = cameraManager;
}

void FacadeSingleton::setOutputManager (OutputManager * outputManager) {
    this->outputManager = outputManager;
}

const int FacadeSingleton::get_argc (void) {
    return this->argc;
}

const int FacadeSingleton::get_expected_argc (void) {
    return this->expected_argc;
}

const char * FacadeSingleton::get_expectedUsageMessage (void) {
    return this->expectedUsageMessage;
}

void FacadeSingleton::checkUsage (void) {
    if (get_argc() != get_expected_argc()) {
        std::string buffer = "Usage: ./" + std::string(get_argv()[0]) + std::string(get_expectedUsageMessage()) + " -- " + std::string(CHECK_USAGE_SCOPE);
        CV_Error(CHECK_USAGE_ERROR, buffer);
    }
}



FacadeSingleton * FacadeSingleton::getInstance (const int argc, const char ** argv, const int expected_argc, const char * expectedUsageMessage) {
    std::lock_guard <std::mutex> lock(singletonMutex);
    if (sharedInstance == nullptr) sharedInstance = new FacadeSingleton(argc, argv, expected_argc, expectedUsageMessage);
    return sharedInstance;
}

FacadeSingleton * FacadeSingleton::getInstance (void) {
    std::lock_guard <std::mutex> lock(singletonMutex);
    if (sharedInstance == nullptr) return nullptr;
    return sharedInstance;
}

const char ** FacadeSingleton::get_argv (void) {
    return FacadeSingleton::argv;
}

RealSenseManager * FacadeSingleton::getCameraManager (void) {
    return this->cameraManager;
}

OutputManager * FacadeSingleton::getOutputManager (void) {
    return this->outputManager;
}

void FacadeSingleton::loadImage(std::string imagePath, int loadType, cv::Mat & inputImage) {
    inputImage = cv::imread(imagePath, loadType);
    if (inputImage.empty()) CV_Error(LOAD_IMAGE_ERROR, LOAD_IMAGE_SCOPE);
}

void FacadeSingleton::saveImage (std::string imageSavePath, cv::Mat & imageToSave) {
    if (!(cv::imwrite(imageSavePath, imageToSave))) CV_Error(SAVE_IMAGE_ERROR, SAVE_IMAGE_SCOPE);
}

cv::Mat FacadeSingleton::realsenseFrameToMat(const rs2::frame & singleFrame) {
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

void FacadeSingleton::startEnvironment (rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale, unsigned short int resX, unsigned short int resY) {
    FacadeSingleton::setCameraManager(new RealSenseD435Manager());
    FacadeSingleton::setOutputManager(new OutputManagerJSON());
    FacadeSingleton::getCameraManager()->startEnvironment(pipelineStream, color_intrin, scale, resX, resY);
    
    CleanCommand cleanCommand;
//    cleanCommand.executeCommand();
    std::stringstream cleanSK;
    cleanSK << "rm -r " << FacadeSingleton::get_argv()[3] << "sk/ > /dev/null && mkdir " << FacadeSingleton::get_argv()[3] << "sk";
    std::system(cleanSK.str().c_str());
}

void FacadeSingleton::getVideoFrames (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale) {
    // blocco openCV Manager
    for (int nFrame = 0; nFrame < user_nFrame; nFrame++) {
        rs2::depth_frame depthFrame = rs2::depth_frame(rs2::frame());
        rs2::frame colorFrame, colorizedDepthFrame;
        getCameraManager()->getVideoFrames(user_nFrame, pipelineStream, depthFrame, colorFrame, colorizedDepthFrame);
        auto cols = depthFrame.get_width();
        auto rows = depthFrame.get_height();
        
        cv::Mat colorImage = FacadeSingleton::realsenseFrameToMat(colorFrame);
        cv::Mat depthImage = FacadeSingleton::realsenseFrameToMat(depthFrame);
        cv::Mat colorizedDepthImage = FacadeSingleton::realsenseFrameToMat(colorizedDepthFrame);
        depthImage *= 1000.0 * scale;
        
        cv::Mat distanceImage = cv::Mat::zeros(rows, cols, CV_32FC1);
        for (int i = 0; i < cols; i++) for (int j = 0; j < rows; j++) distanceImage.at<float>(j, i) = (float) depthFrame.get_distance(i, j);
        
        std::stringstream colorImagePath, distanceImagePath, colorizedDepthImagePath;
        std::stringstream colorImageName, distanceImageName, colorizedDepthImageName;
        
        colorImageName << getCameraManager()->getFrameID() << "_Color";
        distanceImageName << getCameraManager()->getFrameID() << "_Distance";
        colorizedDepthImageName << getCameraManager()->getFrameID() << "_Depth";
        
        colorImagePath << FacadeSingleton::get_argv()[3] << "rgb/" << colorImageName.str() << ".png";
        distanceImagePath << FacadeSingleton::get_argv()[3] << "d/" << distanceImageName.str() << ".exr";
        colorizedDepthImagePath << FacadeSingleton::get_argv()[3] << "depth/" << colorizedDepthImageName.str() << ".png";
//        FacadeSingleton::saveImage(colorImagePath.str(), colorImage);
//        FacadeSingleton::saveImage(distanceImagePath.str(), distanceImage);
//        FacadeSingleton::saveImage(colorizedDepthImagePath.str(), colorizedDepthImage);
        colorImage.release();
        depthImage.release();
        distanceImage.release();
        colorizedDepthImage.release();
    }
    // fine blocco openCV Manager
}

void FacadeSingleton::getVideoBodyKeyPoints (void) {
    OpenPoseCommand openPoseCommand;
//    openPoseCommand.executeCommand();
}

// blocco openCV Manager
void FacadeSingleton::showSkeleton (unsigned int user_nFrame, Json::Value & currentJSON) {
    // comment here for complete test
    for (int nFrame = 0; nFrame < user_nFrame; nFrame++) {
        std::stringstream inputJsonFilePath, skeletonImagePath, colorImagePath, distanceImagePath, colorizedDepthImagePath, skeletonOnlyImagePath, outputJsonFilePath;
        inputJsonFilePath << FacadeSingleton::get_argv()[4] << "op/" << (getCameraManager()->getFrameID() - user_nFrame + nFrame) << "_Color_keypoints.json";
        
        OutputManagerJSON * outputManagerJSON = (OutputManagerJSON *) getOutputManager();
        outputManagerJSON->loadJSON(inputJsonFilePath.str(), currentJSON);
        Json::Value people = outputManagerJSON->getValueAt("people", currentJSON);
        colorImagePath << FacadeSingleton::get_argv()[3] << "rgb/" << (getCameraManager()->getFrameID() - user_nFrame + nFrame) << "_Color.png";
        distanceImagePath << FacadeSingleton::get_argv()[3] << "d/" << (getCameraManager()->getFrameID() - user_nFrame + nFrame) << "_Distance.exr";
        colorizedDepthImagePath << FacadeSingleton::get_argv()[3] << "depth/" << (getCameraManager()->getFrameID() - user_nFrame + nFrame) << "_Depth.png";
        
        cv::Mat colorImage, colorizedDepthImage;
        FacadeSingleton::loadImage(colorImagePath.str(), cv::IMREAD_COLOR, colorImage);
        cv::Mat distanceImage = cv::Mat(colorImage.rows, colorImage.cols, CV_32FC1);
        FacadeSingleton::loadImage(distanceImagePath.str(), cv::IMREAD_ANYCOLOR | cv::IMREAD_ANYDEPTH, distanceImage);
        FacadeSingleton::loadImage(colorizedDepthImagePath.str(), cv::IMREAD_COLOR, colorizedDepthImage);
        cv::imshow("Frame No Skeleton", colorImage);
        cv::imshow("Frame Colorized Depth", colorizedDepthImage);
        cv::Mat skeletonOnlyImage = cv::Mat::zeros(colorImage.rows, colorImage.cols, colorImage.type());
        
        for (Json::Value::ArrayIndex i = 0; i < people.size(); i++) {
            Json::Value singlePerson = outputManagerJSON->getValueAt("pose_keypoints_2d", i, people);
            Skeleton singlePersonSkeleton = Skeleton(colorImage, distanceImage, skeletonOnlyImage, singlePerson);
            singlePersonSkeleton.drawSkeleton();
            outputManagerJSON->makeOutputString(singlePersonSkeleton.getSkeletonPoints3D());
            outputJsonFilePath << FacadeSingleton::get_argv()[4] << "movement/frame" << nFrame << "_person" << i << "_" << JSON_FILE_PATH;
            outputManagerJSON->saveJSON(std::string(outputJsonFilePath.str()));
            outputJsonFilePath.str(std::string());
            outputJsonFilePath.clear();
            // kafka send
        }
        
        cv::imshow("Frame Skeleton Background Cut", skeletonOnlyImage);
        cv::imshow("Frame Skeleton", colorImage);
        skeletonOnlyImagePath << FacadeSingleton::get_argv()[3] << "sk/" << (getCameraManager()->getFrameID() - user_nFrame + nFrame) << "_sk.png";
        skeletonImagePath << FacadeSingleton::get_argv()[3] << "skeleton/" << (getCameraManager()->getFrameID() - user_nFrame + nFrame) << "_Skeleton.png";
        FacadeSingleton::saveImage(skeletonImagePath.str(), colorImage);
        FacadeSingleton::saveImage(skeletonOnlyImagePath.str(), skeletonOnlyImage);
        colorImage.release();
        distanceImage.release();
        colorizedDepthImage.release();
        skeletonOnlyImage.release();
        int key = cv::waitKey(1);
        // if ESC is pressed
        if (key == ESC_KEY) break;
    }
    // fine blocco openCV Manager
    
    MoveCommand moveCommand;
//    moveCommand.executeCommand();
}
