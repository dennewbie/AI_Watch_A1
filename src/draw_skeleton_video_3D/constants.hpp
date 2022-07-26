//
//  constants.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 20/07/22.
//

#ifndef constants_h
#define constants_h



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

static const short int CALLOC_ERROR = 6;
static const char * CALLOC_SCOPE = "Error during calloc";

static const short int FACADE_SINGLETON_NULLPTR_ERROR = 7;
static const char * FACADE_SINGLETON_NULLPTR_SCOPE = "FacadeSingleton::getInstance() returns nullptr";

static const short int USAGE_MANAGER_NULLPTR_ERROR = 8;
static const char * USAGE_MANAGER_NULLPTR_SCOPE = "UsageManager::getInstance() returns nullptr";



static const short int ESC_KEY = 27;

static const float depth_min = 0.10;
static const float depth_max = 6.0;

static const char * JSON_FILE_PATH = "skeletonPoints3D.json";

static const short int programNameOffset = 0;
static const short int openPoseFolderOffset = 1;
static const short int openPoseExecuteCommandOffset = 2;
static const short int imagesFolderOffset = 3;
static const short int outputFolderOffset = 4;

static const short int openPoseBodyKeyPointsNumber = 24;

#endif /* constants_h */
