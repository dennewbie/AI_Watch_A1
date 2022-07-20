//
//  Point.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 20/07/22.
//

#include "Point.hpp"



void Point::setX (float x) {
    this->x = x;
}

void Point::setY (float y) {
    this->y = y;
}



Point::Point (float x, float y) {
    setX(x);
    setY(y);
}

float Point::getX (void) {
    return this->x;
}

float Point::getY (void) {
    return this->y;
}
