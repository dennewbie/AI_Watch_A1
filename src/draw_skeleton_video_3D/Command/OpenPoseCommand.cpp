//
//  OpenPoseCommand.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "SystemCommand.hpp"



void OpenPoseCommand::setCommand (void) {
    UsageManager * usageManagerInstance = UsageManager::getInstance();
    if (usageManagerInstance == nullptr) CV_Error(USAGE_MANAGER_NULLPTR_ERROR, USAGE_MANAGER_NULLPTR_SCOPE);
    const char ** argv = usageManagerInstance->get_argv();
    std::stringstream openPoseTerminalCommand;
    const char * openPoseFolder = argv[openPoseFolderOffset];
    const char * openPoseExecuteCommand = argv[openPoseExecuteCommandOffset];
    const char * imagesFolder = argv[imagesFolderOffset];
    const char * outputFolder = argv[outputFolderOffset];
    
    openPoseTerminalCommand << "cd " << openPoseFolder << " && " << openPoseExecuteCommand
                            << " --num_gpu 1 --num_gpu_start 2 --display 0 --render_pose 0 --image_dir "
                            << imagesFolder << "rgb/" << " --write_json " << outputFolder << "op/"
                            << " --logging_level 255 > /dev/null";
    SystemCommand::command = std::string(openPoseTerminalCommand.str());
}
