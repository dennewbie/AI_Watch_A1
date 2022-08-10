//
//  OutputManager.cpp
//  AI Watch A1
//
//  Created by Denny Caruso on 23/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#include "OutputManager.hpp"



void OutputManager::setStringOutputData (std::string stringOutputData) {
    this->stringOutputData = stringOutputData;
}

std::string OutputManager::getStringOutputData (void) {
    return this->stringOutputData;
}
