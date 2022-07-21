//
//  FacadeSingleton.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 20/07/22.
//

#ifndef FacadeSingleton_hpp
#define FacadeSingleton_hpp

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <json/value.h>
#include <json/json.h>
#include <librealsense2/rs.hpp>
#include "Skeleton.hpp"
#include "constants.hpp"



class FacadeSingleton {
private:
    static FacadeSingleton *    sharedInstance;
    static std::mutex           singletonMutex;
    const int                   argc;
    const char **               argv;
    const int                   expected_argc;
    const char *                expectedUsageMessage;
    long unsigned int           frameID;
    rs2::align                  align;
    struct rs2_intrinsics       depth_intrin;
    struct rs2_intrinsics       color_intrin;
    struct rs2_extrinsics       depth_to_color;
    struct rs2_extrinsics       color_to_depth;
    
    FacadeSingleton (const int argc = 0, const char ** argv = nullptr, const int expected_argc = 0, const char * expectedUsageMessage = nullptr) : argc(argc), argv(argv), expected_argc(expected_argc), expectedUsageMessage(expectedUsageMessage), align(RS2_STREAM_COLOR) {
        checkUsage();
        setFrameID(0);
    }
    
    ~FacadeSingleton () {}
    

    
protected:
    void setFrameID         (long unsigned int newFrameID);
    void set_align          (rs2::align align);
    void set_depth_intrin   (struct rs2_intrinsics depth_intrin);
    void set_color_intrin   (struct rs2_intrinsics & color_intrin);
    void set_depth_to_color (struct rs2_extrinsics depth_to_color);
    void set_color_to_depth (struct rs2_extrinsics color_to_depth);
    
    const int get_argc                          (void);
    const char ** get_argv                      (void);
    const int get_expected_argc                 (void);
    const char * get_expectedUsageMessage       (void);
    long unsigned int getFrameID                (void);
    rs2::align get_align                        (void);
    struct rs2_intrinsics get_depth_intrin      (void);
    
    struct rs2_extrinsics get_depth_to_color    (void);
    struct rs2_extrinsics get_color_to_depth    (void);
    
    void checkUsage             (void);

    
    
public:
    FacadeSingleton (FacadeSingleton & other) = delete;
    void operator=  (const FacadeSingleton &) = delete;
    struct rs2_intrinsics & get_color_intrin    (void);
    
    static FacadeSingleton * getInstance (const int argc, const char ** argv, const int expected_argc, const char * expectedUsageMessage);
    static FacadeSingleton * getInstance (void);
    
    
    void loadImage              (std::string imagePath, int loadType, cv::Mat & inputImage);
    void saveImage              (std::string imageSavePath, cv::Mat & imageToSave);
    void loadJSON               (std::string jsonFilePath, Json::Value & currentJSON);
    cv::Mat realsenseFrameToMat (const rs2::frame & singleFrame);
    void startEnvironment       (rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale, unsigned short int resX, unsigned short int resY);
    void getVideoFrames         (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale);
    void getVideoBodyKeyPoints  (void);
    void showSkeleton           (unsigned int user_nFrame, Json::Value & currentJSON);
};

#endif /* FacadeSingleton_hpp */
