//
//  FacadeSingleton.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 20/07/22.
//

#include "FacadeSingleton.hpp"


// costanti al posto degli indici di argv
// cambiare nomi metodi uguali in classi diverse
FacadeSingleton * FacadeSingleton::sharedInstance { nullptr };
std::mutex FacadeSingleton::singletonMutex;


FacadeSingleton::FacadeSingleton (const int argc = 0, const char ** argv = nullptr, const int expected_argc = 0, const char * expectedUsageMessage = nullptr) {
    setUsageManager(new UsageManager::getInstance(argc, argv, expected_argc, expectedUsageMessage));
}

void FacadeSingleton::setCameraManager (RealSenseManager * cameraManager) {
    this->cameraManager = cameraManager;
}

void FacadeSingleton::setOutputManager (OutputManager * outputManager) {
    this->outputManager = outputManager;
}

void FacadeSingleton::setOpenCV_Manager(OpenCV_Manager * openCV_Manager) {
    this->openCV_Manager = openCV_Manager;
}

void FacadeSingleton::setUsageManager(UsageManager * usageManager) {
    this->usageManager = usageManager;
}




FacadeSingleton * FacadeSingleton::getInstance (const int argc, const char ** argv, const int expected_argc, const char * expectedUsageMessage) {
    std::lock_guard <std::mutex> lock(singletonMutex);
    if (sharedInstance == nullptr) sharedInstance = new FacadeSingleton(argc, argv, expected_argc, expectedUsageMessage);
    return sharedInstance;
}

FacadeSingleton * FacadeSingleton::getInstance (void) {
    std::lock_guard <std::mutex> lock(singletonMutex);
    if (sharedInstance == nullptr) return nullptr;
    return sharedInstance;
}

RealSenseManager * FacadeSingleton::getCameraManager (void) {
    return this->cameraManager;
}

OutputManager * FacadeSingleton::getOutputManager (void) {
    return this->outputManager;
}

OpenCV_Manager * FacadeSingleton::getOpenCV_Manager (void) {
    return this->openCV_Manager;
}

UsageManager * FacadeSingleton::getUsageManager (void) {
    return this->usageManager;
}

void FacadeSingleton::startEnvironment (rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale, unsigned short int resX, unsigned short int resY) {
    FacadeSingleton::setCameraManager(new RealSenseD435Manager());
    FacadeSingleton::setOutputManager(new OutputManagerJSON());
    FacadeSingleton::setOpenCV_Manager(new OpenCV_Manager());
    FacadeSingleton::getCameraManager()->startEnvironment(pipelineStream, color_intrin, scale, resX, resY);
    
    CleanCommand cleanCommand;
//    cleanCommand.executeCommand();
    std::stringstream cleanSK;
    cleanSK << "rm -r " << FacadeSingleton::get_argv()[3] << "sk/ > /dev/null && mkdir " << FacadeSingleton::get_argv()[3] << "sk";
    std::system(cleanSK.str().c_str());
}

void FacadeSingleton::getVideoFrames (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale) {
    getOpenCV_Manager()->getVideoFrames(user_nFrame, pipelineStream, scale);
}

void FacadeSingleton::getVideoBodyKeyPoints (void) {
    OpenPoseCommand openPoseCommand;
//    openPoseCommand.executeCommand();
}

void FacadeSingleton::showSkeleton (unsigned int user_nFrame, Json::Value & currentJSON) {
    getOpenCV_Manager()->showSkeleton(user_nFrame, currentJSON);
}
