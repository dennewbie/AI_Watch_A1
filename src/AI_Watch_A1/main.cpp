//
//  main.cpp
//  AI Watch A1
//
//  Created by Denny Caruso on 06/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

/** 
 * @mainpage AI Watch A1 documentation
 * @section intro_sec Introduction
 * This is the AI Watch A1 docum entation for C++. AI Watch A1 uses one Intel RealSense D435 camera and OpenPose in order to achieve
 * multi-person 3D skeleton detection. Once this task is completed, AI Watch A1 provides support to send each detected skeleton and 
 * its joint points' 3D coordinates (room and D435's details have to be specified) via Kafka, in order to let further detached 
 * computation possible.
 *
 * @section keynote_sec Keynote 📋
 * - [Keynote](https://github.com/dennewbie/AI_Watch_A1/blob/main/caruso_denny_tesi_bsc_cs.key)
 *
 * @section demo_sec Demo 💻
 * - [Demo #1](https://youtu.be/Ac0V8Dj0FbI)
 * - [Demo #2](https://youtu.be/pq3m9U3hRrQ)
 *
 * @section otherdoc_sec Other Docs 📜
 * - [Bachelor Thesis in Computer Science](https://github.com/dennewbie/AI_Watch_A1/blob/main/caruso_denny_tesi_bsc_cs.pdf)
 *
 * @section install_sec Installation 🚀
 * Note: Instructions for MacOS with Intel CPU
 *
 *
 * 1) Install [RealSense SDK 2.0](https://github.com/IntelRealSense/librealsense) and its own dependencies.
 * 
 * 2) Install [OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openpose) and its own dependencies.
 * 
 * 3) Install [Confluent](https://www.confluent.io/) and its own dependencies. This step is not mandatory, but without Confluent,
 * you will have to set up the Kafka environment.
 * 
 * 4) Run the following command in your terminal:
 * ```
 * git clone --recursive git@github.com:dennewbie/AI_Watch_A1.git
 * ```
 * 
 * 5) From `/AI_Watch_A1/src/AI_Watch_A1/` folder, run the following commands in your terminal:
 *  
 * ```
 * mkdir build && cd build
 * ```
 * 
 * 6) Copy OpenPose's `models` folder to the project's build folder.
 * 
 * 7) Copy OpenPose's `BoostConfig.cmake`, `FindGFlags.cmake` and `FindGlog.cmake` files  to the `build/cmake/modules/` folder.
 * 
 * 8) Run the following commands in your terminal:
 * 
 * ```
 * cmake .. && make -j `sysctl -n hw.logicalcpu`
 * ```
 * 
 * 9) Now let's start the Kafka environment. Run the following commands in a new terminal session located on the parent folder of the `confluent` folder.
 * Set the environment variable for the Confluent Platform home directory:
 *   ```
 *   export CONFLUENT_HOME=confluent-7.2.1
 *   ```
 *   Add the Confluent Platform bin directory to your PATH:
 * 
 *   ```
 *   export PATH=$PATH:$CONFLUENT_HOME/bin
 *   ```
 *   Test your installation by running the confluent command:
 *   ```
 *   confluent --help
 *   ```
 *   Your output should show the available commands for managing Confluent Platform.
 *
 *   Start Confluent Platform by using the Confluent CLI confluent local services start command. This command starts all of the 
 *   Confluent Platform components, including Kafka, ZooKeeper, Schema Registry, HTTP REST Proxy for Kafka, Kafka Connect, ksqlDB, 
 *   and Control Center. 
 *   ```
 *   confluent local services start
 *   ```
 *
 *   Your output should resemble:
 *   ```
 *   Starting Zookeeper
 *   Zookeeper is [UP]
 *   Starting Kafka
 *   Kafka is [UP]
 *   Starting Schema Registry
 *   Schema Registry is [UP]
 *   Starting Kafka REST
 *   Kafka REST is [UP]
 *   Starting Connect
 *   Connect is [UP]
 *   Starting KSQL Server
 *   KSQL Server is [UP]
 *   Starting Control Center
 *   Control Center is [UP]
 *   ```
 *
 *   ### Important #1 📌
 *   The confluent local commands are intended for a single-node development environment and are not suitable for a production environment. 
 *   The data that are produced are transient and are intended to be temporary. For production-ready workflows, check [Confluent website](https://www.confluent.io/).
 *
 *   ### Important #2 📌
 *   The Confluent CLI requires Java version 1.8 or 1.11.
 *   See [Confluent versions interoperability](https://docs.confluent.io/current/installation/versions-interoperability.html).
 * 
 * 10) Navigate to `http://localhost:9021` and create a new topic `t1` with default settings. Now go to `/AI_Watch_A1/src/AI_Watch_A1/` and 
 *     set up your [Kafka](https://github.com/edenhill/librdkafka) parameters within the `configuration_file.ini` file. At this point:
 *   - if internal OpenPose execution is chosen, then run the following command in your terminal:
 *  
 * ```
 * sudo ./AI_Watch_A1.bin --num_gpu 1 --num_gpu_start 2 --image_dir rs_images/rgb --write_json op_output/op --logging_level 255
 * ```
 *   - if external OpenPose execution is chosen, then set up your OpenPose parameters within the "conf.conf" file and run the following command in your terminal:
 *
 * ```
 * sudo ./AI_Watch_A1.bin
 * ```
 * 
 * @section tools_sec Tools 🛠
 * - [Intel RealSense SDK](https://github.com/IntelRealSense/librealsense)
 * - [OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openpose)
 * - [OpenCV](https://github.com/opencv/opencv)
 * - [Kafka](https://kafka.apache.org/)
 * - [Kafka C/C++ library](https://github.com/edenhill/librdkafka)
 * - [Confluent](https://www.confluent.io/)
 * - [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
 * - [Doxygen](https://doxygen.nl/)
 * - [StarUML](https://staruml.io/)
 * - [Sketch](https://www.sketch.com/)
 * 
 * @section contributing_sec Contributing 👨🏻👳🏾‍♂️👩🏼‍🦱👽
 * In order to contribute to AI Watch A1, please follow the [contribution guidelines](https://github.com/dennewbie/AI_Watch_A1/blob/main/CONTRIBUTING.md).
 * 
 * @section license_sec License ☢️
 * AI Watch A1 is licensed under the Apache License, Version 2.0. Copyright 2022. Please, see the 
 * [license](https://github.com/dennewbie/AI_Watch_A1/blob/main/LICENSE) for further details and the `/licenses` folder for the used libraries' licenses details.
 * 
 * @section contacts_sec Contacts 🪪
 * - [LinkedIn](https://www.linkedin.com/in/denny-caruso/)
 *
 * @section citation_sec Citation 📖
 *  ```
 *    @report{AIWatchA1,
 *        author = {Denny Caruso},
 *        title = {Multi-person 3D skeleton detection with depth cameras​},
 *        institution = {University of Naples, Parthenope},
 *        year = {2022}
 *    }
 *  ```
 * 
 * @section supervisor_sec Supervisor 
 * - [Dr. Alessio Ferone](https://www.researchgate.net/profile/Alessio-Ferone), CS Assistant Professor at the [University of Naples Parthenope](https://www.uniparthenope.it/).
 *
 * a.a. 2021/2022
 */



