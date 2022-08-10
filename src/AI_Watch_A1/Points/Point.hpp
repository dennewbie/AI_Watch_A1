//
//  Point.hpp
//  AI Watch A1
//
//  Created by Denny Caruso on 20/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#ifndef Point_hpp
#define Point_hpp



/**
 * Point class is a class that represents a 2D Point with its own x coordinate and y coordinate. 
 * Furthermore, the Decorator pattern it's implemented with a raw pointer to a Point.
 * @brief Point class is used for point creations and manipulations.
 */
class Point {
private:
    /**
     * @brief Point's x coordinate.
     */
    float x;
    /**
     * @brief Point's y coordinate.
     */
    float y;
    /**
     * @brief A pointer to Point.
     */
    const Point * decorated;
protected:
    /**
     * @brief Set the Point's x coordinate value.
     * @param x Point's x coordinate value.
     */
    void setX   (float x);
    /**
     * @brief Set the Point's y coordinate value.
     * @param y Point's y coordinate value.
     */
    void setY   (float y);
public:
    /**
     * @brief Construct a new Point object.
     * @param x Point's x coordinate value.
     * @param y Point's y coordinate value.
     * @param decorated A pointer to Point.
     */
    Point (float x, float y, Point * decorated = nullptr) : decorated(decorated) {
        setX(x);
        setY(y);
    }
    /**
     * @brief Destroy the Point object.
     */
    ~Point (void);
    


    /**
     * @brief Get the Point's x coordinate value.
     * @return float 
     */
    float getX                  (void);
    /**
     * @brief Get the Point's y coordinate value.
     * @return float 
     */
    float getY                  (void);
    /**
     * @brief Get the pointer to Point used to check if that's a "decorated" Point.
     * @return const Point *  
     */
    const Point * getDecorated  (void);
};

#endif /* Point_hpp */
