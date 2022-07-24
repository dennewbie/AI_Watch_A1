//
//  UsageManager.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#ifndef UsageManager_hpp
#define UsageManager_hpp

#include <string>
#include <opencv2/core.hpp>
#include <mutex>
#include "../constants.hpp"



class UsageManager {
private:
    static UsageManager *       sharedInstance;
    static std::mutex           singletonMutex;
    
    const int                   argc;
    const char **               argv;
    const int                   expected_argc;
    const char *                expectedUsageMessage;
    
    const int get_argc                          (void);
    const int get_expected_argc                 (void);
    const char * get_expectedUsageMessage       (void);
    void checkUsage                             (void);
    
    UsageManager (const int argc = 0, const char ** argv = nullptr, const int expected_argc = 0, const char * expectedUsageMessage = nullptr) : argc(argc), argv(argv), expected_argc(expected_argc), expectedUsageMessage(expectedUsageMessage) {
        checkUsage();
    }
public:
    static UsageManager * getInstance (const int argc, const char ** argv, const int expected_argc, const char * expectedUsageMessage);
    static UsageManager * getInstance (void);
    
    static const char ** get_argv     (void);
    
};

#endif /* UsageManager_hpp */
