//
//  main.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 06/07/22.
//
//
//#include <librealsense2/rs.hpp>
//#include <iostream>
//
//int main(int argc, char * argv[]) try {
//    rs2::pipeline myPipeline;
//    myPipeline.start();
//    while (true) {
//        rs2::frameset frames = myPipeline.wait_for_frames();
//        rs2::depth_frame depth = frames.get_depth_frame();
//
//        auto width = depth.get_width();
//        auto height = depth.get_height();
//        float dist_to_center = depth.get_distance(width / 2, height / 2);
//        std::cout << "The camera is facing an object " << dist_to_center << " meters away \r";
//    }
//
//    return EXIT_SUCCESS;
//} catch (const rs2::error & e) {
//    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
//    return EXIT_FAILURE;
//} catch (const std::exception& e) {
//    std::cerr << e.what() << std::endl;
//    return EXIT_FAILURE;
//}




//
//// License: Apache 2.0. See LICENSE file in root directory.
//// Copyright(c) 2017 Intel Corporation. All Rights Reserved.
//
//#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
//#include "example.hpp"          // Include short list of convenience functions for rendering
//
//// Capture Example demonstrates how to
//// capture depth and color video streams and render them to the screen
//int main(int argc, char * argv[]) try
//{
//    rs2::log_to_console(RS2_LOG_SEVERITY_ERROR);
//    // Create a simple OpenGL window for rendering:
//    window app(3072, 1920, "RealSense Capture RGB && DEPTH");
//
//    // Declare depth colorizer for pretty visualization of depth data
//    rs2::colorizer color_map;
//    // Declare rates printer for showing streaming rates of the enabled streams.
//    rs2::rates_printer printer;
//
//    // Declare RealSense pipeline, encapsulating the actual device and sensors
//    rs2::pipeline pipe;
//
//    // Start streaming with default recommended configuration
//    // The default video configuration contains Depth and Color streams
//    // If a device is capable to stream IMU data, both Gyro and Accelerometer are enabled by default
//
//    pipe.start();
//
//    while (app) // Application still alive?
//    {
//
//        rs2::frameset frames = pipe.wait_for_frames();
//        rs2::depth_frame depth = frames.get_depth_frame();
//        rs2::frame color = frames.get_color_frame();
//        std::map<int, rs2::frame> framesMap;
//        framesMap.insert({1, color});
//        framesMap.insert({2, depth});
//        app.show(framesMap);
//
////        rs2::frameset data = pipe.wait_for_frames().   // Wait for next set of frames from the camera
////                             apply_filter(printer).     // Print each enabled stream frame rate
////                             apply_filter(color_map);   // Find and colorize the depth data
////
////        // The show method, when applied on frameset, break it to frames and upload each frame into a gl textures
////        // Each texture is displayed on different viewport according to it's stream unique id
////        app.show(data);
//    }
//
//    return EXIT_SUCCESS;
//}
//catch (const rs2::error & e)
//{
//    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
//    return EXIT_FAILURE;
//}
//catch (const std::exception& e)
//{
//    std::cerr << e.what() << std::endl;
//    return EXIT_FAILURE;
//}


