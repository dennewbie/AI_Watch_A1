//
//  RealSenseManager.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#ifndef RealSenseManager_hpp
#define RealSenseManager_hpp

#include <librealsense2/rs.hpp>
#include <iostream>
#include <opencv2/core.hpp>
#include "../../constants.hpp"



/**
 * @brief RealSenseManager class is a class that abstracts the behavior of an Intel RealSense Camera, 
 * in order to capture frames, apply post-processing, and so on.
 */
class RealSenseManager {
private:
    /**
     * @brief Current frame counter.
     */
    unsigned int                frameID;
    /**
     * @brief Auxiliary processing block that performs image alignment using depth data and camera calibration.
     * @see http://docs.ros.org/en/kinetic/api/librealsense2/html/classrs2_1_1align.html
     */
    rs2::align                  align;
    /**
     * @brief Reference to depth stream intrinsics.
     * @see https://dev.intelrealsense.com/docs/projection-in-intel-realsense-sdk-20
     */
    struct rs2_intrinsics       depth_intrin;
    /**
     * @brief Reference to color stream intrinsics.
     * @see https://dev.intelrealsense.com/docs/projection-in-intel-realsense-sdk-20
     */
    struct rs2_intrinsics       color_intrin;
    /**
     * @brief Reference to depth stream extrinsics.
     * @see https://dev.intelrealsense.com/docs/projection-in-intel-realsense-sdk-20
     */
    struct rs2_extrinsics       depth_to_color;
    /**
     * @brief Reference to color stream extrinsics.
     * @see https://dev.intelrealsense.com/docs/projection-in-intel-realsense-sdk-20
     */
    struct rs2_extrinsics       color_to_depth;
protected:
    /**
     * @brief Set the Frame ID value.
     * @param frameID Current frame counter.
     */
    void setFrameID             (unsigned int frameID);
    /**
     * @brief Set the align object.
     * @see http://docs.ros.org/en/kinetic/api/librealsense2/html/classrs2_1_1align.html
     * @param align Auxiliary processing block that performs image alignment using depth data and camera calibration.
     */
    void set_align              (rs2::align align);
    /**
     * @brief Set the depth intrinsics object.
     * @param depth_intrin Reference to depth stream intrinsics.
     */
    void set_depth_intrin       (struct rs2_intrinsics depth_intrin);
    /**
     * @brief Set the color intrinsics object.
     * @param color_intrin Reference to color stream intrinsics.
     */
    void set_color_intrin       (struct rs2_intrinsics & color_intrin);
    /**
     * @brief Set the depth extrinsics object.
     * @param depth_to_color Reference to depth stream extrinsics.
     */
    void set_depth_to_color     (struct rs2_extrinsics depth_to_color);
    /**
     * @brief Set the color extrinsics object.
     * @param color_to_depth Reference to color stream extrinsics.
     */
    void set_color_to_depth     (struct rs2_extrinsics color_to_depth);
    


