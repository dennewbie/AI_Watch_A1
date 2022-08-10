//
//  FacadeSingleton.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 20/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

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
    


    /**
     * @brief Construct a new Facade Singleton object.
     * @param expected_argc the number of parameters that the program expects to find in the configuration file.
     * @param expectedUsageMessage a simple message that lets the user understand how to properly run the
     * executable.
     */
    FacadeSingleton (const int expected_argc = 0, const char * expectedUsageMessage = nullptr);
    /**
     * @brief Destroy the Facade Singleton object.
     */
    ~FacadeSingleton(void);
protected:
    /**
     * @brief Set the RealSeneManager pointer.
     * @param cameraManager pointer to a RealSeneManager object.
     * @see RealSenseManager.hpp
     */
    void setCameraManager               (RealSenseManager * cameraManager);
    /**
     * @brief Set the OutputManager pointer.
     * @param outputManager pointer to an OutputManager object.
     * @see OutputManager.hpp
     */
    void setOutputManager               (OutputManager * outputManager);
    /**
     * @brief Set the OpenCV_Manager pointer.
     * @param openCV_Manager pointer to an OpenCV_Manager object.
     * @see OpenCV_Manager.hpp
     */
    void setOpenCV_Manager              (OpenCV_Manager * openCV_Manager);
    /**
     * @brief Set the UsageManager pointer.
     * @param usageManager pointer to an UsageManager object.
     * @see UsageManager.hpp
     */
    void setUsageManager                (UsageManager * usageManager);
    /**
     * @brief Set the CoordinateMappingManager pointer.
     * @param coordinateMappingManager pointer to an CoordinateMappingManager object.
     * @see CoordinateMappingManager.hpp
     */
    void setCoordinateMappingManager    (CoordinateMappingManager * coordinateMappingManager);
    /**
     * @brief Set the ImageManager pointer.
     * @param imageManager pointer to an ImageManager object.
     * @see ImageManager.hpp
     */
    void setImageManager                (ImageManager * imageManager);
    /**
     * @brief Set the KafkaManager pointer.
     * @param kafkaManager pointer to a KafkaManager object.
     * @see KafkaManager.hpp
     */
    void setKafkaManager                (KafkaManager * kafkaManager);
