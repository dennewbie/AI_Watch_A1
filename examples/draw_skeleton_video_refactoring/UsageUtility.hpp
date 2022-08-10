//
//  UsageUtility.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 17/07/22.
//

#ifndef UsageUtility_hpp
#define UsageUtility_hpp

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <librealsense2/rs.hpp>
#include "Skeleton.hpp"



static const short int CHECK_USAGE_ERROR = 1;
static const char * CHECK_USAGE_SCOPE = "usage";

static const short int LOAD_IMAGE_ERROR = 2;
static const char * LOAD_IMAGE_SCOPE = "Could not open or find the image";

static const short int SAVE_IMAGE_ERROR = 3;
static const char * SAVE_IMAGE_SCOPE = "Could not save the image on disk";

static const short int LOAD_JSON_ERROR = 4;
static const char * LOAD_JSON_SCOPE = "Could not open or find the JSON file";

static const short int ESC_KEY = 27;



class UsageUtility {
private:
    const int argc;
    const char ** argv;
    const int expected_argc;
    const char * expectedUsageMessage;
    long unsigned int frameID;
    rs2::align align;
    
    const int get_argc (void);
    const char ** get_argv (void);
    const int get_expected_argc (void);
    const char * get_expectedUsageMessage (void);
    
    void setFrameID (long unsigned int newFrameID);
    long unsigned int getFrameID (void);
    
    void set_align (rs2::align align);
    rs2::align get_align (void);
public:
    
    UsageUtility (const int argc = 0, const char ** argv = nullptr, const int expected_argc = 0, const char * expectedUsageMessage = nullptr) : argc(argc), argv(argv), expected_argc(expected_argc), expectedUsageMessage(expectedUsageMessage), align(RS2_STREAM_COLOR) {
        checkUsage();
        setFrameID(0);
    }
    // Controllo dei parametri di input
    void checkUsage (void);
    void loadImage (cv::String imagePath, int loadType, cv::Mat & inputImage);
    void saveImage (std::stringstream imageSavePath, cv::Mat & imageToSave);
    void loadJSON (const char * jsonFilePath, Json::Value & currentJSON);
    cv::Mat realsenseFrameToMat(const rs2::frame & singleFrame);
    void startEnvironment (rs2::pipeline & pipelineStream, float * scale, unsigned short int resX, unsigned short int resY);
    void getVideoFrames (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale);
    void getVideoBodyKeyPoints (void);
    void showSkeleton (unsigned int user_nFrame, Json::Value & currentJSON);
};



//extern void checkUsage (const int argc, const char ** argv, const int expected_argc, const char * expectedUsageMessage);
//extern void loadImage (cv::String imagePath, int loadType, cv::Mat & inputImage);
//extern void saveImage (cv::String imageSavePath, cv::Mat & imageToSave);
//extern void loadJSON (const char * jsonFilePath, Json::Value & currentJSON);
//extern cv::Mat realsenseFrameToMat(const rs2::frame & singleFrame);
//extern void startEnvironment (rs2::pipeline & pipelineStream, rs2::align * align, float * scale, const int argc = 0, const char ** argv = nullptr, const int expected_argc = 0, const char * expectedUsageMessage = nullptr);
//extern void getSkeleton (void);

#endif /* UsageUtility_hpp */
