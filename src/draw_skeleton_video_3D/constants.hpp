//
//  constants.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 20/07/22.
//

#ifndef constants_h
#define constants_h



// Error codes and error messages declaration.
static const short int CHECK_USAGE_ERROR = 1;
static const char * CHECK_USAGE_SCOPE = "usage";

static const short int LOAD_IMAGE_ERROR = 2;
static const char * LOAD_IMAGE_SCOPE = "Could not open or find the image";

static const short int SAVE_IMAGE_ERROR = 3;
static const char * SAVE_IMAGE_SCOPE = "Could not save the image on disk";

static const short int LOAD_JSON_ERROR = 4;
static const char * LOAD_JSON_SCOPE = "Could not open or find the JSON file";

static const short int RS_CAMERA_ERROR = 5;
static const char * RS_CAMERA_SCOPE = "Troubles during initialization of RealSense Camera";

static const short int FACADE_SINGLETON_NULLPTR_ERROR = 6;
static const char * FACADE_SINGLETON_NULLPTR_SCOPE = "FacadeSingleton::getInstance() returns nullptr";

static const short int USAGE_MANAGER_NULLPTR_ERROR = 7;
static const char * USAGE_MANAGER_NULLPTR_SCOPE = "UsageManager::getInstance() returns nullptr";

static const short int RDKAFKA_GET_KEYS_FROM_JSON_ERROR = 8;
static const char * RDKAFKA_GET_KEYS_FROM_JSON_SCOPE = "KafkaManager::loadConfigurationGroup() error during g_key_file_get_keys()";

static const short int RDKAFKA_GET_KEY_FROM_JSON_ERROR = 9;
static const char * RDKAFKA_GET_KEY_FROM_JSON_SCOPE = "KafkaManager::loadConfigurationGroup() error during g_key_file_get_string()";

static const short int RDKAFKA_CONF_SET_ERROR = 10;
static const char * RDKAFKA_CONF_SET_SCOPE = "KafkaManager::loadConfigurationGroup() error during rd_kafka_conf_set()";

static const short int NEW_ALLOC_ERROR = 11;
static const char * NEW_ALLOC_SCOPE = "Error while allocating dynamic memory with new.";



// Other useful constants declaration.
static const short int ESC_KEY = 27;

static const float depth_min = 0.10;
static const float depth_max = 6.0;

static const char * JSON_FILE_PATH = "skeletonsPoints3D.json";

static const short int programNameOffset = 0;
static const short int openPoseFolderOffset = 1;
static const short int openPoseExecuteCommandOffset = 2;
static const short int imagesFolderOffset = 3;
static const short int outputFolderOffset = 4;

static const short int openPoseBodyKeyPointsNumber = 24;

static const float skeletonThreshold = 0.05;
//static const short int framesToSkip = 30;
static const short int framesToSkip = 1;
static const bool NOT_FIRST_BOOT = false;
static const bool FIRST_BOOT = true;

#endif /* constants_h */
