//
//  SinglePoint3D.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 20/07/22.
//

#include "SinglePoint3D.hpp"



void SinglePoint3D::setX (float x) {
    this->x = x;
}

void SinglePoint3D::setY (float y) {
    this->y = y;
}
 
void SinglePoint3D::setZ (float z) {
    this->z = z;
}

float SinglePoint3D::getX (void) {
    return this->x;
}

float SinglePoint3D::getY (void) {
    return this->y;
}

float SinglePoint3D::getZ (void) {
    return this->z;
}



SinglePoint3D::SinglePoint3D (float x, float y, float z) {
    setX(x);
    setY(y);
    setZ(z);
}
