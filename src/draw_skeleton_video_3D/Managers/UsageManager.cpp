//
//  UsageManager.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "UsageManager.hpp"



UsageManager * UsageManager::sharedInstance { nullptr };
std::mutex UsageManager::singletonMutex;



void UsageManager::checkUsage (void) {
    if (get_argc() != get_expected_argc()) {
        std::string buffer = "Usage: ./" + std::string(get_argv()[programNameOffset]) + std::string(get_expectedUsageMessage()) + " -- " + std::string(CHECK_USAGE_SCOPE);
        CV_Error(CHECK_USAGE_ERROR, buffer);
    }
}

const int UsageManager::get_argc (void) {
    return this->argc;
}

const int UsageManager::get_expected_argc (void) {
    return this->expected_argc;
}

const char * UsageManager::get_expectedUsageMessage (void) {
    return this->expectedUsageMessage;
}



UsageManager * UsageManager::getInstance (const int argc, const char ** argv, const int expected_argc, const char * expectedUsageMessage) {
    std::lock_guard <std::mutex> lock(singletonMutex);
    if (sharedInstance == nullptr) sharedInstance = new UsageManager(argc, argv, expected_argc, expectedUsageMessage);
    return sharedInstance;
}

UsageManager * UsageManager::getInstance (void) {
    std::lock_guard <std::mutex> lock(singletonMutex);
    if (sharedInstance == nullptr) return nullptr;
    return sharedInstance;
}

const char ** UsageManager::get_argv (void) {
    std::stringstream openPoseTerminalCommand;
    UsageManager * usageManagerInstance = UsageManager::getInstance();
    if (usageManagerInstance == nullptr) CV_Error(USAGE_MANAGER_NULLPTR_ERROR, USAGE_MANAGER_NULLPTR_SCOPE);
    return usageManagerInstance->argv;
}
