//
//  Point.cpp
//  AI Watch A1
//
//  Created by Denny Caruso on 20/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#include "Point.hpp"



void Point::setX (float x) {
    this->x = x;
}

void Point::setY (float y) {
    this->y = y;
}

Point::~Point (void) {
    if (getDecorated() != nullptr) delete getDecorated();
}



float Point::getX (void) {
    return this->x;
}

float Point::getY (void) {
    return this->y;
}

const Point * Point::getDecorated (void) {
    return this->decorated;
}
