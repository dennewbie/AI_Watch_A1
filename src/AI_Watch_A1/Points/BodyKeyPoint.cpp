//
//  BodyKeyPoint.cpp
//  AI Watch A1
//
//  Created by Denny Caruso on 17/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#include "BodyKeyPoint.hpp"



void BodyKeyPoint::setConfidence (float confidence) {
    this->confidence = confidence;
}



BodyKeyPoint::BodyKeyPoint (float x, float y, float confidence, Point * decorated) : Point(x, y, decorated) {
    setConfidence(confidence);
}

float BodyKeyPoint::getConfidence (void) {
    return this->confidence;
}
