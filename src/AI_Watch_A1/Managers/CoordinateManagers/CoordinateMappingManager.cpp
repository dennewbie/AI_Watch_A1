//
//  CoordinateMappingManager.cpp
//  AI Watch A1
//
//  Created by Denny Caruso on 26/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#include "CoordinateMappingManager.hpp"
#include <iostream>



Room CoordinateMappingManager::getRoom (void) {
    return this->room;
}

float CoordinateMappingManager::transformWidthCoordinate (float widthCoordinate) {
    float environmentWidth = std::abs(getRoom().getMinWidth()) + std::abs(getRoom().getMaxWidth());
    float environmentWidthRS = std::abs(getRoom().getMinWidthRS()) + std::abs(getRoom().getMaxWidthRS());
    return (((widthCoordinate - getRoom().getMinWidthRS()) / environmentWidthRS) * environmentWidth) + getRoom().getMinWidth();
}

float CoordinateMappingManager::transformHeightCoordinate (float heightCoordinate) {
//    float environmentHeight = std::abs(getRoom().getMinHeight()) + std::abs(getRoom().getMaxHeight());
//    float environmentHeightRS = std::abs(getRoom().getMinHeightRS()) + std::abs(getRoom().getMaxHeightRS());
//    float tempHeight = -(((heightCoordinate - getRoom().getMaxHeightRS()) / environmentHeightRS) * environmentHeight) + getRoom().getMinHeight();
//    return std::abs(tempHeight) - 0.9;
    
    float newHeightCoordinate = -heightCoordinate + getRoom().getMaxHeightRS() - getRoom().getHeightOffset();
    if (newHeightCoordinate >= getRoom().getMaxHeight()) {
        return getRoom().getMaxHeight();
    } else if (newHeightCoordinate <= 0) {
        return 0;
    }

    return newHeightCoordinate;
}

float CoordinateMappingManager::inverseTransform (float inputNumber) {
    float outputNumber = 0.0;
    if (inputNumber >= 1) {
        outputNumber = (1 - 2 * inputNumber);
    } else if (inputNumber <= -1) {
        outputNumber = (-(1 + 2 * inputNumber));
    } else {
        outputNumber = (1 - std::abs(inputNumber) + 0.25);
    }
    
    return outputNumber;
}



std::vector <Point3D *> * CoordinateMappingManager::mapToMeters (std::vector <Point3D *> pointsToMap, std::vector <bool> bodyKeyPointsMap, float xOrigin, float zOrigin) {
    std::vector <Point3D *> * newPoints = new std::vector <Point3D *>;
    
    for (unsigned char i = 0; i < bodyKeyPointsMap.size(); i++) {
        if (!bodyKeyPointsMap.at(i)) {
            newPoints->push_back(new Point3D(0, 0, 0, new BodyKeyPoint(0, 0, 0)));
        } else {
            newPoints->push_back(new Point3D(
                transformWidthCoordinate(pointsToMap.at(i)->getX()),
                transformHeightCoordinate(pointsToMap.at(i)->getY()),
                pointsToMap.at(i)->getZ() - zOrigin + getRoom().getDistanceCameraFromBackWall(),
                new BodyKeyPoint(0, 0, ((BodyKeyPoint *) pointsToMap.at(i)->getDecorated())->getConfidence()))
            );
        }
    }
    
    return newPoints;
}
