//
//  main.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 06/07/22.
//

// Command-line user interface
//#define OPENPOSE_FLAGS_DISABLE_PRODUCER
//#define OPENPOSE_FLAGS_DISABLE_DISPLAY
//#include <openpose/flags.hpp>
//#include <openpose/headers.hpp>

// Custom OpenPose flags
// Producer
//DEFINE_string(image_dir, "/", "Process a directory of images. Read all standard formats (jpg, png, bmp, etc.).");
// Display
//DEFINE_bool(no_display, false, "Enable to disable the visual display.");



#include "FacadeSingleton.hpp"
//#include <openpose/flags.hpp>
//#include <openpose/headers.hpp>
//#include <opencv2/opencv.hpp>



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
    Json::Value currentJSON;
    // Scaling factor for distance frame and topic name for kafka connection.
    float scale;
    const char * destinationKafkaTopic = "t1";
    // Optimal resolution for D435: 848x480.
    unsigned  int user_nFrame = 30, resX = 848, resY = 480;
    struct rs2_intrinsics color_intrin;
    
    // Parsing command line flags
//    gflags::ParseCommandLineFlags(& argc, & argv, true);
    
    // Declaring a pointer to a FacadeSingleton object (it will be helpful to easily interact with all submodules) and starting D435 camera.
    FacadeSingleton * myUtility = FacadeSingleton::getInstance(& argc, & argv, expected_argc, expectedUsageMessage);
    myUtility->startEnvironment(pipelineStream, color_intrin, & scale, resX, resY, destinationKafkaTopic);

    /*
        An infinite loop that captures the frames seen from the camera, gives them to OpenPose, gets the output, and builds skeletons.
        After that, we create a properly formatted output JSON file and send it via Kafka for further elaboration.
    */
    while (true) {
        myUtility->getVideoFrames(user_nFrame, pipelineStream, scale);
        myUtility->getVideoBodyKeyPoints(& argc, & argv);
        myUtility->showSkeletons(user_nFrame, currentJSON);
//        myUtility->sendData(user_nFrame);
        break;
    }
    return EXIT_SUCCESS;
}
//
//
//void configureWrapper(op::Wrapper & opWrapper) {
//    try {
//        // logging_level
//        op::checkBool(
//            0 <= FLAGS_logging_level && FLAGS_logging_level <= 255, "Wrong logging_level value.",
//            __LINE__, __FUNCTION__, __FILE__);
//        op::ConfigureLog::setPriorityThreshold((op::Priority)FLAGS_logging_level);
//        op::Profiler::setDefaultX(FLAGS_profile_speed);
//
//        // Applying user defined configuration - GFlags to program variables
//        // outputSize
//        const auto outputSize = op::flagsToPoint(op::String(FLAGS_output_resolution), "-1x-1");
//        // netInputSize
//        const auto netInputSize = op::flagsToPoint(op::String(FLAGS_net_resolution), "-1x368");
//        // faceNetInputSize
//        const auto faceNetInputSize = op::flagsToPoint(op::String(FLAGS_face_net_resolution), "368x368 (multiples of 16)");
//        // handNetInputSize
//        const auto handNetInputSize = op::flagsToPoint(op::String(FLAGS_hand_net_resolution), "368x368 (multiples of 16)");
//        // poseMode
//        const auto poseMode = op::flagsToPoseMode(FLAGS_body);
//        // poseModel
//        const auto poseModel = op::flagsToPoseModel(op::String(FLAGS_model_pose));
//        // JSON saving
//        if (!FLAGS_write_keypoint.empty()) {
//            op::opLog("Flag `write_keypoint` is deprecated and will eventually be removed. Please, use `write_json`"
//                " instead.", op::Priority::Max);
//        }
//        // keypointScaleMode
//        const auto keypointScaleMode = op::flagsToScaleMode(FLAGS_keypoint_scale);
//        // heatmaps to add
//        const auto heatMapTypes = op::flagsToHeatMaps(FLAGS_heatmaps_add_parts, FLAGS_heatmaps_add_bkg,
//                                                      FLAGS_heatmaps_add_PAFs);
//        const auto heatMapScaleMode = op::flagsToHeatMapScaleMode(FLAGS_heatmaps_scale);
//        // >1 camera view?
//        const auto multipleView = (FLAGS_3d || FLAGS_3d_views > 1);
//        // Face and hand detectors
//        const auto faceDetector = op::flagsToDetector(FLAGS_face_detector);
//        const auto handDetector = op::flagsToDetector(FLAGS_hand_detector);
//        // Enabling Google Logging
//        const bool enableGoogleLogging = true;
//
//        // Pose configuration (use WrapperStructPose{} for default and recommended configuration)
//        const op::WrapperStructPose wrapperStructPose{
//            poseMode, netInputSize, FLAGS_net_resolution_dynamic, outputSize, keypointScaleMode, FLAGS_num_gpu,
//            FLAGS_num_gpu_start, FLAGS_scale_number, (float)FLAGS_scale_gap,
//            op::flagsToRenderMode(FLAGS_render_pose, multipleView), poseModel, !FLAGS_disable_blending,
//            (float)FLAGS_alpha_pose, (float)FLAGS_alpha_heatmap, FLAGS_part_to_show, op::String(FLAGS_model_folder),
//            heatMapTypes, heatMapScaleMode, FLAGS_part_candidates, (float)FLAGS_render_threshold,
//            FLAGS_number_people_max, FLAGS_maximize_positives, FLAGS_fps_max, op::String(FLAGS_prototxt_path),
//            op::String(FLAGS_caffemodel_path), (float)FLAGS_upsampling_ratio, enableGoogleLogging};
//        opWrapper.configure(wrapperStructPose);
//        // Face configuration (use op::WrapperStructFace{} to disable it)
//        const op::WrapperStructFace wrapperStructFace{
//            FLAGS_face, faceDetector, faceNetInputSize,
//            op::flagsToRenderMode(FLAGS_face_render, multipleView, FLAGS_render_pose),
//            (float)FLAGS_face_alpha_pose, (float)FLAGS_face_alpha_heatmap, (float)FLAGS_face_render_threshold};
//        opWrapper.configure(wrapperStructFace);
//        // Hand configuration (use op::WrapperStructHand{} to disable it)
//        const op::WrapperStructHand wrapperStructHand{
//            FLAGS_hand, handDetector, handNetInputSize, FLAGS_hand_scale_number, (float)FLAGS_hand_scale_range,
//            op::flagsToRenderMode(FLAGS_hand_render, multipleView, FLAGS_render_pose), (float)FLAGS_hand_alpha_pose,
//            (float)FLAGS_hand_alpha_heatmap, (float)FLAGS_hand_render_threshold};
//        opWrapper.configure(wrapperStructHand);
//        // Extra functionality configuration (use op::WrapperStructExtra{} to disable it)
//        const op::WrapperStructExtra wrapperStructExtra{
//            FLAGS_3d, FLAGS_3d_min_views, FLAGS_identification, FLAGS_tracking, FLAGS_ik_threads};
//        opWrapper.configure(wrapperStructExtra);
//        // Output (comment or use default argument to disable any output)
//        const op::WrapperStructOutput wrapperStructOutput{
//            FLAGS_cli_verbose, op::String(FLAGS_write_keypoint), op::stringToDataFormat(FLAGS_write_keypoint_format),
//            op::String(FLAGS_write_json), op::String(FLAGS_write_coco_json), FLAGS_write_coco_json_variants,
//            FLAGS_write_coco_json_variant, op::String(FLAGS_write_images), op::String(FLAGS_write_images_format),
//            op::String(FLAGS_write_video), FLAGS_write_video_fps, FLAGS_write_video_with_audio,
//            op::String(FLAGS_write_heatmaps), op::String(FLAGS_write_heatmaps_format), op::String(FLAGS_write_video_3d),
//            op::String(FLAGS_write_video_adam), op::String(FLAGS_write_bvh), op::String(FLAGS_udp_host),
//            op::String(FLAGS_udp_port)};
//        opWrapper.configure(wrapperStructOutput);
//        // No GUI. Equivalent to: opWrapper.configure(op::WrapperStructGui{});
//        // Set to single-thread (for sequential processing and/or debugging and/or reducing latency)
//        if (FLAGS_disable_multi_thread)
//            opWrapper.disableMultiThreading();
//    } catch (const std::exception & e) {
//        op::error(e.what(), __LINE__, __FUNCTION__, __FILE__);
//    }
//}
//
//
//int tutorialApiCpp() {
//    try {
//        op::Wrapper opWrapper{ op::ThreadManagerMode::Asynchronous };
//        configureWrapper(opWrapper);
//        opWrapper.start();
//        // Read frames on directory
//        const auto imagePaths = op::getFilesOnDirectory(FLAGS_image_dir, op::Extensions::Images);
//
//        // Process and display images
//        for (const auto & imagePath : imagePaths) {
//            const cv::Mat cvImageToProcess = cv::imread(imagePath);
//            const op::Matrix imageToProcess = OP_CV2OPCONSTMAT(cvImageToProcess);
//            auto datumProcessed = opWrapper.emplaceAndPop(imageToProcess);
//        }
//        return 0;
//    } catch (const std::exception &) {
//        return -1;
//    }
//}
//
//int main(int argc, char ** argv) {
//    // Parsing command line flags
//    gflags::ParseCommandLineFlags(& argc, & argv, true);
//
//    // Running tutorialApiCpp
//    return tutorialApiCpp();
//}
