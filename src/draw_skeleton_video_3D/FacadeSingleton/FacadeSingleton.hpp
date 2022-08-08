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
#include "../Managers/CoordinateManagers/CoordinateMappingManager.hpp"
#include "../Managers/ImageManager.hpp"
#include "../Managers/KafkaManager.hpp"
#include <fstream>



class RealSenseManager;
class OutputManager;
class OpenCV_Manager;
class UsageManager;
class CoordinateMappingManager;
class ImageManager;
class KafkaManager;



/**
 * A facade is a structural design pattern that provides a simplified interface to a library, 
 * a framework, or any other complex set of classes. A Facade class can often be transformed into a 
 * Singleton since a single facade object is sufficient in most cases. Since we need just one access 
 * point to this class and since the internal submodules are complex, a class FacadeSingleton 
 * implements both behaviors.  
 * @brief FacadeSingleton class is used as a single access point to a simplified interface.
 */
class FacadeSingleton {
private:
    /**
     * @brief The field for storing the singleton instance.
     */
    static FacadeSingleton *    sharedInstance;
    /**
     * @brief Mutex for thread-safe access.
     */
    static std::mutex           singletonMutex;
    


    /**
     * @brief A pointer to RealSenseManager object. A RealSenseManager object is responsible for 
     * handling the camera setup, frames acquisition and frames post-processing.
     * @see RealSenseManager.hpp
     */
    RealSenseManager *          cameraManager;
    /**
     * @brief A pointer to OutputManager object. An OutputManager object is responsible for 
     * handling the final output generation to send via Kafka later on.
     * @see OutputManager.hpp
     */
    OutputManager *             outputManager;
    /**
     * @brief A pointer to OpenCV_Manager object. An OpenCV_Manager object is responsible for 
     * converting camera frame to an OpenCV matrix and booting building skeletons into the image.
     * @see OpenCV_Manager.hpp
     */
    OpenCV_Manager *            openCV_Manager;
    /**
     * @brief A pointer to UsageManager object. An UsageManager object is responsible for 
     * checking if the parameters read from configuration file are fine, correct and valid. 
     * Furthermore this class provides methods to access this parameters.
     * @see UsageManager.hpp
     */
    UsageManager *              usageManager;
    /**
     * @brief A pointer to CoordinateMappingManager object. A CoordinateMappingManager object is responsible 
     * for transforming one coordinate range values' space into another one. For instance, it can transform 
     * a RealSense coordinates space to meters or to Unity coordinates. In both cases, there are several 
     * parameters to set up regarding the scene and the room where the camera is installed.
     * @see constants.hpp
     * @see CoordinateMappingManager.hpp
     */
    CoordinateMappingManager *  coordinateMappingManager;
    /**
     * @brief A pointer to CoordinateMappingManager object. A CoordinateMappingManager object is responsible 
     * for broad tasks such as loading, saving, and showing images, as well as releasing the memory 
     * allocated for those images.
     * @see ImageManager.hpp
     */
    ImageManager *              imageManager;
    /**
     * @brief A pointer to KafkaManager object. A KafkaManager object is responsible 
     * for sending previously produced JSON output via Kafka.
     * @see KafkaManager.hpp
     */
    KafkaManager *              kafkaManager;
    
    FacadeSingleton (const int expected_argc = 0, const char * expectedUsageMessage = nullptr);
    ~FacadeSingleton(void);
protected:
    void setCameraManager               (RealSenseManager * cameraManager);
    void setOutputManager               (OutputManager * outputManager);
    void setOpenCV_Manager              (OpenCV_Manager * openCV_Manager);
    void setUsageManager                (UsageManager * usageManager);
    void setCoordinateMappingManager    (CoordinateMappingManager * coordinateMappingManager);
    void setImageManager                (ImageManager * imageManager);
    void setKafkaManager                (KafkaManager * kafkaManager);
public:
    FacadeSingleton (FacadeSingleton & other) = delete;
    void operator=  (const FacadeSingleton &) = delete;
    
    static FacadeSingleton * getInstance (const int expected_argc, const char * expectedUsageMessage);
    static FacadeSingleton * getInstance (void);
    
    RealSenseManager * getCameraManager                     (void);
    OutputManager * getOutputManager                        (void);
    OpenCV_Manager * getOpenCV_Manager                      (void);
    UsageManager * getUsageManager                          (void);
    CoordinateMappingManager * getCoordinateMappingManager  (void);
    ImageManager * getImageManager                          (void);
    KafkaManager * getKafkaManager                          (void);
    
    void startEnvironment       (rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale,
                                 unsigned short int resX, unsigned short int resY, const char * destinationKafkaTopic);
    void getVideoFrames         (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale);
    void getVideoBodyKeyPoints  (int * argc, char *** argv);
    void showSkeletons          (unsigned int user_nFrame);
    void sendData               (unsigned int user_nFrame);
};

#endif /* FacadeSingleton_hpp */
