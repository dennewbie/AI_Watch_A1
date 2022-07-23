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
#include "Skeleton.hpp"
#include "constants.hpp"
#include "../Command/SystemCommand.hpp"
#include "../Managers/RealSenseManagers/RealSenseManager.hpp"
#include "../Managers/OutputManagers/OutputManager.hpp"



class FacadeSingleton {
private:
    static FacadeSingleton *    sharedInstance;
    static std::mutex           singletonMutex;
    const int                   argc;
    const char **               argv;
    const int                   expected_argc;
    const char *                expectedUsageMessage;
    RealSenseManager *          cameraManager;
    OutputManager *             outputManager;
    
    FacadeSingleton (const int argc = 0, const char ** argv = nullptr, const int expected_argc = 0, const char * expectedUsageMessage = nullptr) : argc(argc), argv(argv), expected_argc(expected_argc), expectedUsageMessage(expectedUsageMessage) {
        checkUsage();
    }
protected:
    void setCameraManager (RealSenseManager * cameraManager);
    void setOutputManager (OutputManager * outputManager);
    
    const int get_argc                          (void);
    const int get_expected_argc                 (void);
    const char * get_expectedUsageMessage       (void);
    void checkUsage                             (void);
public:
    FacadeSingleton (FacadeSingleton & other) = delete;
    void operator=  (const FacadeSingleton &) = delete;
    
    static FacadeSingleton * getInstance (const int argc, const char ** argv, const int expected_argc, const char * expectedUsageMessage);
    static FacadeSingleton * getInstance (void);
    const char ** get_argv               (void);
    RealSenseManager * getCameraManager  (void);
    OutputManager * getOutputManager     (void);
    
    void loadImage              (std::string imagePath, int loadType, cv::Mat & inputImage);
    void saveImage              (std::string imageSavePath, cv::Mat & imageToSave);
    cv::Mat realsenseFrameToMat (const rs2::frame & singleFrame);
    void startEnvironment       (rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale,
                                 unsigned short int resX, unsigned short int resY);
    void getVideoFrames         (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale);
    void getVideoBodyKeyPoints  (void);
    void showSkeleton           (unsigned int user_nFrame, Json::Value & currentJSON);
};

#endif /* FacadeSingleton_hpp */
