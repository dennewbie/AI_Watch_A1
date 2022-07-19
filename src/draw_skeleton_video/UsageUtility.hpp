//
//  UsageUtility.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 17/07/22.
//

#ifndef UsageUtility_hpp
#define UsageUtility_hpp

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <json/value.h>
#include <json/json.h>
#include <fstream>
#include <vector>

static const short int CHECK_USAGE_ERROR = 1;
static const char * CHECK_USAGE_SCOPE = "usage";

static const short int LOAD_IMAGE_ERROR = 2;
static const char * LOAD_IMAGE_SCOPE = "Could not open or find the image";

static const short int LOAD_JSON_ERROR = 3;
static const char * LOAD_JSON_SCOPE = "Could not open or find the JSON file";



extern void checkUsage (const int argc, const char ** argv, const int expected_argc, const char * expectedUsageMessage);
extern void loadImage (cv::String imagePath, int loadType, cv::Mat & inputImage, const int argc = 0, const char ** argv = nullptr, const int expected_argc = 0, const char * expectedUsageMessage = nullptr);
extern void loadJSON (const char * jsonFilePath, Json::Value & currentJSON);

#endif /* UsageUtility_hpp */
