//
//  Point3D.cpp
//  AI Watch A1
//
//  Created by Denny Caruso on 20/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#include "Point3D.hpp"



void Point3D::setZ (float z) {
    this->z = z;
}



Point3D::Point3D (float x, float y, float z, Point * decorated) : Point(x, y, decorated) {
    setZ(z);
}

float Point3D::getZ (void) {
    return this->z;
}
