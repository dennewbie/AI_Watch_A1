//
//  FacadeSingleton.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 20/07/22.
//

#ifndef FacadeSingleton_hpp
#define FacadeSingleton_hpp

#include "../Command/SystemCommand.hpp"
#include "../Managers/RealSenseManagers/RealSenseManager.hpp"
#include "../Managers/OutputManagers/OutputManager.hpp"
#include "../Managers/OpenCV_Manager.hpp"
#include "../Managers/UsageManager.hpp"



class RealSenseManager;
class OutputManager;
class OpenCV_Manager;
class UsageManager;



class FacadeSingleton {
private:
    static FacadeSingleton *    sharedInstance;
    static std::mutex           singletonMutex;
    
    RealSenseManager *          cameraManager;
    OutputManager *             outputManager;
    OpenCV_Manager *            openCV_Manager;
    UsageManager *              usageManager;
    
    FacadeSingleton (const int argc = 0, const char ** argv = nullptr, const int expected_argc = 0, const char * expectedUsageMessage = nullptr);
protected:
    void setCameraManager (RealSenseManager * cameraManager);
    void setOutputManager (OutputManager * outputManager);
    void setOpenCV_Manager (OpenCV_Manager * openCV_Manager);
    void setUsageManager (UsageManager * usageManager);
public:
    FacadeSingleton (FacadeSingleton & other) = delete;
    void operator=  (const FacadeSingleton &) = delete;
    
    static FacadeSingleton * getInstance (const int argc, const char ** argv, const int expected_argc, const char * expectedUsageMessage);
    static FacadeSingleton * getInstance (void);
    
    RealSenseManager * getCameraManager  (void);
    OutputManager * getOutputManager     (void);
    OpenCV_Manager * getOpenCV_Manager   (void);
    UsageManager * getUsageManager       (void);
    
    void startEnvironment       (rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale,
                                 unsigned short int resX, unsigned short int resY);
    void getVideoFrames         (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale);
    void getVideoBodyKeyPoints  (void);
    void showSkeleton           (unsigned int user_nFrame, Json::Value & currentJSON);
};

#endif /* FacadeSingleton_hpp */
