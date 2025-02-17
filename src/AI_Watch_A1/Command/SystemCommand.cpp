//
//  SystemCommand.cpp
//  AI Watch A1
//
//  Created by Denny Caruso on 23/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#include "SystemCommand.hpp"



void SystemCommand::setCommand (std::string command) {
    this->command = command;
}

std::string SystemCommand::getCommand (void) {
    return this->command;
}

void SystemCommand::executeCommand (int * argc, char *** argv) {
    setCommand(argc, argv);
    if (getCommand().size() > 0 && getCommand() != "OP") std::system(getCommand().c_str());
}
