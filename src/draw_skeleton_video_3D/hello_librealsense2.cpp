//
//  main.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 06/07/22.
//

#include "FacadeSingleton.hpp"



const int expected_argc = 5;
const char * expectedUsageMessage = "Usage: sudo ./hello_librealsense2.bin <path/openpose folder/> <./path/openpose.bin> "
                                    "<path/images folder/> <path/JSON output folder/>";



int main (int argc, const char * argv[]) {
    rs2::pipeline pipelineStream;
    Json::Value currentJSON;
    float scale;
    // risoluzione ottimale D435: 848x480
    unsigned  int user_nFrame = 60, resX = 848, resY = 480;
    struct rs2_intrinsics color_intrin;
    FacadeSingleton * myUtility = FacadeSingleton::getInstance(argc, argv, expected_argc, expectedUsageMessage);
    myUtility->startEnvironment(pipelineStream, color_intrin, & scale, resX, resY);

    while (true) {
        myUtility->getVideoFrames(user_nFrame, pipelineStream, scale);
        myUtility->getVideoBodyKeyPoints();
        myUtility->showSkeleton(user_nFrame, currentJSON);
        break;
    }
    return EXIT_SUCCESS;
}

