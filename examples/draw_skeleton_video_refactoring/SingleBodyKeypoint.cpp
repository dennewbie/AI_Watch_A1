//
//  SingleBodyKeypoint.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 17/07/22.
//

#include "SingleBodyKeypoint.hpp"

void SingleBodyKeypoint::setX (int x) {
    this->x = x;
}

void SingleBodyKeypoint::setY (int y) {
    this->y = y;
}

void SingleBodyKeypoint::setConfidence (float confidence) {
    this->confidence = confidence;
}



SingleBodyKeypoint::SingleBodyKeypoint (void) {
    setX(0);
    setY(0);
    setConfidence(0.00);
}

SingleBodyKeypoint::SingleBodyKeypoint (int x, int y, float confidence) {
    setX(x);
    setY(y);
    setConfidence(confidence);
}

int SingleBodyKeypoint::getX (void) {
    return this->x;
}

int SingleBodyKeypoint::getY (void) {
    return this->y;
}

float SingleBodyKeypoint::getConfidence (void) {
    return this->confidence;
}
