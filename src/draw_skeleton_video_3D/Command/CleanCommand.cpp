//
//  CleanCommand.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "SystemCommand.hpp"



void CleanCommand::setCommand (void) {
    std::stringstream cleanTerminalCommand;
    cleanTerminalCommand << "rm -r " << FacadeSingleton::getInstance()->get_argv()[3] << "rgb/ > /dev/null && "
                            "rm -r " << FacadeSingleton::getInstance()->get_argv()[3] << "d/ > /dev/null && "
                            "rm -r " << FacadeSingleton::getInstance()->get_argv()[3] << "skeleton/ > /dev/null && "
                            "rm -r " << FacadeSingleton::getInstance()->get_argv()[3] << "videoframe/ > /dev/null && "
                            "rm -r " << FacadeSingleton::getInstance()->get_argv()[4] << "op/ > /dev/null && "
                            "rm -r " << FacadeSingleton::getInstance()->get_argv()[3] << "depth/ > /dev/null && "
                            "rm -r " << FacadeSingleton::getInstance()->get_argv()[3] << "sk/ > /dev/null && "
                            "rm -r " << FacadeSingleton::getInstance()->get_argv()[4] << "movement/ > /dev/null && "
                            "mkdir " << FacadeSingleton::getInstance()->get_argv()[3] << "rgb && "
                            "mkdir " << FacadeSingleton::getInstance()->get_argv()[3] << "d && "
                            "mkdir " << FacadeSingleton::getInstance()->get_argv()[3] << "videoframe && "
                            "mkdir " << FacadeSingleton::getInstance()->get_argv()[3] << "skeleton && "
                            "mkdir " << FacadeSingleton::getInstance()->get_argv()[3] << "depth && "
                            "mkdir " << FacadeSingleton::getInstance()->get_argv()[3] << "sk && "
                            "mkdir " << FacadeSingleton::getInstance()->get_argv()[4] << "movement/ && "
                            "mkdir " << FacadeSingleton::getInstance()->get_argv()[4] << "op/";
    SystemCommand::command = std::string(cleanTerminalCommand.str());
}
