//
//  FacadeSingleton.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 20/07/22.
//

#include "FacadeSingleton.hpp"



FacadeSingleton * FacadeSingleton::sharedInstance { nullptr };
std::mutex FacadeSingleton::singletonMutex;



FacadeSingleton::FacadeSingleton (const int expected_argc, const char * expectedUsageMessage) {
    std::ifstream inputFile(CONF_FILE_PATH);
    std::string singleLineConfigurationFile;

//    int * fileArgc = (int *) calloc(1, sizeof(int));
//    * fileArgc = (int) totalFileParameters;
//    char *** fileArgv = (char ***) calloc(1, sizeof(char **));
//    * fileArgv = (char **) calloc(totalFileParameters, sizeof(char **));
//    unsigned char rowCounter = 0;
//    if (!fileArgc || !fileArgv || ! * fileArgv) CV_Error(CALLOC_ERROR, CALLOC_SCOPE);
//    // read usage's configuration parameters from file
//    while (inputFile >> singleLineConfigurationFile) {
//        (* fileArgv)[rowCounter] = (char *) calloc((unsigned int) singleLineConfigurationFile.size(), sizeof(char));
//        if (!(* fileArgv)[rowCounter]) CV_Error(CALLOC_ERROR, CALLOC_SCOPE);
//        strcpy((* fileArgv)[rowCounter], singleLineConfigurationFile.c_str());
//        rowCounter++;
//    }

    int * fileArgc = new (std::nothrow) int;
    * fileArgc = (int) totalFileParameters;
    char *** fileArgv = new (std::nothrow) char **;
    * fileArgv = new (std::nothrow) char *[totalFileParameters];
    unsigned char rowCounter = 0;

    if (!fileArgc || !fileArgv || ! * fileArgv) CV_Error(NEW_ALLOC_ERROR, NEW_ALLOC_SCOPE);
    // Read usage's configuration parameters from file
    while (inputFile >> singleLineConfigurationFile) {
        (* fileArgv)[rowCounter] = new (std::nothrow) char [(unsigned int) singleLineConfigurationFile.size()];
        if (!(* fileArgv)[rowCounter]) CV_Error(NEW_ALLOC_ERROR, NEW_ALLOC_SCOPE);
        strcpy((* fileArgv)[rowCounter], singleLineConfigurationFile.c_str());
        rowCounter++;
    }
    
    setUsageManager(UsageManager::getInstance(fileArgc, fileArgv, expected_argc, expectedUsageMessage));
}

FacadeSingleton::~FacadeSingleton (void) {
    delete getCameraManager();
    delete getOutputManager();
    delete getOpenCV_Manager();
    delete getUsageManager();
    delete getCoordinateMappingManager();
    delete getImageManager();
//    delete getKafkaManager();
    delete sharedInstance;
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

void FacadeSingleton::setCoordinateMappingManager (CoordinateMappingManager * coordinateMappingManager) {
    this->coordinateMappingManager = coordinateMappingManager;
}

void FacadeSingleton::setImageManager (ImageManager * imageManager) {
    this->imageManager = imageManager;
}

void FacadeSingleton::setKafkaManager (KafkaManager * kafkaManager) {
    this->kafkaManager = kafkaManager;
}



FacadeSingleton * FacadeSingleton::getInstance (const int expected_argc, const char * expectedUsageMessage) {
    std::lock_guard <std::mutex> lock(singletonMutex);
    if (sharedInstance == nullptr) sharedInstance = new FacadeSingleton(expected_argc, expectedUsageMessage);
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

CoordinateMappingManager * FacadeSingleton::getCoordinateMappingManager (void) {
    return this->coordinateMappingManager;
}

ImageManager * FacadeSingleton::getImageManager (void) {
    return this->imageManager;
}

KafkaManager * FacadeSingleton::getKafkaManager (void) {
    return this->kafkaManager;
}

void FacadeSingleton::startEnvironment (rs2::pipeline & pipelineStream, struct rs2_intrinsics & color_intrin, float * scale, unsigned short int resX, unsigned short int resY, const char * destinationKafkaTopic) {
    FacadeSingleton::setCameraManager(new RealSenseD435Manager());
    FacadeSingleton::setOutputManager(new OutputManagerJSON());
    FacadeSingleton::setOpenCV_Manager(new OpenCV_Manager());
    FacadeSingleton::setCoordinateMappingManager(new UnityCoordinateMappingManager());
    FacadeSingleton::setImageManager(new ImageManager());
//    FacadeSingleton::setKafkaManager(new KafkaManager(destinationKafkaTopic));
    FacadeSingleton::getCameraManager()->startEnvironment(pipelineStream, color_intrin, scale, resX, resY, FIRST_BOOT);
    cleanBuildFolder();
}

void FacadeSingleton::getVideoFrames (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale) {
    getOpenCV_Manager()->getVideoFramesCV(user_nFrame, pipelineStream, scale);
}

void FacadeSingleton::getVideoBodyKeyPoints (int * argc, char *** argv) {
    SystemCommand * openPoseCommand = new OpenPoseCommand();
    openPoseCommand->executeCommand(argc, argv);
    delete openPoseCommand;
}

void FacadeSingleton::showSkeletons (unsigned int user_nFrame) {
    getOpenCV_Manager()->showSkeletonsCV(user_nFrame);
}

void FacadeSingleton::sendData (unsigned int user_nFrame) {
    char ** argv = * FacadeSingleton::getUsageManager()->get_argv(), * outputFolder = argv[outputFolderOffset];
    unsigned int frameID = FacadeSingleton::getCameraManager()->getFrameID(), currentImageID;
    OutputManagerJSON * myOutputManagerJSON = (OutputManagerJSON *) FacadeSingleton::getOutputManager();
    
//    for (unsigned int nFrame = 0; nFrame < user_nFrame; nFrame++) {
//        Json::Value currentJSON;
//        std::stringstream outputJsonFilePath;
//        currentImageID = frameID - user_nFrame + nFrame;
//        outputJsonFilePath << outputFolder << "movement/frame" << currentImageID << "_skeletonsPoints3D.json";
//        if (myOutputManagerJSON->loadJSON(outputJsonFilePath.str(), currentJSON)) {
//            std::string key = std::to_string(currentImageID);
//            FacadeSingleton::getKafkaManager()->sendData(key.c_str(), currentJSON);
//        }
//    }
}

void FacadeSingleton::cleanBuildFolder (void) {
    SystemCommand * cleanCommand = new CleanCommand();
    cleanCommand->executeCommand(getUsageManager()->get_argc(), getUsageManager()->get_argv());
    delete cleanCommand;
}
