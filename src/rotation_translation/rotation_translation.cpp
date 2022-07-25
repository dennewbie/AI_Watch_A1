#include <librealsense2/rs.hpp>
#include <iostream>


int main(int argc, char ** argv) {
    rs2::log_to_console(RS2_LOG_SEVERITY_ERROR);
    rs2::rates_printer printer;
    rs2::config myConfiguration;
    float scale;
    int resX = 848, resY = 480;
    rs2::pipeline pipelineStream;
    struct rs2_intrinsics color_intrin;
    struct rs2_intrinsics depth_intrin;
    struct rs2_extrinsics depth_to_color;
    struct rs2_extrinsics color_to_depth;
    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_DEPTH, resX, resY, rs2_format::RS2_FORMAT_Z16);
    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_COLOR, resX, resY, rs2_format::RS2_FORMAT_RGB8);
    rs2::pipeline_profile myPipelineProfile = pipelineStream.start(myConfiguration);
    rs2::align align_to(RS2_STREAM_COLOR);
    rs2::align align = rs2::align(align_to);
    rs2::depth_sensor sensor = myPipelineProfile.get_device().first<rs2::depth_sensor>();
    scale = sensor.get_depth_scale();
    
    //     Capture 30 frames to give autoexposure, etc. a chance to settle
        for (int i = 0; i < 30; i++) pipelineStream.wait_for_frames();
    depth_intrin = myPipelineProfile.get_stream(RS2_STREAM_DEPTH).as<rs2::video_stream_profile>().get_intrinsics();
    color_intrin = myPipelineProfile.get_stream(RS2_STREAM_COLOR).as<rs2::video_stream_profile>().get_intrinsics();
    color_to_depth = myPipelineProfile.get_stream(RS2_STREAM_DEPTH).as<rs2::video_stream_profile>().get_extrinsics_to(myPipelineProfile.get_stream(RS2_STREAM_COLOR));
    depth_to_color = myPipelineProfile.get_stream(RS2_STREAM_COLOR).as<rs2::video_stream_profile>().get_extrinsics_to(myPipelineProfile.get_stream(RS2_STREAM_DEPTH));
    
    const rs2::stream_profile myStreamProfile = pipelineStream.get_active_profile().get_stream(RS2_STREAM_COLOR).as<rs2::stream_profile>();
    const rs2_extrinsics myExtrinsics = pipelineStream.get_active_profile().get_stream(RS2_STREAM_DEPTH).as<rs2::video_stream_profile>().get_extrinsics_to(myStreamProfile);
    float rotation[9];
    for (int i = 0; i < 9; i++) {
        rotation[i] = myExtrinsics.rotation[i];
    }
    
    std::cout << " ROTATION:\n";
    for (int i = 0; i < 9; i++) {
        std::cout << rotation[i] << "\t";
    }
    
    std::cout << "\n";
    float translation[3];
    for (int i = 0; i < 3; i++) {
        translation[i] = myExtrinsics.translation[i];
    }
    
    std::cout << "TRANSLATION:\n";
    for (int i = 0; i < 3; i++) {
        std::cout << translation[i] << "\t";
    }
    std::cout << "\n\n";
    return 0;
}
