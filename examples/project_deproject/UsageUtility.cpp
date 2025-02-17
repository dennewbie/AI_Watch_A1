//
//  UsageUtility.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 17/07/22.
//

#include "UsageUtility.hpp"



const int UsageUtility::get_argc (void) {
    return this->argc;
}

const char ** UsageUtility::get_argv (void) {
    return this->argv;
}

const int UsageUtility::get_expected_argc (void) {
    return this->expected_argc;
}

const char * UsageUtility::get_expectedUsageMessage (void) {
    return this->expectedUsageMessage;
}

void UsageUtility::setFrameID (long unsigned int frameID) {
    this->frameID = frameID;
}

long unsigned int UsageUtility::getFrameID (void) {
    return this->frameID;
}

void UsageUtility::set_align (rs2::align align) {
    this->align = align;
}

rs2::align UsageUtility::get_align (void) {
    return this->align;
}



void UsageUtility::checkUsage (void) {
    if (get_argc() != get_expected_argc()) {
        std::string buffer = "Usage: ./" + std::string(get_argv()[0]) + std::string(get_expectedUsageMessage()) + " -- " + std::string(CHECK_USAGE_SCOPE);
        CV_Error(CHECK_USAGE_ERROR, buffer);
    }
}

void UsageUtility::loadImage(std::string imagePath, int loadType, cv::Mat & inputImage) {
    inputImage = cv::imread(imagePath, loadType);
    if (inputImage.empty()) CV_Error(LOAD_IMAGE_ERROR, LOAD_IMAGE_SCOPE);
}

void UsageUtility::saveImage (std::string imageSavePath, cv::Mat & imageToSave) {
    if (!(cv::imwrite(imageSavePath, imageToSave))) CV_Error(SAVE_IMAGE_ERROR, SAVE_IMAGE_SCOPE);
}

void UsageUtility::loadJSON (std::string filePathJSON, Json::Value & currentJSON) {
    Json::Reader readerJSON;
    std::ifstream streamJSON(filePathJSON.c_str(), std::ifstream::binary);
    if (!(readerJSON.parse(streamJSON, currentJSON, false))) {
        std::cout  << "\n" << readerJSON.getFormattedErrorMessages() << "\n";
        CV_Error(LOAD_JSON_ERROR, LOAD_JSON_SCOPE);
    }
}

cv::Mat UsageUtility::realsenseFrameToMat(const rs2::frame & singleFrame) {
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

void UsageUtility::startEnvironment (rs2::pipeline & pipelineStream, float * scale, unsigned short int resX, unsigned short int resY) {
    rs2::log_to_console(RS2_LOG_SEVERITY_ERROR);
    rs2::colorizer colorMap;
    rs2::rates_printer printer;
    rs2::config myConfiguration;
    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_DEPTH, resX, resY, rs2_format::RS2_FORMAT_Z16);
    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_COLOR, resX, resY, rs2_format::RS2_FORMAT_RGB8);
    rs2::pipeline_profile myPipelineProfile = pipelineStream.start(myConfiguration);
    rs2::align align_to(RS2_STREAM_COLOR);
    set_align(rs2::align(align_to));
    rs2::depth_sensor sensor = myPipelineProfile.get_device().first<rs2::depth_sensor>();
    * scale = sensor.get_depth_scale();
    
    // Capture 30 frames to give autoexposure, etc. a chance to settle
    for (int i = 0; i < 30; i++) pipelineStream.wait_for_frames();
    
    std::stringstream cleanTerminalCommand;
    cleanTerminalCommand << "rm -r " << get_argv()[3] << "rgb/ > /dev/null && rm -r " << get_argv()[3] << "d/ > /dev/null && rm -r " << get_argv()[3] << "skeleton/ > /dev/null && rm -r " << get_argv()[3] << "videoframe/ > /dev/null && rm -r " << get_argv()[4] << " > /dev/null && mkdir " << get_argv()[3] << "rgb && mkdir " << get_argv()[3] << "d && mkdir " << get_argv()[3] << "videoframe && mkdir " << get_argv()[3] << "skeleton && mkdir " << get_argv()[4];
    std::system(cleanTerminalCommand.str().c_str());
}

