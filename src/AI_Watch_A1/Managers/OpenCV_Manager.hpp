//
//  OpenCV_Manager.hpp
//  AI Watch A1
//
//  Created by Denny Caruso on 23/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#ifndef OpenCV_Manager_hpp
#define OpenCV_Manager_hpp

#include "../Skeleton.hpp"



/**
 * OpenCV_Manager class is a class that is responsible for converting a rs2::frame to a cv::Mat, retrieving video frames 
 * from the camera and handling them, showing the skeletons, producing related output, and saving results.
 * @brief OpenCV_Manager class is used for general-purpose tasks on the captured frames.
 */
class OpenCV_Manager {
public:
    /**
     * @brief Destroy the OpenCV_Manager object.
     */
    virtual ~OpenCV_Manager() = default;
    


    /**
     * @brief This method converts a frame of type rs2::frame to cv::Mat.
     * @param singleFrame A frame of type rs2::frame.
     * @return cv::Mat 
     */
    cv::Mat realsenseFrameToMat     (const rs2::frame & singleFrame);
    /**
     * @brief Get user_nFrame video frames from the pipeline by applying a specific scaling factor.
     * @param user_nFrame frame's number to capture according to user choice.
     * @param pipelineStream The pipeline simplifies the user interaction with the device and computer vision processing modules. 
     * The class abstracts the camera configuration and streaming, and the vision modules triggering and threading. 
     * It lets the application focus on the computer vision output of the modules, or the device output data. 
     * The pipeline can manage computer vision modules, which are implemented as a processing block. 
     * The pipeline is the consumer of the processing block interface, while the application consumes the computer vision interface.
     * @param scale Scaling factor.
     * @see https://dev.intelrealsense.com/docs/docs-get-started
     * @see getVideoFrames(unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale)
     * @see getVideoFramesRS(unsigned int user_nFrame, rs2::pipeline & pipelineStream, rs2::depth_frame & depthFrame, rs2::frame & colorFrame, rs2::frame & colorizedDepthFrame)
     */
    void getVideoFramesCV           (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale);
    /**
     * @brief Retrieve OpenPose's output, convert it to RealSense coordinate's space, show results and save them.
     * @param user_nFrame frame's number to capture according to user choice.
     * @see showSkeletons(unsigned int user_nFrame)
     */
    void showSkeletonsCV            (unsigned int user_nFrame);
};

#endif /* OpenCV_Manager_hpp */