    /**
     * @brief Get the align object.
     * @return rs2::align 
     * @see http://docs.ros.org/en/kinetic/api/librealsense2/html/classrs2_1_1align.html
     */
    rs2::align get_align                        (void);
    /**
     * @brief Get the depth intrinsics object.
     * @return struct rs2_intrinsics 
     */
    struct rs2_intrinsics get_depth_intrin      (void);
    /**
     * @brief Get the depth extrinsics object.
     * @return struct rs2_extrinsics 
     */
    struct rs2_extrinsics get_depth_to_color    (void);
    /**
     * @brief Get the color extrinsics object.
     * @return struct rs2_extrinsics 
     */
    struct rs2_extrinsics get_color_to_depth    (void);
public:
    /**
     * @brief Construct a new RealSenseManager object.
     */
    RealSenseManager (void);
    /**
     * @brief Destroy the RealSenseManager object.
     */
    virtual ~RealSenseManager() = default;
    /**
     * @brief Get the current frame ID value.
     * @return unsigned int 
     */
    unsigned int getFrameID                     (void);
    /**
     * @brief Get the color intrinsics object.
     * @return struct rs2_intrinsics & 
     */
    struct rs2_intrinsics & get_color_intrin    (void);
    /**
     * @brief This method is useful to invoke at the boot of the program where we want
     * to initialize the different mangers, start the camera and set up the related
     * environment. This method can be overridden and specified according to camera model.
     * @param pipelineStream The pipeline simplifies the user interaction with the device and computer vision processing modules. 
     * The class abstracts the camera configuration and streaming, and the vision modules triggering and threading. 
     * It lets the application focus on the computer vision output of the modules, or the device output data. 
     * The pipeline can manage computer vision modules, which are implemented as a processing block. 
     * The pipeline is the consumer of the processing block interface, while the application consumes the computer vision interface.
     * @param color_intrin Reference to color video stream intrinsics.
     * @param scale Pointer to scaling factor.
     * @param resX x resoultion <->
     * @param resY y resolution
     * @param firstBoot true if the method is called for the first time (in this case a kind of camera calibration is done), false otherwise.
     * @param destinationKafkaTopic the destination's kafka topic's name.
     * @see https://dev.intelrealsense.com/docs/docs-get-started
     * @see startEnvironment(rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale, unsigned short int resX, unsigned short int resY, const char * destinationKafkaTopic)
     */
    virtual void startEnvironment               (rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale,
                                                 unsigned short int resX, unsigned short int resY, bool firstBoot) = 0;
    /**
     * @brief Get user_nFrame video frames from the pipeline by applying a specific scaling factor.
     * This method can be overridden and specified according to camera model.
     * @param user_nFrame frame's number to capture according to user choice. 
     * @param pipelineStream The pipeline simplifies the user interaction with the device and computer vision processing modules. 
     * The class abstracts the camera configuration and streaming, and the vision modules triggering and threading. 
     * It lets the application focus on the computer vision output of the modules, or the device output data. 
     * The pipeline can manage computer vision modules, which are implemented as a processing block. 
     * The pipeline is the consumer of the processing block interface, while the application consumes the computer vision interface.
     * @param depthFrame Reference to depth frame object that will be captured.
     * @param colorFrame Reference to color frame object that will be captured.
     * @param colorizedDepthFrame Reference to colorized depth frame object that will be captured.
     * @see https://dev.intelrealsense.com/docs/docs-get-started
     * @see getVideoFramesCV(unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale)
     * @see getVideoFrames         (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale)
     */
    virtual void getVideoFramesRS               (unsigned int user_nFrame, rs2::pipeline & pipelineStream,
                                                 rs2::depth_frame & depthFrame, rs2::frame & colorFrame,
                                                 rs2::frame & colorizedDepthFrame) = 0;
};

class RealSenseD435Manager : public RealSenseManager {
public:
    /**
     * @brief This method is useful to invoke at the boot of the program where we want
     * to initialize the different mangers, start the camera and set up the related
     * environment. This method is specific for D435 Intel RealSense camera.
     * @param pipelineStream The pipeline simplifies the user interaction with the device and computer vision processing modules. 
     * The class abstracts the camera configuration and streaming, and the vision modules triggering and threading. 
     * It lets the application focus on the computer vision output of the modules, or the device output data. 
     * The pipeline can manage computer vision modules, which are implemented as a processing block. 
     * The pipeline is the consumer of the processing block interface, while the application consumes the computer vision interface.
     * @param color_intrin Reference to color video stream intrinsics.
     * @param scale Pointer to scaling factor.
     * @param resX x resoultion <->
     * @param resY y resolution
     * @param firstBoot true if the method is called for the first time (in this case a kind of camera calibration is done), false otherwise.
     * @param destinationKafkaTopic the destination's kafka topic's name.
     * @see https://dev.intelrealsense.com/docs/docs-get-started
     * @see startEnvironment(rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale, unsigned short int resX, unsigned short int resY, const char * destinationKafkaTopic)
     */
    void startEnvironment                       (rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale,
                                                 unsigned short int resX, unsigned short int resY, bool firstBoot) override;
    /**
     * @brief Get user_nFrame video frames from the pipeline by applying a specific scaling factor.
     * This method is specific for D435 Intel RealSense camera.
     * @param user_nFrame frame's number to capture according to user choice. 
     * @param pipelineStream The pipeline simplifies the user interaction with the device and computer vision processing modules. 
     * The class abstracts the camera configuration and streaming, and the vision modules triggering and threading. 
     * It lets the application focus on the computer vision output of the modules, or the device output data. 
     * The pipeline can manage computer vision modules, which are implemented as a processing block. 
     * The pipeline is the consumer of the processing block interface, while the application consumes the computer vision interface.
     * @param depthFrame Reference to depth frame object that will be captured.
     * @param colorFrame Reference to color frame object that will be captured.
     * @param colorizedDepthFrame Reference to colorized depth frame object that will be captured.
     * @see https://dev.intelrealsense.com/docs/docs-get-started
     * @see getVideoFramesCV(unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale)
     * @see getVideoFrames         (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale)
     */
    void getVideoFramesRS                       (unsigned int user_nFrame, rs2::pipeline & pipelineStream,
                                                 rs2::depth_frame & depthFrames, rs2::frame & colorFrames,
                                                 rs2::frame & colorizedDepthFrames) override;
};

#endif /* RealSenseManager_hpp */