//
//
//// License: Apache 2.0. See LICENSE file in root directory.
//// Copyright(c) 2015-2017 Intel Corporation. All Rights Reserved.
//
//#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
//
//#include <fstream>              // File IO
//#include <iostream>             // Terminal IO
//#include <sstream>              // Stringstreams
//
//// 3rd party header for writing png files
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
//
//// Helper function for writing metadata to disk as a csv file
//void metadata_to_csv(const rs2::frame& frm, const std::string& filename);
//
//// This sample captures 30 frames and writes the last frame to disk.
//// It can be useful for debugging an embedded system with no display.
//int main(int argc, char * argv[]) try
//{
//    // Declare depth colorizer for pretty visualization of depth data
//    rs2::colorizer color_map;
//    rs2::frameset myVideo;
//
//
//    // Declare RealSense pipeline, encapsulating the actual device and sensors
//    rs2::pipeline pipe;
//    rs2::config cfg;
//    cfg.enable_stream(rs2_stream::RS2_STREAM_DEPTH, 640, 360, rs2_format::RS2_FORMAT_Z16);
//    cfg.enable_stream(rs2_stream::RS2_STREAM_COLOR, 640, 360, rs2_format::RS2_FORMAT_RGB8);
//    rs2::pipeline_profile profile = pipe.start(cfg);
//    // Start streaming with default recommended configuration
//
//    // Capture 30 frames to give autoexposure, etc. a chance to settle
//    for (auto i = 0; i < 30; ++i) pipe.wait_for_frames();
//
//    // Wait for the next set of frames from the camera. Now that autoexposure, etc.
//    // has settled, we will write these to disk
//    for (auto&& frame : pipe.wait_for_frames())
//    {
//        // We can only save video frames as pngs, so we skip the rest
//        if (auto vf = frame.as<rs2::video_frame>())
//        {
//            auto stream = frame.get_profile().stream_type();
//            // Use the colorizer to get an rgb image for the depth stream
//            if (vf.is<rs2::depth_frame>()) vf = color_map.process(frame);
//
//            // Write images to disk
//            std::stringstream png_file;
//            png_file << "rs-save-to-disk-output-" << vf.get_profile().stream_name() << ".png";
//            stbi_write_png(png_file.str().c_str(), vf.get_width(), vf.get_height(),
//                           vf.get_bytes_per_pixel(), vf.get_data(), vf.get_stride_in_bytes());
//            std::cout << "Saved " << png_file.str() << std::endl;
//
//            // Record per-frame metadata for UVC streams
//            std::stringstream csv_file;
//            csv_file << "rs-save-to-disk-output-" << vf.get_profile().stream_name()
//                     << "-metadata.csv";
//            metadata_to_csv(vf, csv_file.str());
//        }
//    }
//
//    return EXIT_SUCCESS;
//}
//catch(const rs2::error & e)
//{
//    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
//    return EXIT_FAILURE;
//}
//catch(const std::exception & e)
//{
//    std::cerr << e.what() << std::endl;
//    return EXIT_FAILURE;
//}
//
//void metadata_to_csv(const rs2::frame& frm, const std::string& filename)
//{
//    std::ofstream csv;
//
//    csv.open(filename);
//
//    //    std::cout << "Writing metadata to " << filename << endl;
//    csv << "Stream," << rs2_stream_to_string(frm.get_profile().stream_type()) << "\nMetadata Attribute,Value\n";
//
//    // Record all the available metadata attributes
//    for (size_t i = 0; i < RS2_FRAME_METADATA_COUNT; i++)
//    {
//        if (frm.supports_frame_metadata((rs2_frame_metadata_value)i))
//        {
//            csv << rs2_frame_metadata_to_string((rs2_frame_metadata_value)i) << ","
//                << frm.get_frame_metadata((rs2_frame_metadata_value)i) << "\n";
//        }
//    }
//
//    csv.close();
//}


