//
//  draw_skeleton_video.cpp
//  Disegno Body Keypoints and Edges con OpenCV a partire da più file JSON file prodotti da OpenPose 
//
//  Created by Denny Caruso on 06/07/22.
//

#include "Skeleton.hpp"
#include <librealsense2/rs.hpp>


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