//
//  RealSenseD435Manager.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#ifndef RealSenseD435Manager_hpp
#define RealSenseD435Manager_hpp

#include <librealsense2/rs.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "constants.hpp"



class RealSenseD435Manager {
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
    RealSenseD435Manager                        (void);
    long unsigned int getFrameID                (void);
    struct rs2_intrinsics & get_color_intrin    (void);
    void startEnvironment                       (rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale,
                                                 unsigned short int resX, unsigned short int resY);
    void getVideoFrames                         (unsigned int user_nFrame, rs2::pipeline & pipelineStream,
                                                 std::vector <rs2::depth_frame> & depthFrames, std::vector <rs2::frame> & colorFrames,
                                                 std::vector <rs2::frame> & colorizedDepthFrames);
};

#endif /* RealSenseD435Manager_hpp */