//
//// conversione con openCV
//
//#include <librealsense2/rs.hpp>
//#include <iostream>
//#include "example.hpp"
//#include <opencv2/opencv.hpp>
//#include <openpose/headers.hpp>
//
//// Convert rs2::frame to cv::Mat
//cv::Mat realsenseFrameToMat(const rs2::frame & singleFrame) {
//    rs2::video_frame videoFrame = singleFrame.as<rs2::video_frame>();
//    const int frameWidth = videoFrame.get_width(), frameHeight = videoFrame.get_height();
//
//    switch (singleFrame.get_profile().format()) {
//        case RS2_FORMAT_BGR8:
//            return cv::Mat(cv::Size(frameWidth, frameHeight), CV_8UC3, (void *) singleFrame.get_data(), cv::Mat::AUTO_STEP);
//        case RS2_FORMAT_RGB8: {
//            cv::Mat rgbFrame = cv::Mat(cv::Size(frameWidth, frameHeight), CV_8UC3, (void*) singleFrame.get_data(), cv::Mat::AUTO_STEP);
//            cv::cvtColor(rgbFrame, rgbFrame, cv::COLOR_RGB2BGR);
//            return rgbFrame;
//        }
//        case RS2_FORMAT_Z16:
//            return cv::Mat(cv::Size(frameWidth, frameHeight), CV_16UC1, (void *) singleFrame.get_data(), cv::Mat::AUTO_STEP);
//        case RS2_FORMAT_Y8:
//            return cv::Mat(cv::Size(frameWidth, frameHeight), CV_8UC1, (void *) singleFrame.get_data(), cv::Mat::AUTO_STEP);
//        default:
//            throw std::runtime_error("Frame format is not supported yet!");
//            break;
//    }
//}
//
//int main (int argc, char * argv[]) try {
//    rs2::log_to_console(RS2_LOG_SEVERITY_ERROR);
//    rs2::colorizer colorMap;
//    rs2::rates_printer printer;
//    rs2::config myConfiguration;
//    rs2::pipeline pipelineStream;
//    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_DEPTH, 640, 360, rs2_format::RS2_FORMAT_Z16);
//    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_COLOR, 640, 360, rs2_format::RS2_FORMAT_RGB8);
//
//    rs2::pipeline_profile myPipelineProfile = pipelineStream.start(myConfiguration);
//    rs2::align alignment(RS2_STREAM_COLOR);
//    rs2::depth_sensor sensor = myPipelineProfile.get_device().first<rs2::depth_sensor>();
//    float scale = sensor.get_depth_scale();
//
//    while (true) {
//        rs2::frameset streamData = pipelineStream.wait_for_frames(), alignedStreamData = alignment.process(streamData);
//        rs2::frame colorizedDepth = alignedStreamData.get_depth_frame().apply_filter(colorMap);
//        rs2::frame depth = alignedStreamData.get_depth_frame();
//        rs2::frame color = alignedStreamData.get_color_frame();
//
//        cv::Mat colorImage = realsenseFrameToMat(color);
//        cv::Mat depthImage = realsenseFrameToMat(depth);
//        cv::Mat colorizedDepthImage = realsenseFrameToMat(colorizedDepth);
//        depthImage *= 1000.0 * scale;
//
//        imshow("Depth Video", depthImage);
//        imshow("Depth Video Colorized", colorizedDepthImage);
//        imshow("Color Video Colorized", colorImage);
//        std::cout << "DEPTH: " << depthImage << "\nDEPTH COLOR: " <<colorizedDepthImage << "\nCOLOR: " << colorImage << "\n\n";
//        int key = cv::waitKey(0);
//        // if ESC is pressed
//        if (key == 27) break;
//    }
//    return EXIT_SUCCESS;
//} catch (const rs2::error & e){
//    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n   " << e.what() << std::endl;
//    return EXIT_FAILURE;
//} catch (const std::exception & e) {
//    std::cerr << e.what() << std::endl;
//    return EXIT_FAILURE;
//}







////
////  json_reader.cpp
////  Lettura di un file JSON in C++
////
////  Created by Denny Caruso on 10/07/22
////
//
//#include <iostream>
//#include <json/json.h>
//#include <json/value.h>
//#include <fstream>
//#include <string>
//
//int main (int argc, char * argv[]) {
//    Json::Value actualJSON;   // will contains the root value after parsing.
//    Json::Reader readerJSON;
//    std::ifstream streamJSON("op_output/cavani_keypoints.json", std::ifstream::binary);
//    if (!(readerJSON.parse(streamJSON, actualJSON, false))) std::cout  << readerJSON.getFormattedErrorMessages() << "\n";
//    std::cout << actualJSON;
//    return EXIT_SUCCESS;
//}



