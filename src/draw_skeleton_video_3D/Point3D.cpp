//
//  Point3D.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 20/07/22.
//

#include "Point3D.hpp"



void Point3D::setZ (float z) {
    this->z = z;
}



Point3D::Point3D (float x, float y, float z) : Point(x, y) {
    setZ(z);
}

float Point3D::getZ (void) {
    return this->z;
}
