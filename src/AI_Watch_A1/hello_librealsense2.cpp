//
//  main.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 06/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#include "FacadeSingleton.hpp"



const int expected_argc = 5;
const char * expectedUsageMessage = "Usage: sudo ./hello_librealsense2.bin <path/openpose folder/> <./path/openpose.bin> "
                                    "<path/images folder/> <path/JSON output folder/>";



/**
 * The main function contains a sample code to launch the program.
 * @brief
 * Main
 *
 * @param argc Main argument count
 * @param argv Main argument values
 * @return int The return value for main indicates how the program exited. Normal exit is represented by a 0 return value from main.
 * Abnormal exit is signaled by a non-zero return, but there is no standard for how non-zero codes are interpreted.
 */
int main (int argc, char ** argv) {
    rs2::pipeline pipelineStream;
    // Scaling factor for distance frame and topic name for kafka connection.
    float scale;
    const char * destinationKafkaTopic = "t1";
    // Optimal resolution for D435: 848x480.
    unsigned  int user_nFrame = 30, resX = 848, resY = 480;
    struct rs2_intrinsics color_intrin;
    
    // Declaring a pointer to a FacadeSingleton object (it will be helpful to easily interact with all submodules) and starting D435 camera.
    FacadeSingleton * myUtility = FacadeSingleton::getInstance(expected_argc, expectedUsageMessage);
    myUtility->startEnvironment(pipelineStream, color_intrin, & scale, resX, resY, destinationKafkaTopic);

    /*
        An infinite loop that captures the frames seen from the camera, gives them to OpenPose, gets the output, and builds skeletons.
        After that, we create a properly formatted output JSON file and send it via Kafka for further elaboration.
    */
    while (true) {
        myUtility->getVideoFrames(user_nFrame, pipelineStream, scale);
        myUtility->getVideoBodyKeyPoints(& argc, & argv);
        myUtility->showSkeletons(user_nFrame);
//        myUtility->sendData(user_nFrame);
        myUtility->cleanBuildFolder();
//        break;
    }
    return EXIT_SUCCESS;
}
