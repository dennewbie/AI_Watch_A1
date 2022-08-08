//
//  RealSenseManager.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "RealSenseManager.hpp"



void RealSenseD435Manager::startEnvironment (rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale, unsigned short int resX, unsigned short int resY, bool firstBoot) try {
    rs2::log_to_console(RS2_LOG_SEVERITY_ERROR);
    rs2::rates_printer printer;
    rs2::config myConfiguration;
    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_DEPTH, resX, resY, rs2_format::RS2_FORMAT_Z16);
    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_COLOR, resX, resY, rs2_format::RS2_FORMAT_RGB8);
    rs2::pipeline_profile myPipelineProfile = pipelineStream.start(myConfiguration);
    rs2::align align_to(RS2_STREAM_COLOR);
    RealSenseManager::set_align(rs2::align(align_to));
    rs2::depth_sensor sensor = myPipelineProfile.get_device().first<rs2::depth_sensor>();
    * scale = sensor.get_depth_scale();
    
    // Capture 30 frames to give autoexposure, etc. a chance to settle
    if (firstBoot) for (int i = 0; i < 30; i++) pipelineStream.wait_for_frames();
    
    RealSenseManager::set_depth_intrin(myPipelineProfile.get_stream(RS2_STREAM_DEPTH).as<rs2::video_stream_profile>().get_intrinsics());
    color_intrin = myPipelineProfile.get_stream(RS2_STREAM_COLOR).as<rs2::video_stream_profile>().get_intrinsics();
    RealSenseManager::set_color_intrin(color_intrin);
    RealSenseManager::set_color_to_depth(myPipelineProfile.get_stream(RS2_STREAM_DEPTH).as<rs2::video_stream_profile>().get_extrinsics_to(myPipelineProfile.get_stream(RS2_STREAM_COLOR)));
    RealSenseManager::set_depth_to_color(myPipelineProfile.get_stream(RS2_STREAM_COLOR).as<rs2::video_stream_profile>().get_extrinsics_to(myPipelineProfile.get_stream(RS2_STREAM_DEPTH)));
} catch (const rs2::error & e){
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n   " << e.what() << std::endl;
    CV_Error(RS_CAMERA_ERROR, RS_CAMERA_SCOPE);
} catch (const std::exception & e) {
    std::cerr << e.what() << std::endl;
    CV_Error(RS_CAMERA_ERROR, RS_CAMERA_SCOPE);
}

void RealSenseD435Manager::getVideoFramesRS (unsigned int user_nFrame, rs2::pipeline & pipelineStream, rs2::depth_frame & depthFrame, rs2::frame & colorFrame, rs2::frame & colorizedDepthFrame) try {
    rs2::colorizer colorMap;
    rs2::spatial_filter spatialFilter;
    
    // Capture frames and apply post-processing
    rs2::frameset streamData = pipelineStream.wait_for_frames(), alignedStreamData = RealSenseManager::get_align().process(streamData);
    depthFrame = alignedStreamData.get_depth_frame();
    spatialFilter.set_option(RS2_OPTION_HOLES_FILL, 1);
    depthFrame = spatialFilter.process(depthFrame);
    
    colorFrame = alignedStreamData.get_color_frame();
    colorizedDepthFrame = depthFrame.apply_filter(colorMap);
    RealSenseManager::setFrameID(RealSenseD435Manager::getFrameID() + 1);
} catch (const rs2::error & e){
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n   " << e.what() << std::endl;
    CV_Error(RS_CAMERA_ERROR, RS_CAMERA_SCOPE);
} catch (const std::exception & e) {
    std::cerr << e.what() << std::endl;
    CV_Error(RS_CAMERA_ERROR, RS_CAMERA_SCOPE);
}
