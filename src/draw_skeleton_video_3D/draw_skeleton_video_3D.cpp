//
//  draw_skeleton_video_3D.cpp
//  Disegno Body Keypoints and Edges con OpenCV a partire da più file JSON file prodotti da OpenPose.
//  Proiezione delle coordinate spaziali tridimensionali.
//
//  Created by Denny Caruso on 20/07/22.
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
    struct rs2_intrinsics color_intrin;
    UsageUtility myUsageUtility = UsageUtility(argc, argv, expected_argc, expectedUsageMessage);
    myUsageUtility.startEnvironment(pipelineStream, color_intrin, & scale, resX, resY);
    

    while (true) {
//        myUsageUtility.getVideoFrames(user_nFrame, pipelineStream, scale);
//        myUsageUtility.getVideoBodyKeyPoints();
        myUsageUtility.showSkeleton(user_nFrame, currentJSON, color_intrin);
    }
    return EXIT_SUCCESS;
}

//
//
//// Mappare un pixel colore in un'immagine RGB in un pixel profondità in un'immagine profondità
//int main (int argc, const char * argv[]) {
//    rs2::log_to_console(RS2_LOG_SEVERITY_ERROR);
//    rs2::pipeline pipelineStream;
//    rs2::colorizer colorMap;
//    rs2::rates_printer printer;
//    rs2::config myConfiguration;
//    int resX = 640, resY = 360;
//    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_DEPTH, resX, resY, rs2_format::RS2_FORMAT_Z16);
//    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_COLOR, resX, resY, rs2_format::RS2_FORMAT_RGB8);
//    rs2::pipeline_profile myPipelineProfile = pipelineStream.start(myConfiguration);
//    rs2::align align_to(RS2_STREAM_COLOR);
//    rs2::align align = rs2::align(align_to);
//    rs2::depth_sensor sensor = myPipelineProfile.get_device().first<rs2::depth_sensor>();
//    float scale = sensor.get_depth_scale();
//
//    // Capture 30 frames to give autoexposure, etc. a chance to settle
//    for (int i = 0; i < 30; i++) pipelineStream.wait_for_frames();
////    void rs2_project_color_pixel_to_depth_pixel    (    float     to_pixel[2],
////    const uint16_t *     data,
////    float     depth_scale,
////    float     depth_min,
////    float     depth_max,
////    const struct rs2_intrinsics *     depth_intrin,
////    const struct rs2_intrinsics *     color_intrin,
////    const struct rs2_extrinsics *     color_to_depth,
////    const struct rs2_extrinsics *     depth_to_color,
////    const float     from_pixel[2]
////    )
//
////    void rs2_deproject_pixel_to_point (float point[3], const rs2_intrinsics *intrin, const float pixel[2], float depth)
//
//
//    rs2::frameset streamData = pipelineStream.wait_for_frames(), alignedStreamData = align.process(streamData);
//    rs2::depth_frame depth = alignedStreamData.get_depth_frame();
//    rs2::frame color = alignedStreamData.get_color_frame();
//    rs2::frame colorizedDepth = alignedStreamData.get_depth_frame().apply_filter(colorMap);
////    rs2::depth_frame depth = streamData.get_depth_frame();
////    rs2::frame color = streamData.get_color_frame();
////    rs2::frame colorizedDepth = streamData.get_depth_frame().apply_filter(colorMap);
//    UsageUtility myUsageUtility = UsageUtility();
//    cv::Mat colorImage = myUsageUtility.realsenseFrameToMat(color);
//    cv::Mat depthImage = myUsageUtility.realsenseFrameToMat(depth);
//    cv::Mat colorizedDepthImage = myUsageUtility.realsenseFrameToMat(colorizedDepth);
//    depthImage *= 1000.0 * scale;
//
//    float depth_min = 0.11, depth_max = 5.0;
//    struct rs2_intrinsics depth_intrin = myPipelineProfile.get_stream(RS2_STREAM_DEPTH).as<rs2::video_stream_profile>().get_intrinsics();
//    struct rs2_intrinsics color_intrin = myPipelineProfile.get_stream(RS2_STREAM_COLOR).as<rs2::video_stream_profile>().get_intrinsics();
//
//    struct rs2_extrinsics color_to_depth = myPipelineProfile.get_stream(RS2_STREAM_DEPTH).as<rs2::video_stream_profile>().get_extrinsics_to(myPipelineProfile.get_stream(RS2_STREAM_COLOR));
//    struct rs2_extrinsics depth_to_color = myPipelineProfile.get_stream(RS2_STREAM_COLOR).as<rs2::video_stream_profile>().get_extrinsics_to(myPipelineProfile.get_stream(RS2_STREAM_DEPTH));
//
//    float to_pixel[2][2] = { { 0, 0 }, { 0, 0 } };
//    float from_pixel[2][2] = { { 100, 350 }, { 200.0, 200.0 } };
//
//    rs2_project_color_pixel_to_depth_pixel(& to_pixel[0][0], (unsigned short int *) depth.get_data(), scale, depth_min, depth_max, & depth_intrin, & color_intrin, & color_to_depth, & depth_to_color, & from_pixel[0][0]);
//
//    std::cout << "FROM\n" << from_pixel[0][0] << " " << from_pixel[0][1] << " TO " << to_pixel[0][0] << " " << to_pixel[0][1] << "\nFROM\n" << from_pixel[1][0] << " " << from_pixel[1][1] << " TO " << to_pixel[1][0] << " " << to_pixel[1][1] << "\n";
//
//    float distance1 = depth.get_distance(from_pixel[0][0], from_pixel[0][1]);
//    float distance2 = depth.get_distance(from_pixel[0][0], from_pixel[0][1]);
//    std:: cout << "\nDIST1 : " << distance1 << " DIST2: " << distance2;
//
//    float point[3] = { 0, 0, 0 };
//    rs2_deproject_pixel_to_point(point, & color_intrin, & from_pixel[0][0], distance2);
//    std::cout << "\nPOINT: " << point[0] << " " << point[1] << "  " << point[2] << "\n";
//    cv::circle(colorImage, cv::Point(from_pixel[0][0], from_pixel[0][1]), 5, cv::Scalar(0, 0, 255));
//    cv::circle(colorizedDepthImage, cv::Point(from_pixel[0][0], from_pixel[0][1]), 5, cv::Scalar(255, 255, 255));
//    cv::imshow("RGB", colorImage);
//    cv::imshow("D", colorizedDepthImage);
//    cv::waitKey(0);
//
//
//
////
////
////depth_min = 0.11 #meter
////depth_max = 1.0 #meter
////
////depth_intrin = profile.get_stream(rs.stream.depth).as_video_stream_profile().get_intrinsics()
////color_intrin = profile.get_stream(rs.stream.color).as_video_stream_profile().get_intrinsics()
////
////depth_to_color_extrin =  profile.get_stream(rs.stream.depth).as_video_stream_profile().get_extrinsics_to( profile.get_stream(rs.stream.color))
////color_to_depth_extrin =  profile.get_stream(rs.stream.color).as_video_stream_profile().get_extrinsics_to( profile.get_stream(rs.stream.depth))
////
////color_points = [
////    [400.0, 150.0],
////    [560.0, 150.0],
////    [560.0, 260.0],
////    [400.0, 260.0]
////]
////for color_point in color_points:
////   depth_point_ = rs.rs2_project_color_pixel_to_depth_pixel(
////                depth_frame.get_data(), depth_scale,
////                depth_min, depth_max,
////                depth_intrin, color_intrin, depth_to_color_extrin, color_to_depth_extrin, color_point)
//    return EXIT_SUCCESS;
//}