public:
    /**
     * @brief Disabling the possibility to clone the Singleton object. 
     * Singletons should not be cloneable.
     * @param other 
     */
    FacadeSingleton (FacadeSingleton & other) = delete;
    /**
     * @brief Disabling the possibility to assign a Singleton object.
     * Singletons should not be assignable.
     */
    void operator=  (const FacadeSingleton &) = delete;
    


    /**
     * @brief Get the unique class instance, given input parameters. This method
     * should be called the first time when we want to create a reference to the 
     * object of this class.
     * @param expected_argc the number of parameters that the program expects to find in the configuration file.
     * @param expectedUsageMessage a simple message that lets the user understand how to properly run the
     * @return FacadeSingleton *
     */
    static FacadeSingleton * getInstance (const int expected_argc, const char * expectedUsageMessage);
    /**
     * @brief Get the unique class instance. This methods should be called in the following
     * scenario: when we just want to retrieve the reference to the object of this class.
     * @return FacadeSingleton * 
     */
    static FacadeSingleton * getInstance (void);



    /**
     * @brief Get the RealSenseManager pointer.
     * @return RealSenseManager * 
     * @see RealSenseManager.hpp
     */
    RealSenseManager * getCameraManager                     (void);
    /**
     * @brief Get the OutputManager pointer.
     * @return OutputManager * 
     * @see OutputManager.hpp
     */
    OutputManager * getOutputManager                        (void);
    /**
     * @brief Get the OpenCV_Manager pointer.
     * @return OpenCV_Manager * 
     * @see OpenCV_Manager.hpp
     */
    OpenCV_Manager * getOpenCV_Manager                      (void);
    /**
     * @brief Get the UsageManager pointer.
     * @return UsageManager * 
     * @see UsageManager.hpp
     */
    UsageManager * getUsageManager                          (void);
    /**
     * @brief Get the CoordinateMappingManager pointer.
     * @return CoordinateMappingManager * 
     * @see constants.hpp
     * @see CoordinateMappingManager.hpp
     */
    CoordinateMappingManager * getCoordinateMappingManager  (void);
    /**
     * @brief Get the ImageManager pointer.
     * @return ImageManager * 
     * @see ImageManager.hpp
     */
    ImageManager * getImageManager                          (void);
    /**
     * @brief Get the KafkaManager pointer.
     * @return KafkaManager * 
     * @see KafkaManager.hpp
     */
    KafkaManager * getKafkaManager                          (void);


    
    /**
     * @brief This method is useful to invoke at the boot of the program where we want
     * to initialize the different mangers, start the camera and set up the related
     * environment.
     * @param pipelineStream The pipeline simplifies the user interaction with the device and computer vision processing modules. 
     * The class abstracts the camera configuration and streaming, and the vision modules triggering and threading. 
     * It lets the application focus on the computer vision output of the modules, or the device output data. 
     * The pipeline can manage computer vision modules, which are implemented as a processing block. 
     * The pipeline is the consumer of the processing block interface, while the application consumes the computer vision interface.
     * @param color_intrin Reference to color video stream intrinsics.
     * @param scale Pointer to scaling factor.
     * @param resX x resoultion <->
     * @param resY y resolution
     * @param destinationKafkaTopic the destination's kafka topic's name.
     * @see https://dev.intelrealsense.com/docs/docs-get-started
     * @see startEnvironment(rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale, unsigned short int resX, unsigned short int resY, bool firstBoot)
     */
    void startEnvironment       (rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale,
                                 unsigned short int resX, unsigned short int resY, const char * destinationKafkaTopic);
    /**
     * @brief Get user_nFrame video frames from the pipeline by applying a specific scaling factor.
     * @param user_nFrame frame's number to capture according to user choice.
     * @param pipelineStream The pipeline simplifies the user interaction with the device and computer vision processing modules. 
     * The class abstracts the camera configuration and streaming, and the vision modules triggering and threading. 
     * It lets the application focus on the computer vision output of the modules, or the device output data. 
     * The pipeline can manage computer vision modules, which are implemented as a processing block. 
     * The pipeline is the consumer of the processing block interface, while the application consumes the computer vision interface.
     * @param scale Scaling factor.
     * @see https://dev.intelrealsense.com/docs/docs-get-started
     * @see getVideoFramesCV(unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale)
     * @see getVideoFramesRS(unsigned int user_nFrame, rs2::pipeline & pipelineStream, rs2::depth_frame & depthFrame, rs2::frame & colorFrame, rs2::frame & colorizedDepthFrame)
     */
    void getVideoFrames         (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale);
    /**
     * @brief Start and execute OpenPose submodule.
     * @param argc arguments' number specified on launch (from main).
     * @param argv arguments' specified on launch (from main).
     * @see https://cmu-perceptual-computing-lab.github.io/openpose/web/html/doc/md_doc_00_index.html
     */
    void getVideoBodyKeyPoints  (int * argc, char *** argv);
    /**
     * @brief Retrieve OpenPose's output, convert it to RealSense coordinate's space, show results and save them.
     * @param user_nFrame frame's number to capture according to user choice.
     * @see showSkeletonsCV(unsigned int user_nFrame)
     */
    void showSkeletons          (unsigned int user_nFrame);
    /**
     * @brief Send saved results by getVideoBodyKeyPoints(...) via Kafka using the KafkaManager.
     * @param user_nFrame frame's number to capture according to user choice.
     * @see https://kafka.apache.org/documentation/
     * @see sendData(const char * key, Json::Value root)
     */
    void sendData               (unsigned int user_nFrame);
    /**
     * @brief This method cleans the build folder, in order to prepare the environment for the next loop iteration. It does this by deleting all images and JSON files
     * produced during the current loop iteration.
     */
    void cleanBuildFolder       (void);
};

#endif /* FacadeSingleton_hpp */
