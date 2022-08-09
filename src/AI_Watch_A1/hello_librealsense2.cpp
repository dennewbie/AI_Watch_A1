//
//  main.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 06/07/22.
//



/** 
 * @mainpage AI Watch A1 Documentation
 * @section intro_sec Introduction
 * This is the AI Watch A1 Documentation for C++
 * @section install_sec Installation
 * 1) Install RealSense SDK 2.0 and its own dependencies.
 * 
 * 2) Install OpenPose and its own dependencies.
 * 
 * 3) Go to the downloaded project folder.
 * 
 * 4) Set up your Kafka parameters within "configuration_file.ini"
 * 
 * 5) Run the following commands in your terminal:
 * 
 * mkdir build && cd build
 * 
 * 6) Copy OpenPose's "models" folder to the project's build folder.
 * 
 * 7) Copy OpenPose's "BoostConfig.cmake", "FindGFlags.cmake" and "FindGlog.cmake" files 
 * to the build/cmake/modules/ folder
 * 
 * 8) Run the following commands in your terminal:
 * 
 * cmake .. && make -j`sysctl -n hw.logicalcpu`
 * 
 * 9.1) If internal OpenPose execution is chosen, then run the following command in your terminal:
 * 
 * 
 * sudo ./hello_librealsense2.bin --num_gpu 1 --num_gpu_start 2 --image_dir rs_images/rgb --write_json op_output/op --logging_level 255
 * 
 * 9.2) If external OpenPose execution is chosen, then set up your OpenPose parameters 
 * within the "conf.conf" file, run the following command in your terminal:
 * 
 * 
 * sudo ./hello_librealsense2.bin
 */



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