//
//// ----------------------------- OpenPose C++ API Tutorial - Example 1 - Body from image -----------------------------
//// It reads an image, process it, and displays it with the pose keypoints.
//
//// Third-party dependencies
//#include <opencv2/opencv.hpp>
//// Command-line user interface
//#define OPENPOSE_FLAGS_DISABLE_POSE
//#include <openpose/flags.hpp>
//// OpenPose dependencies
//#include <openpose/headers.hpp>
//
//// Custom OpenPose flags
//// Producer
//DEFINE_string(image_path, "examples/media/COCO_val2014_000000000192.jpg",
//    "Process an image. Read all standard formats (jpg, png, bmp, etc.).");
//// Display
//DEFINE_bool(no_display,                 false,
//    "Enable to disable the visual display.");
//
//// This worker will just read and return all the jpg files in a directory
//void display(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr) {
//    try {
//        // User's displaying/saving/other processing here
//            // datum.cvOutputData: rendered frame with pose or heatmaps
//            // datum.poseKeypoints: Array<float> with the estimated pose
//        if (datumsPtr != nullptr && !datumsPtr->empty()) {
//            // Display image
//            const cv::Mat cvMat = OP_OP2CVCONSTMAT(datumsPtr->at(0)->cvOutputData);
//            if (!cvMat.empty()) {
//                cv::imshow(OPEN_POSE_NAME_AND_VERSION + " - Tutorial C++ API", cvMat);
//                cv::waitKey(0);
//            } else {
//                op::opLog(std::string("Empty cv::Mat as output."));
//            }
//        } else {
//            op::opLog(std::string("Nullptr or empty datumsPtr found."));
//        }
//    } catch (const std::exception& e) {
//        op::error(e.what());
//    }
//}
//
//void printKeypoints(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr) {
//    try {
//        // Example: How to use the pose keypoints
//        if (datumsPtr != nullptr && !datumsPtr->empty()) {
//            // Alternative 1
//            op::opLog("Body keypoints: " + datumsPtr->at(0)->poseKeypoints.toString(), op::Priority::High);
//
//            // // Alternative 2
//            // op::opLog(datumsPtr->at(0)->poseKeypoints, op::Priority::High);
//
//            // // Alternative 3
//            // std::cout << datumsPtr->at(0)->poseKeypoints << std::endl;
//
//            // // Alternative 4 - Accessing each element of the keypoints
//            // op::opLog("\nKeypoints:", op::Priority::High);
//            // const auto& poseKeypoints = datumsPtr->at(0)->poseKeypoints;
//            // op::opLog("Person pose keypoints:", op::Priority::High);
//            // for (auto person = 0 ; person < poseKeypoints.getSize(0) ; person++)
//            // {
//            //     op::opLog("Person " + std::to_string(person) + " (x, y, score):", op::Priority::High);
//            //     for (auto bodyPart = 0 ; bodyPart < poseKeypoints.getSize(1) ; bodyPart++)
//            //     {
//            //         std::string valueToPrint;
//            //         for (auto xyscore = 0 ; xyscore < poseKeypoints.getSize(2) ; xyscore++)
//            //             valueToPrint += std::to_string(   poseKeypoints[{person, bodyPart, xyscore}]   ) + " ";
//            //         op::opLog(valueToPrint, op::Priority::High);
//            //     }
//            // }
//            // op::opLog(" ", op::Priority::High);
//        } else {
//            op::opLog(std::string("Nullptr or empty datumsPtr found."));
//        }
//    } catch (const std::exception& e) {
//        op::error(e.what());
//    }
//}
//
//int tutorialApiCpp() {
//    try {
//        op::opLog(std::string("Starting OpenPose demo..."));
//        const auto opTimer = op::getTimerInit();
//
//        // Configuring OpenPose
//        op::opLog(std::string("Configuring OpenPose..."));
//        op::Wrapper opWrapper{op::ThreadManagerMode::Asynchronous};
//        // Set to single-thread (for sequential processing and/or debugging and/or reducing latency)
//        if (FLAGS_disable_multi_thread) opWrapper.disableMultiThreading();
//
//        // Starting OpenPose
//        op::opLog("Starting thread(s)...", op::Priority::High);
//        opWrapper.start();
//
//        // Process and display image
//        const cv::Mat cvImageToProcess = cv::imread(FLAGS_image_path);
//        const op::Matrix imageToProcess = OP_CV2OPCONSTMAT(cvImageToProcess);
//        auto datumProcessed = opWrapper.emplaceAndPop(imageToProcess);
//        if (datumProcessed != nullptr) {
//            printKeypoints(datumProcessed);
//            if (!FLAGS_no_display) display(datumProcessed);
//        } else {
//            op::opLog("Image could not be processed.", op::Priority::High);
//        }
//        // Measuring total time
//        op::printTime(opTimer, "OpenPose demo successfully finished. Total time: ", " seconds.", op::Priority::High);
//
//        // Return
//        return 0;
//    } catch (const std::exception&) {
//        return -1;
//    }
//}
//
//int main(int argc, char *argv[]) {
//    // Parsing command line flags
//    gflags::ParseCommandLineFlags(&argc, &argv, true);
//
//    // Running tutorialApiCpp
//    return tutorialApiCpp();
//}



