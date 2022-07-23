//
//  OpenPoseCommand.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "SystemCommand.hpp"



void OpenPoseCommand::setCommand (void) {
    std::stringstream openPoseTerminalCommand;
    openPoseTerminalCommand << "cd " << FacadeSingleton::getInstance()->get_argv()[1] << " && "
                            << FacadeSingleton::getInstance()->get_argv()[2]
                            << " --num_gpu 1 --num_gpu_start 2 --display 0 --render_pose 0 --image_dir "
                            << FacadeSingleton::getInstance()->get_argv()[3] << "rgb/ --write_json "
                            << FacadeSingleton::getInstance()->get_argv()[4] << "op/ --logging_level 255 > /dev/null";
    SystemCommand::command = std::string(openPoseTerminalCommand.str());
}
