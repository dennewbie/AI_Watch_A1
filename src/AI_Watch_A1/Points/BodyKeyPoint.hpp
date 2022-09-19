//
//  BodyKeyPoint.hpp
//  AI Watch A1
//
//  Created by Denny Caruso on 17/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#ifndef BodyKeyPoint_hpp
#define BodyKeyPoint_hpp

#include "Point.hpp"



/**
 * BodyKeyPoint class is a class that represents a Body Keypoint with its own x coordinate and y coordinate. 
 * This class inherits from Point and adds the "confidence" detail in order to keep track of the OpenPose confidence
 * on this particular point.
 * @brief BodyKeyPoint class is used for body keypoint creations and manipulations.
 */
class BodyKeyPoint : public Point {
private:
    /**
     * @brief The confidence value is an OpenPose parameter to evaluate how accurate the process was while 
     * determining this particular joint point.
     */
    float confidence;
    


    /**
     * @brief Set the confidence value.
     * @param confidence 
     */
    void setConfidence  (float confidence);
public:
    /**
     * @brief Construct a new Body Keypoint object.
     * @param x 
     * @param y 
     * @param confidence 
     * @param decorated 
     * @see Point (float x, float y, Point * decorated = nullptr) : decorated(decorated)
     */
    BodyKeyPoint        (float x, float y, float confidence, Point * decorated = nullptr);
    
    /**
     * @brief Get the confidence value.
     * @return float 
     */
    float getConfidence (void);
};

#endif /* BodyKeyPoint_hpp */