//
//// avvio con OpenPose da linea di comando
//#include <librealsense2/rs.hpp>
//#include <iostream>
//#include "example.hpp"
//#include <opencv2/opencv.hpp>
//#include <json/json.h>
//#include <json/value.h>
//#include <fstream>
//#include <string>
//
//// Convert rs2::frame to cv::Mat
//cv::Mat realsenseFrameToMat(const rs2::frame & singleFrame) {
//    rs2::video_frame videoFrame = singleFrame.as<rs2::video_frame>();
//    const int frameWidth = videoFrame.get_width(), frameHeight = videoFrame.get_height();
//
//    switch (singleFrame.get_profile().format()) {
//        case RS2_FORMAT_BGR8:
//            return cv::Mat(cv::Size(frameWidth, frameHeight), CV_8UC3, (void *) singleFrame.get_data(), cv::Mat::AUTO_STEP);
//        case RS2_FORMAT_RGB8: {
//            cv::Mat rgbFrame = cv::Mat(cv::Size(frameWidth, frameHeight), CV_8UC3, (void*) singleFrame.get_data(), cv::Mat::AUTO_STEP);
//            cv::cvtColor(rgbFrame, rgbFrame, cv::COLOR_RGB2BGR);
//            return rgbFrame;
//        }
//        case RS2_FORMAT_Z16:
//            return cv::Mat(cv::Size(frameWidth, frameHeight), CV_16UC1, (void *) singleFrame.get_data(), cv::Mat::AUTO_STEP);
//        case RS2_FORMAT_Y8:
//            return cv::Mat(cv::Size(frameWidth, frameHeight), CV_8UC1, (void *) singleFrame.get_data(), cv::Mat::AUTO_STEP);
//        default:
//            throw std::runtime_error("Frame format is not supported yet!");
//            break;
//    }
//}
//
//int main (int argc, char * argv[]) try {
//    rs2::log_to_console(RS2_LOG_SEVERITY_ERROR);
//    rs2::colorizer colorMap;
//    rs2::rates_printer printer;
//    rs2::config myConfiguration;
//    rs2::pipeline pipelineStream;
//    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_DEPTH, 640, 360, rs2_format::RS2_FORMAT_Z16);
//    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_COLOR, 640, 360, rs2_format::RS2_FORMAT_RGB8);
//
//    rs2::pipeline_profile myPipelineProfile = pipelineStream.start(myConfiguration);
//    rs2::align alignment(RS2_STREAM_COLOR);
//    rs2::depth_sensor sensor = myPipelineProfile.get_device().first<rs2::depth_sensor>();
//    float scale = sensor.get_depth_scale();
//
//     // Capture 30 frames to give autoexposure, etc. a chance to settle
//    for (int i = 0; i < 30; i++) pipelineStream.wait_for_frames();
//
//     while (true) {
//        rs2::frameset streamData = pipelineStream.wait_for_frames(), alignedStreamData = alignment.process(streamData);
//        rs2::frame colorizedDepth = alignedStreamData.get_depth_frame().apply_filter(colorMap);
//        rs2::frame depth = alignedStreamData.get_depth_frame();
//        rs2::frame color = alignedStreamData.get_color_frame();
//
//        cv::Mat colorImage = realsenseFrameToMat(color);
//        cv::Mat depthImage = realsenseFrameToMat(depth);
//        cv::Mat colorizedDepthImage = realsenseFrameToMat(colorizedDepth);
//        depthImage *= 1000.0 * scale;
//
//        imshow("Depth Video", depthImage);
//        imshow("Depth Video Colorized", colorizedDepthImage);
//        imshow("Color Video Colorized", colorImage);
//        std::system("cd ../../../ && cd materiale_tesi/openpose/ && cd ../../ && pwd && cd materiale_tesi/openpose/ && pwd && ./build/examples/openpose/openpose.bin --image_dir ../../librealsensetest/librealsensetest/build3/rs_images/ --write_json ../../librealsensetest/librealsensetest/build3/op_output/ --num_gpu 1 --num_gpu_start 2");
//
//        int key = cv::waitKey(0);
//         // if ESC is pressed
//        if (key == 27) break;
//
//    }
//    return EXIT_SUCCESS;
//} catch (const rs2::error & e){
//    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n   " << e.what() << std::endl;
//    return EXIT_FAILURE;
//} catch (const std::exception & e) {
//    std::cerr << e.what() << std::endl;
//    return EXIT_FAILURE;
//}


