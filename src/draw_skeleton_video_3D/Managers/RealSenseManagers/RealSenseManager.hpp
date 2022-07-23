//
//  RealSenseManager.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#ifndef RealSenseManager_hpp
#define RealSenseManager_hpp

#include <librealsense2/rs.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "constants.hpp"



class RealSenseManager {
private:
    long unsigned int           frameID;
    rs2::align                  align;
    struct rs2_intrinsics       depth_intrin;
    struct rs2_intrinsics       color_intrin;
    struct rs2_extrinsics       depth_to_color;
    struct rs2_extrinsics       color_to_depth;
protected:
    void setFrameID         (long unsigned int newFrameID);
    void set_align          (rs2::align align);
    void set_depth_intrin   (struct rs2_intrinsics depth_intrin);
    void set_color_intrin   (struct rs2_intrinsics & color_intrin);
    void set_depth_to_color (struct rs2_extrinsics depth_to_color);
    void set_color_to_depth (struct rs2_extrinsics color_to_depth);
    
    rs2::align get_align                        (void);
    struct rs2_intrinsics get_depth_intrin      (void);
    struct rs2_extrinsics get_depth_to_color    (void);
    struct rs2_extrinsics get_color_to_depth    (void);
public:
    RealSenseManager (void);
    long unsigned int getFrameID                (void);
    struct rs2_intrinsics & get_color_intrin    (void);
    virtual void startEnvironment               (rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale,
                                                 unsigned short int resX, unsigned short int resY) = 0;
    virtual void getVideoFrames                 (unsigned int user_nFrame, rs2::pipeline & pipelineStream,
                                                 rs2::depth_frame & depthFrames, rs2::frame & colorFrames,
                                                  rs2::frame & colorizedDepthFrames) = 0;
};

class RealSenseD435Manager : public RealSenseManager {
public:
    void startEnvironment                       (rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale,
                                                 unsigned short int resX, unsigned short int resY);
    void getVideoFrames                         (unsigned int user_nFrame, rs2::pipeline & pipelineStream,
                                                 rs2::depth_frame & depthFrames, rs2::frame & colorFrames,
                                                 rs2::frame & colorizedDepthFrames);
};

#endif /* RealSenseManager_hpp */
