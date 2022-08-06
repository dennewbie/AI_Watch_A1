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
    
    int *                       argc;
    char ***                    argv;
    const int                   expected_argc;
    const char *                expectedUsageMessage;
    
    const int get_expected_argc                 (void);
    const char * get_expectedUsageMessage       (void);
    void checkUsage                             (void);
    
    UsageManager (int * argc = nullptr, char *** argv = nullptr, const int expected_argc = 0, const char * expectedUsageMessage = nullptr) : argc(argc), argv(argv), expected_argc(expected_argc), expectedUsageMessage(expectedUsageMessage) {
        checkUsage();
    }
public:
    UsageManager (UsageManager & other) = delete;
    void operator=  (const UsageManager &) = delete;
    
    virtual ~UsageManager();
    static UsageManager * getInstance (int * argc, char *** argv, const int expected_argc, const char * expectedUsageMessage);
    static UsageManager * getInstance (void);
    
    int * get_argc         (void);
    char *** get_argv      (void);
    
};

#endif /* UsageManager_hpp */