#include "FacadeSingleton.hpp"



const int expected_argc = 5;
const char * expectedUsageMessage = "Usage: sudo ./AI_Watch_A1.bin <path/openpose folder/> <./path/openpose.bin> "
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
    unsigned int user_nFrame = 60, resX = 848, resY = 480;
    const unsigned short int framesToSkip = 5;
    const float skeletonThreshold = 0.05;
    struct rs2_intrinsics color_intrin;
    Room room = CVPR_Lab();
    
    // Declaring a pointer to a FacadeSingleton object (it will be helpful to easily interact with all submodules) and starting D435 camera.
    FacadeSingleton * myUtility = FacadeSingleton::getInstance(expected_argc, expectedUsageMessage);
    myUtility->startEnvironment(pipelineStream, color_intrin, & scale, resX, resY, destinationKafkaTopic, room);

    /*
        An infinite loop that captures the frames seen from the camera, gives them to OpenPose, gets the output, and builds skeletons.
        After that, we create a properly formatted output JSON file and send it via Kafka for further elaboration.
    */
    while (true) {
        myUtility->getVideoFrames(user_nFrame, pipelineStream, scale, framesToSkip);
        myUtility->getVideoBodyKeyPoints(& argc, & argv);
        myUtility->showSkeletons(user_nFrame, skeletonThreshold);
        myUtility->sendData(user_nFrame);
        myUtility->cleanBuildFolder();
    }
    return EXIT_SUCCESS;
}
