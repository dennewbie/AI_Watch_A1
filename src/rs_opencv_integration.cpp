//
//  rs_opencv_integration.cpp
//  Integrazione OpenCV con RealSense SDK
//
//  Created by Denny Caruso on 09/07/22.
//

#include <librealsense2/rs.hpp>
#include <iostream>
#include "example.hpp"
#include <opencv2/opencv.hpp>

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
    rs2::log_to_console(RS2_LOG_SEVERITY_ERROR);
    rs2::colorizer colorMap;
    rs2::rates_printer printer;
    rs2::config myConfiguration;
    rs2::pipeline pipelineStream;
    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_DEPTH, 640, 360, rs2_format::RS2_FORMAT_Z16);
    myConfiguration.enable_stream(rs2_stream::RS2_STREAM_COLOR, 640, 360, rs2_format::RS2_FORMAT_RGB8);

    rs2::pipeline_profile myPipelineProfile = pipelineStream.start(myConfiguration);
    rs2::align alignment(RS2_STREAM_COLOR);
    rs2::depth_sensor sensor = myPipelineProfile.get_device().first<rs2::depth_sensor>();
    float scale = sensor.get_depth_scale();

    while (true) {
        rs2::frameset streamData = pipelineStream.wait_for_frames(), alignedStreamData = alignment.process(streamData);
        rs2::frame colorizedDepth = alignedStreamData.get_depth_frame().apply_filter(colorMap);
        rs2::frame depth = alignedStreamData.get_depth_frame();
        rs2::frame color = alignedStreamData.get_color_frame();

        cv::Mat colorImage = realsenseFrameToMat(color);
        cv::Mat depthImage = realsenseFrameToMat(depth);
        cv::Mat colorizedDepthImage = realsenseFrameToMat(colorizedDepth);
        depthImage *= 1000.0 * scale;

        imshow("Depth Video", depthImage);
        imshow("Depth Video Colorized", colorizedDepthImage);
        imshow("Color Video Colorized", colorImage);
        int key = cv::waitKey(1);
        // if ESC is pressed
        if (key == 27) break;
    }
    return EXIT_SUCCESS;
} catch (const rs2::error & e){
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n   " << e.what() << std::endl;
    return EXIT_FAILURE;
} catch (const std::exception & e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}