//
//// Disegno Body Keypoints con OpenCV a partire da un JSON file
//#include "Skeleton.hpp"
//
//const int expected_argc = 3;
//const char * expectedUsageMessage = "Usage: sudo ./hello_librealsense2.bin <path/image.jpeg> <path/file.json>";
//
//int main (int argc, char * argv[]) {
//    cv::Mat inputImage;
//    Json::Value currentJSON;
//
//    checkUsage (argc, (const char **) argv, expected_argc, expectedUsageMessage);
//    loadImage(std::string(argv[1]), cv::IMREAD_COLOR, inputImage);
//    loadJSON(argv[2], currentJSON);
//
//    std::vector<SingleBodyKeypoint> bodyKeyPoints;
//    std::vector<bool> bodyKeyPointsMap;
//    cv::imshow("no circle", inputImage);
//
//    Json::Value people = currentJSON["people"];
//    for (Json::Value::ArrayIndex i = 0; i != people.size(); i++) {
//        Json::Value singlePerson = (people[i])["pose_keypoints_2d"];
//        Skeleton singlePersonSkeleton = Skeleton(inputImage, bodyKeyPoints, bodyKeyPointsMap, singlePerson);
//        singlePersonSkeleton.drawSkeleton();
//    }
//
//    cv::imshow("circle w/lines", inputImage);
//    cv::waitKey(0);
//    return EXIT_SUCCESS;
//}




//// Disegno Body Keypoints and Edges con OpenCV a partire da un JSON file prodotto da OpenPose
//#include "Skeleton.hpp"
//#include <sstream>
//
//const int expected_argc = 7;
//const char * expectedUsageMessage = "Usage: sudo ./hello_librealsense2.bin <path/image.jpeg> <path/openpose folder> <./path/openpose.bin> <path/images folder> <path/JSON output folder>  <path/output file.json>";
//
//int main (int argc, char * argv[]) {
//    cv::Mat inputImage;
//    Json::Value currentJSON;
//
//    checkUsage (argc, (const char **) argv, expected_argc, expectedUsageMessage);
//    loadImage(std::string(argv[1]), cv::IMREAD_COLOR, inputImage);
//    std::stringstream terminalCommand;
//    terminalCommand << "cd " << argv[2] << " && " << argv[3] << " --num_gpu 1 --num_gpu_start 2 --display 0 --render_pose 0 --image_dir " << argv[4] << " --write_json " << argv[5];
//
//    std::system(terminalCommand.str().c_str());
//    std::vector<SingleBodyKeypoint> bodyKeyPoints;
//    std::vector<bool> bodyKeyPointsMap;
//    cv::imshow("no circle", inputImage);
//
//    loadJSON(argv[6], currentJSON);
//    Json::Value people = currentJSON["people"];
//    for (Json::Value::ArrayIndex i = 0; i != people.size(); i++) {
//        Json::Value singlePerson = (people[i])["pose_keypoints_2d"];
//        Skeleton singlePersonSkeleton = Skeleton(inputImage, bodyKeyPoints, bodyKeyPointsMap, singlePerson);
//        singlePersonSkeleton.drawSkeleton();
//    }
//
//    cv::imshow("circle w/lines", inputImage);
//    cv::waitKey(0);
//    return EXIT_SUCCESS;
//}




