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



/**
 * UsageManager class is a class that keeps track of configuration parameters read from a configuration file, 
 * checks if these parameters are valid, and if they are equal to the number of the expected parameters. Furthermore, 
 * it offers an on-demand service by returning the parameters read from the file to the callers. 
 * @brief UsageManager class is a utility class that helps with configuration parameters.
 */
class UsageManager {
private:
    /**
     * @brief The field for storing the singleton instance.
     */
    static UsageManager *       sharedInstance;
    /**
     * @brief Mutex for thread-safe access.
     */
    static std::mutex           singletonMutex;
    


    /**
     * @brief configuration parameters' number.
     */
    int *                       argc;
    /**
     * @brief configuration parameters.
     */
    char ***                    argv;
    /**
     * @brief expected configuration parameters' number.
     */
    const int                   expected_argc;
    /**
     * @brief a simple message that lets the user understand how to properly run the executable.
     */
    const char *                expectedUsageMessage;
    


    /**
     * @brief Get the expected argc value.
     * @return const int 
     */
    const int get_expected_argc                 (void);
    /**
     * @brief Get the expected usage message.
     * @return const char * 
     */
    const char * get_expectedUsageMessage       (void);
    /**
     * @brief Checks if the configuration parameters are valid and if they are equal to the number of the expected parameters. 
     * If not, it raises an error.
     */
    void checkUsage                             (void);



    /**
     * @brief Construct a new UsageManager object
     * @param argc configuration parameters' number.
     * @param argv  configuration parameters.
     * @param expected_argc expected configuration parameters' number.
     * @param expectedUsageMessage a simple message that lets the user understand how to properly run the executable.
     */
    UsageManager (int * argc = nullptr, char *** argv = nullptr, const int expected_argc = 0, const char * expectedUsageMessage = nullptr) : argc(argc), argv(argv), expected_argc(expected_argc), expectedUsageMessage(expectedUsageMessage) {
        checkUsage();
    }
public:
    /**
     * @brief Disabling the possibility to clone the Singleton object. 
     * Singletons should not be cloneable.
     * @param other 
     */
    UsageManager (UsageManager & other) = delete;
    /**
     * @brief Disabling the possibility to assign a Singleton object.
     * Singletons should not be assignable.
     */
    void operator=  (const UsageManager &) = delete;
    


    /**
     * @brief Destroy the Usage Manager object.
     */
    virtual ~UsageManager();
    /**
     * @brief Get the unique class instance, given input parameters. This method
     * should be called the first time when we want to create a reference to the 
     * object of this class.
     * @param argc configuration parameters' number.
     * @param argv  configuration parameters.
     * @param expected_argc expected configuration parameters' number.
     * @param expectedUsageMessage a simple message that lets the user understand how to properly run the executable.
     * @return UsageManager * 
     */
    static UsageManager * getInstance (int * argc, char *** argv, const int expected_argc, const char * expectedUsageMessage);
    /**
     * @brief Get the unique class instance. This methods should be called in the following
     * scenario: when we just want to retrieve the reference to the object of this class.
     * @return UsageManager* 
     */
    static UsageManager * getInstance (void);
    


    /**
     * @brief Get the argc's pointer.
     * @return int* 
     */
    int * get_argc         (void);
     /**
     * @brief Get the argv's pointer.
     * @return char *** 
     */
    char *** get_argv      (void);
};

#endif /* UsageManager_hpp */
