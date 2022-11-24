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
 * - Bachelor Thesis in Computer Science: [PDF TesiOnline](http://www.tesionline.it/default/tesi.asp?idt=57417)
 *
 * @section install_sec Installation 🚀
 * Note: Instructions for MacOS with Intel CPU / M1 chip
 *
 *
 * 1) Install [RealSense SDK 2.0](https://github.com/IntelRealSense/librealsense) and its own dependencies. The following guide is really helpful:
 * [build RealSense for macOS Monterey (Intel + Apple Silicon)](https://lightbuzz.com/realsense-macos/).
 * 
 * 2) Install [OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openpose) and its own dependencies. Useful guides: [build openpose with/without GPU support for macOS](https://medium.com/@alok.gandhi2002/build-openpose-with-without-gpu-support-for-macos-catalina-10-15-6-8fb936c9ab05#726f), [OpenPose for M1/Intel](https://blog.csdn.net/qq_27180763/article/details/126134888?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_utm_term~default-0-126134888-blog-122796729.pc_relevant_layerdownloadsortv1&spm=1001.2101.3001.4242.1&utm_relevant_index=3).
 *
 * In order to properly choose the `GPU_MODE` during OpenPose installation and/or in order to install OpenPose on other operating systems, check out this page: [OpenPose Docs](https://cmu-perceptual-computing-lab.github.io/openpose/web/html/doc/md_doc_installation_0_index.html). If you have MacOS with Intel CPU and a GPU that matches OpenPose prerequisites, then you can set `GPU_MODE` to `OPENCL` (GPU-accelerated, it is harder to install but provides a faster runtime speed).
 * Otherwise, if you have a MacOS with M1 chip, it's suggested to set `GPU_MODE` to `CPU_ONLY`.
 *
 * [CMake Settings for Intel](https://user-images.githubusercontent.com/41870472/197208265-82949343-d927-4894-ac0b-591c788e7974.png)
 *
 * [CMake Settings for >= M1](https://user-images.githubusercontent.com/41870472/197208278-4498ff62-0295-4eda-b6a1-023c2d89c0ec.png)
 *
 *
 * 3) Install [Apache Kafka](https://kafka.apache.org/), [Confluent](https://www.confluent.io/) and their own dependencies.
 * Confluent is not mandatory, but without it, you will have to set up the Kafka environment on your own. Useful guides:
 *
 * [how to install Apache Kafka on Mac](https://www.conduktor.io/kafka/how-to-install-apache-kafka-on-mac),
 * [how to install Confluent](https://docs.confluent.io/4.0.1/installation/installing_cp.html).
 * 
 * 4) Run the following command in your terminal:
 * ```
 * git clone --recursive git@github.com:dennewbie/AI_Watch_A1.git
 * ```
 * After that, remove all the files named `emptyFileForPadding.txt` in the cloned folder.
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
 * 8) Update `caffe lib` path inside `CMakeLists.txt`. Then run the following commands in your terminal:
 * 
 * ```
 * cmake .. && make -j `sysctl -n hw.logicalcpu`
 * ```
 *
 * 9) This step is optional. Run the following command in your terminal:
 *
 * ```
 * sudo make install
 * ```
 * 
 * 10) Now let's start the Kafka environment. Run the following commands in a new terminal session located on the parent folder of the `confluent` folder.
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
 *  ### Important #3 📌
 *  In order to improve speed and general performance, you could disable images' showing and change the number of frames captured per second. In this last option, capturing too few frames per second reduces output' quality. Furthermore, it's also possible to reduce OpenPose's network resolution, but a significant drawback is reduced accuracy.
 *
 *  ### Important #4 📌
 *  Place the camera in a way that it can "see" the left and the right wall of the room.
 * 
 * 11) Navigate to `http://localhost:9021` and create a new topic `topic1` with default settings. Now go to `/AI_Watch_A1/src/AI_Watch_A1/` and
 *     set up your [Kafka](https://github.com/edenhill/librdkafka) parameters within the `configuration_file.ini` file. At this point:
 *   - if internal OpenPose execution is chosen, then run the following command in your terminal:
 *  
 * ```
 * sudo ./AI_Watch_A1.bin --num_gpu 1 --num_gpu_start 2 --image_dir rs_images/rgb --write_json op_output/op --logging_level 255
 * ```
 *   - if external OpenPose execution is chosen, then set up your OpenPose parameters within the `conf.conf` file and run the following command in your terminal:
 *
 * ```
 * sudo ./AI_Watch_A1.bin
 * ```
 *
 *  Note that the internal OpenPose execution is suggested.
 *
 *
 * @section issues_sec Known issues ⚠️
 * 1) The module can rarely get stuck on the following invocation located in `RealSenseD435Manager::23`:
 *
     ```
     rs2::pipeline_profile myPipelineProfile = pipelineStream.start(myConfiguration);
     ```
 *
     This means some errors have occurred, due to the USB connection while starting the camera's environment. In order to fix that, just exit the program, unplug the RealSense camera from the USB cable, and connect it again.
 *
 *  @section sys_structure System Structure 🏛
 *  [A1 System Structure](https://github.com/dennewbie/AI_Watch_A1/blob/main/design/A1_details.png)
 *
 * @section tools_sec Tools 🛠
 * - [Intel RealSense SDK](https://github.com/IntelRealSense/librealsense)
 * - [OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openpose)
 * - [OpenCV](https://github.com/opencv/opencv)
 * - [OpenCL](https://www.khronos.org/opencl/)
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
 * @section Other_modules_sec Other modules
 * - [B1: anomaly detection + digital twin](https://github.com/Luruu/AI_Watch_B1)
 * - [C1: Unity3D rendering](https://github.com/RenatoEsposito1999/AIWatch_C1)
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
    const char * destinationKafkaTopic = "topic1";
    // Optimal resolution for D435: 848x480.
    unsigned int user_nFrame = 50, resX = 848, resY = 480;
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
