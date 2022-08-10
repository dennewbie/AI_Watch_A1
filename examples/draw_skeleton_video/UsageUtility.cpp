//
//  UsageUtility.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 17/07/22.
//

#include "UsageUtility.hpp"



// Controllo dei parametri di input
void checkUsage(const int argc, const char ** argv, const int expected_argc, const char * expectedUsageMessage) {
    if (argc != expected_argc) {
        std::string buffer = "Usage: ./" + std::string(argv[0]) + std::string(expectedUsageMessage) + " -- " + std::string(CHECK_USAGE_SCOPE);
        CV_Error(CHECK_USAGE_ERROR, buffer);
    }
}

void loadImage(cv::String imagePath, int loadType, cv::Mat & inputImage, const int argc, const char ** argv, const int expected_argc, const char * expectedUsageMessage) {
    if (argc) {
        checkUsage(argc, argv, expected_argc, expectedUsageMessage);
        imagePath = std::string(argv[1]);
    }
 
    inputImage = cv::imread(imagePath, loadType);

    if (inputImage.empty()) CV_Error(LOAD_IMAGE_ERROR, LOAD_IMAGE_SCOPE);
}

void loadJSON (const char * filePathJSON, Json::Value & currentJSON) {
    Json::Reader readerJSON;
    
    std::ifstream streamJSON(std::string(filePathJSON), std::ifstream::binary);
    if (!(readerJSON.parse(streamJSON, currentJSON, false))) {
        std::cout  << "\n" << readerJSON.getFormattedErrorMessages() << "\n";
        CV_Error(LOAD_JSON_ERROR, LOAD_JSON_SCOPE);
    }
}
