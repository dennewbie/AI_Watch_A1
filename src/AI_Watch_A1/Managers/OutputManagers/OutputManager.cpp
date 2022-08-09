//
//  OutputManager.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "OutputManager.hpp"



void OutputManager::setStringOutputData (std::string stringOutputData) {
    this->stringOutputData = stringOutputData;
}

std::string OutputManager::getStringOutputData (void) {
    return this->stringOutputData;
}
