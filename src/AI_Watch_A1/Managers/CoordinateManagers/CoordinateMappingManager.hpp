//
//  CoordinateMappingManager.hpp
//  AI Watch A1
//
//  Created by Denny Caruso on 26/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#ifndef CoordinateMappingManager_hpp
#define CoordinateMappingManager_hpp

#include <vector>
#include <cmath>
#include "../../Room/CVPR_Lab.hpp"
#include "../../Points/Point3D.hpp"
#include "../../Points/BodyKeyPoint.hpp"



/**
 * @brief The CoordinateMappingManager class is a class that is responsible for converting coordinates values from a coordinates' space 
 * to another one. A certain coordinates' space has to inherit from this class and implement its own conversion method, 
 * overriding the base class method.
 * @see https://math.stackexchange.com/questions/685110/how-to-determine-coordinates-on-two-different-size-rectangles
 */
class CoordinateMappingManager {
protected:
    /**
     * @brief Specific room within which the coordinate mapping will be done.
     */
    const Room room;
    
    /**
     * @brief Returns the room object.
     * @return Room
     */
    Room getRoom (void);
    /**
     * @brief Converts width value.
     * @param widthCoordinate Input width value.
     * @return float 
     */
    float transformWidthCoordinate      (float widthCoordinate);
    /**
     * @brief Converts height value.
     * @param heightCoordinate Input height value.
     * @return float 
     */
    float transformHeightCoordinate     (float heightCoordinate);
    /**
     * @brief Implements the inverse conversion on the input value.
     * @param inputNumber Input value to convert.
     * @return float 
     */
    float inverseTransform              (float inputNumber);
public:
    /**
     * @brief Construct a new Coordinate Mapping Manager object.
     * @param room Specific room within which the coordinate mapping will be done.
     */
    CoordinateMappingManager (Room room) : room(room) { }
    /**
     * @brief This method requires pointers' Point3D's vector, the related vector map, and the original coordinates' space origins. 
     * It returns a pointer to pointers' Point3D's vector that actually contains all input Points whose coordinates' values have been 
     * converted to the new coordinates' space. In the parent class, the conversion just converts the RealSense's values to more 
     * accessible axes' origins.
     * @param pointsToMap 
     * @param bodyKeyPointsMap 
     * @param xOrigin 
     * @param zOrigin 
     * @return std::vector <Point3D *> * 
     */
    virtual std::vector <Point3D *> * mapToMeters   (std::vector <Point3D *> pointsToMap, std::vector <bool> bodyKeyPointsMap,
                                                     float xOrigin, float zOrigin);
};



/**
 * @brief The UnityCoordinateMappingManager class is a class that is responsible for converting coordinates values from a coordinates' space 
 * to Unity coordinates' space whose parameters are specified at the top of this header file. 
 * @see https://math.stackexchange.com/questions/685110/how-to-determine-coordinates-on-two-different-size-rectangles
 */
class UnityCoordinateMappingManager : public CoordinateMappingManager {
public:
    /**
     * @brief Construct a new Unity Coordinate Mapping Manager object.
     * @param room Specific room within which the Unity' coordinate mapping will be done.
     */
    UnityCoordinateMappingManager (Room room);
    /**
     * @brief This method requires pointers' Point3D's vector, the related vector map, and the original coordinates' space origins. 
     * It returns a pointer to pointers' Point3D's vector that actually contains all input Points whose coordinates' values have been 
     * converted to the new coordinates' space. In this case, the method converts the values to Unity coordinates' space values whose 
     * configuration parameters are specified at the top of this header file.
     * 
     * @param pointsToMap 
     * @param bodyKeyPointsMap 
     * @param xOrigin 
     * @param zOrigin 
     * @return std::vector <Point3D *> * 
     */
    std::vector <Point3D *> * mapToMeters           (std::vector <Point3D *> pointsToMap, std::vector <bool> bodyKeyPointsMap,
                                                     float xOrigin, float zOrigin) override;
};

#endif /* CoordinateMappingManager_hpp */
