//
//  draw_skeleton_video_refactoring.cpp
//  Disegno Body Keypoints and Edges con OpenCV a partire da più file JSON file prodotti da OpenPose 
//
//  Created by Denny Caruso on 06/07/22.
//

#include "UsageUtility.hpp"



const int expected_argc = 5;
const char * expectedUsageMessage = "Usage: sudo ./hello_librealsense2.bin <path/openpose folder/> <./path/openpose.bin> <path/images folder/> <path/JSON output folder/>";



int main (int argc, const char * argv[]) {
    rs2::pipeline pipelineStream;
    Json::Value currentJSON;
    float scale;
    unsigned short int resX = 640, resY = 360;
    unsigned int user_nFrame = 120;
    UsageUtility myUsageUtility = UsageUtility(argc, argv, expected_argc, expectedUsageMessage);
    myUsageUtility.startEnvironment(pipelineStream, & scale, resX, resY);
    
    while (true) {
        myUsageUtility.getVideoFrames(user_nFrame, pipelineStream, scale);
        myUsageUtility.getVideoBodyKeyPoints();
        myUsageUtility.showSkeleton(user_nFrame, currentJSON);
    }
    return EXIT_SUCCESS;
}