// Disegno Body Keypoints and Edges con OpenCV a partire da un JSON file prodotto da OpenPose
#include "Skeleton.hpp"
#include <librealsense2/rs.hpp>
#include "example.hpp"


const int expected_argc = 5;
const char * expectedUsageMessage = "Usage: sudo ./hello_librealsense2.bin <path/openpose folder/> <./path/openpose.bin> <path/images folder/> <path/JSON output folder/>";

// Convert rs2::frame to cv::Mat
cv::Mat realsenseFrameToMat(const rs2::frame & singleFrame) {
    rs2::video_frame videoFrame = singleFrame.as<rs2::video_frame>();
    const int frameWidth = videoFrame.get_width(), frameHeight = videoFrame.get_height();

    switch (singleFrame.get_profile().format()) {
        case RS2_FORMAT_BGR8:
            return cv::Mat(cv::Size(frameWidth, frameHeight), CV_8UC3, (void *) singleFrame.get_data(), cv::Mat::AUTO_STEP);
        case RS2_FORMAT_RGB8: {
            cv::Mat rgbFrame = cv::Mat(cv::Size(frameWidth, frameHeight), CV_8UC3, (void*) singleFrame.get_data(), cv::Mat::AUTO_STEP);
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

int main (int argc, char * argv[]) try {
    Json::Value currentJSON;
    rs2::log_to_console(RS2_LOG_SEVERITY_ERROR);
    rs2::colorizer colorMap;
    rs2::rates_printer printer;
    rs2::config myConfiguration;
    rs2::pipeline pipelineStream;
    long unsigned int frameID = 0;
//    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_DEPTH, 640, 360, rs2_format::RS2_FORMAT_Z16);
//    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_COLOR, 640, 360, rs2_format::RS2_FORMAT_RGB8);

    rs2::pipeline_profile myPipelineProfile = pipelineStream.start();
//    rs2::pipeline_profile myPipelineProfile = pipelineStream.start(myConfiguration);
//    rs2::align align_to(RS2_STREAM_DEPTH);
//    rs2::align align = rs2::align(align_to);
    rs2::depth_sensor sensor = myPipelineProfile.get_device().first<rs2::depth_sensor>();
    float scale = sensor.get_depth_scale();

     // Capture 30 frames to give autoexposure, etc. a chance to settle
    for (int i = 0; i < 30; i++) pipelineStream.wait_for_frames();
    checkUsage (argc, (const char **) argv, expected_argc, expectedUsageMessage);
    
    std::stringstream cleanTerminalCommand;
    cleanTerminalCommand << "rm -r " << argv[3] << "rgb/ > /dev/null && rm -r " << argv[3] << "d/ > /dev/null && rm -r " << argv[3] << "skeleton/ > /dev/null && rm -r " << argv[3] << "videoframe/ > /dev/null && rm -r " << argv[4] << " > /dev/null && mkdir " << argv[3] << "rgb && mkdir " << argv[3] << "d && mkdir " << argv[3] << "videoframe && mkdir " << argv[3] << "skeleton && mkdir " << argv[4];
    system(cleanTerminalCommand.str().c_str());
    
    while (true) {
        for (int nFrame = 0; nFrame < 120; nFrame++) {
            rs2::frameset streamData = pipelineStream.wait_for_frames()/*, alignedStreamData = align.process(streamData)*/;
//            rs2::depth_frame depth = alignedStreamData.get_depth_frame();
//            rs2::frame color = alignedStreamData.get_color_frame();
            rs2::depth_frame depth = streamData.get_depth_frame();
            rs2::frame color = streamData.get_color_frame();
            cv::Mat colorImage = realsenseFrameToMat(color);
            cv::Mat depthImage = realsenseFrameToMat(depth);
            depthImage *= 1000.0 * scale;

            auto cols = depth.get_width();
            auto rows = depth.get_height();
//            std::cout << "\nCOLOR ROWS: " << colorImage.rows << " COLOR COLS: " << colorImage.cols << "\nD ROWS: " << rows << " D COLS: " << cols << "\n";
            cv::Mat distanceImage = cv::Mat::zeros(rows, cols, CV_32FC1);
            for (int i = 0; i < cols; i++) for (int j = 0; j < rows; j++) {
                distanceImage.at<float>(i, j) = (float) depth.get_distance(i, j);
                if (distanceImage.at<float>(i, j) < 0.001) distanceImage.at<float>(i, j) = 0;
            }

//            std::cout << depth.get_distance(cols / 2, rows / 2) << " at " << cols/2 << ", " << rows / 2;
            std::stringstream colorImagePath, distanceImagePath;
            std::stringstream colorImageName, distanceImageName;
//            std::cout << distanceImage;
//            break;
            colorImageName << frameID << "_Color";
            distanceImageName << frameID << "_Distance";
            colorImagePath << argv[3] << "rgb/" << colorImageName.str() << ".png";
            distanceImagePath << argv[3] << "d/" << distanceImageName.str() << ".png";
            cv::imwrite(std::string(colorImagePath.str()), colorImage);
            cv::imwrite(std::string(distanceImagePath.str()), distanceImage);
            colorImage.release();
            depthImage.release();
            frameID += 1;
        }
        
        std::stringstream firstTerminalCommand, secondTerminalCommand;
        firstTerminalCommand << "cd " << argv[1] << " && " << argv[2] << " --num_gpu 1 --num_gpu_start 2 --display 0 --render_pose 0 --image_dir " << argv[3] << "rgb/" << " --write_json " << argv[4] << " --logging_level 255 > /dev/null";
    
        std::system(firstTerminalCommand.str().c_str());

//        frameID = 120;
        for (int nFrame = 0; nFrame < 120; nFrame++) {
            std::vector<SingleBodyKeypoint> bodyKeyPoints;
            std::vector<bool> bodyKeyPointsMap;
            std::stringstream jsonFilePath, skeletonImagePath, colorImagePath, distanceImagePath;
            jsonFilePath << argv[4] << (frameID - 120 + nFrame) << "_Color_keypoints.json";

            loadJSON(jsonFilePath.str().c_str(), currentJSON);
            Json::Value people = currentJSON["people"];
            colorImagePath << argv[3] << "rgb/" << (frameID - 120 + nFrame) << "_Color.png";
            distanceImagePath << argv[3] << "d/" << (frameID - 120 + nFrame) << "_Distance.png";
            cv::Mat colorImage = cv::imread(colorImagePath.str()), distanceImage = cv::imread(distanceImagePath.str());
            cv::imshow("Frame No Skeleton", colorImage);
            for (Json::Value::ArrayIndex i = 0; i != people.size(); i++) {
                Json::Value singlePerson = (people[i])["pose_keypoints_2d"];
                Skeleton singlePersonSkeleton = Skeleton(colorImage, distanceImage, bodyKeyPoints, bodyKeyPointsMap, singlePerson);
                singlePersonSkeleton.drawSkeleton();
            }

            
            cv::imshow("Frame Skeleton", colorImage);
            skeletonImagePath << argv[3] << "skeleton/" << (frameID - 120 + nFrame) << "_Skeleton.png";
            cv::imwrite(skeletonImagePath.str().c_str(), colorImage);
            int key = cv::waitKey(0);
             // if ESC is pressed
            if (key == 27) break;
        }
        
        secondTerminalCommand << "mv -v " << argv[3] << "rgb/* " << argv[3] << "videoframe/ > /dev/null";
        std::system(secondTerminalCommand.str().c_str());
    }
    return EXIT_SUCCESS;
} catch (const rs2::error & e){
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n   " << e.what() << std::endl;
    return EXIT_FAILURE;
} catch (const std::exception & e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}
