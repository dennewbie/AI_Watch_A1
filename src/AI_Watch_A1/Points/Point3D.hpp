//
//  Point3D.hpp
//  AI Watch A1
//
//  Created by Denny Caruso on 20/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#ifndef Point3D_hpp
#define Point3D_hpp

#include "Point.hpp"



/**
 * Point3D class is a class that represents a Point with its own x coordinate, y coordinate, and z coordinate. 
 * This class inherits from Point and adds the "z coordinate" detail.
 * @brief Point3D class is used for Point3D creations and manipulations.
 */
class Point3D : public Point {
private:
    /**
     * @brief Point's z coordinate.
     */
    float z;
    


    /**
     * @brief Set the Point's z coordinate value.
     * @param z Point's z coordinate value.
     */
    void setZ   (float z);
public:
    /**
     * @brief Construct a new Point 3D object
     * @param x Point's x coordinate value.
     * @param y Point's y coordinate value.
     * @param z Point's z coordinate value.
     * @param decorated 
     * @see Point (float x, float y, Point * decorated = nullptr) : decorated(decorated)
     */
    Point3D     (float x, float y, float z, Point * decorated = nullptr);

    /**
     * @brief Get the Point's z coordinate value.
     * @return float 
     */
    float getZ  (void);
};

#endif /* Point3D_hpp */
