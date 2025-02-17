//
//  UnityCoordinateMappingManager.cpp
//  AI Watch A1
//
//  Created by Denny Caruso on 30/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#include "CoordinateMappingManager.hpp"



UnityCoordinateMappingManager::UnityCoordinateMappingManager (Room room) : CoordinateMappingManager(room) { }

std::vector <Point3D *> * UnityCoordinateMappingManager::mapToMeters (std::vector <Point3D *> pointsToMap, std::vector <bool> bodyKeyPointsMap, float xOrigin, float zOrigin) {
    std::vector <Point3D *> * newPoints = new std::vector <Point3D *>;
    for (unsigned char i = 0; i < bodyKeyPointsMap.size(); i++) {
        if (!bodyKeyPointsMap.at(i)) {
            newPoints->push_back(new Point3D(0, 0, 0, new BodyKeyPoint(0, 0, 0)));
        } else {
            newPoints->push_back(new Point3D(
                transformWidthCoordinate(pointsToMap.at(i)->getX()) - std::abs(xOrigin),
                transformHeightCoordinate(pointsToMap.at(i)->getY()),
                - (std::abs(pointsToMap.at(i)->getZ()) + std::abs(zOrigin) + getRoom().getDistanceCameraFromBackWall()),
                new BodyKeyPoint(0, 0, ((BodyKeyPoint *) pointsToMap.at(i)->getDecorated())->getConfidence()))
            );
        }
    }

    return newPoints; 
}

/*
 
 Example: Rotating camera by 180°.
 
    newPoints->push_back(new Point3D(
        getRoom().getMaxWidth() - transformWidthCoordinate(pointsToMap.at(i)->getX()) - std::abs(xOrigin),
        transformHeightCoordinate(pointsToMap.at(i)->getY()),
        - (getRoom().getMaxDepth() - std::abs(pointsToMap.at(i)->getZ()) + std::abs(zOrigin) - getRoom().getDistanceCameraFromBackWall()),
        new BodyKeyPoint(0, 0, ((BodyKeyPoint *) pointsToMap.at(i)->getDecorated())->getConfidence()))
    );
    
 */
