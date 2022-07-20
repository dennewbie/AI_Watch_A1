//
//  BodyKeyPoint.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 17/07/22.
//

#include "BodyKeyPoint.hpp"



void BodyKeyPoint::setConfidence (float confidence) {
    this->confidence = confidence;
}



BodyKeyPoint::BodyKeyPoint (int x, int y, float confidence) : Point(x, y){
    setConfidence(confidence);
}

float BodyKeyPoint::getConfidence (void) {
    return this->confidence;
}