void UsageUtility::getVideoFrames (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale) try {
    for (int nFrame = 0; nFrame < user_nFrame; nFrame++) {
        rs2::frameset streamData = pipelineStream.wait_for_frames(), alignedStreamData = get_align().process(streamData);
        rs2::depth_frame depth = alignedStreamData.get_depth_frame();
        rs2::frame color = alignedStreamData.get_color_frame();
        cv::Mat colorImage = realsenseFrameToMat(color);
        cv::Mat depthImage = realsenseFrameToMat(depth);
        
        depthImage *= 1000.0 * scale;
        
        auto cols = depth.get_width();
        auto rows = depth.get_height();
        cv::Mat distanceImage = cv::Mat::zeros(rows, cols, CV_32FC1);
        for (int i = 0; i < cols; i++) for (int j = 0; j < rows; j++) distanceImage.at<float>(j, i) = (float) depth.get_distance(i, j);
        
        std::stringstream colorImagePath, distanceImagePath;
        std::stringstream colorImageName, distanceImageName;
        
        colorImageName << getFrameID() << "_Color";
        distanceImageName << getFrameID() << "_Distance";
        colorImagePath << get_argv()[3] << "rgb/" << colorImageName.str() << ".png";
        distanceImagePath <<  get_argv()[3] << "d/" << distanceImageName.str() << ".exr";
        saveImage(colorImagePath.str(), colorImage);
        saveImage(distanceImagePath.str(), distanceImage);
        colorImage.release();
        depthImage.release();
        setFrameID(getFrameID() + 1);
    }
} catch (const rs2::error & e){
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n   " << e.what() << std::endl;
    CV_Error(RS_CAMERA_ERROR, RS_CAMERA_SCOPE);
} catch (const std::exception & e) {
    std::cerr << e.what() << std::endl;
    CV_Error(RS_CAMERA_ERROR, RS_CAMERA_SCOPE);
}

void UsageUtility::getVideoBodyKeyPoints (void) {
    std::stringstream firstTerminalCommand;
    firstTerminalCommand << "cd " << get_argv()[1] << " && " << get_argv()[2] << " --num_gpu 1 --num_gpu_start 2 --display 0 --render_pose 0 --image_dir " << get_argv()[3] << "rgb/" << " --write_json " << get_argv()[4] << " --logging_level 255 > /dev/null";
    std::system(firstTerminalCommand.str().c_str());
}

void UsageUtility::showSkeleton (unsigned int user_nFrame, Json::Value & currentJSON) {
    for (int nFrame = 0; nFrame < user_nFrame; nFrame++) {
        std::vector <SingleBodyKeypoint> bodyKeyPoints;
        std::vector <bool> bodyKeyPointsMap;
        std::stringstream jsonFilePath, skeletonImagePath, colorImagePath, distanceImagePath;
        jsonFilePath << get_argv()[4] << (getFrameID() - user_nFrame + nFrame) << "_Color_keypoints.json";
        
        loadJSON(jsonFilePath.str(), currentJSON);
        Json::Value people = currentJSON["people"];
        colorImagePath << get_argv()[3] << "rgb/" << (getFrameID() - user_nFrame + nFrame) << "_Color.png";
        distanceImagePath << get_argv()[3] << "d/" << (getFrameID() - user_nFrame + nFrame) << "_Distance.exr";
        
        cv::Mat colorImage;
        loadImage(colorImagePath.str(), cv::IMREAD_COLOR, colorImage);
        cv::Mat distanceImage = cv::Mat(colorImage.rows, colorImage.cols, CV_32FC1);
        loadImage(distanceImagePath.str(), cv::IMREAD_ANYCOLOR | cv::IMREAD_ANYDEPTH, distanceImage);
        cv::imshow("Frame No Skeleton", colorImage);
        for (Json::Value::ArrayIndex i = 0; i != people.size(); i++) {
            Json::Value singlePerson = (people[i])["pose_keypoints_2d"];
            Skeleton singlePersonSkeleton = Skeleton(colorImage, distanceImage, bodyKeyPoints, bodyKeyPointsMap, singlePerson);
            singlePersonSkeleton.drawSkeleton();
        }
        
        cv::imshow("Frame Skeleton", colorImage);
        skeletonImagePath << get_argv()[3] << "skeleton/" << (getFrameID() - user_nFrame + nFrame) << "_Skeleton.png";
        saveImage(skeletonImagePath.str(), colorImage);
        int key = cv::waitKey(1);
        // if ESC is pressed
        if (key == ESC_KEY) break;
    }
    
    std::stringstream secondTerminalCommand;
    secondTerminalCommand << "mv -v " << get_argv()[3] << "rgb/* " << get_argv()[3] << "videoframe/ > /dev/null";
    std::system(secondTerminalCommand.str().c_str());
}
