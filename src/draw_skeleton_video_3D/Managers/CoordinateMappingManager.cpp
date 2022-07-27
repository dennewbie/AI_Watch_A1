//
//  CoordinateMappingManager.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 26/07/22.
//

#include "CoordinateMappingManager.hpp"



float CoordinateMappingManager::transformWidthCoordinate (float widthCoordinate) {
    float environmentWidth = std::abs(minWidth) + std::abs(maxWidth);
    float environmentWidthRS = std::abs(minWidthRS) + std::abs(maxWidthRS);
    return (((widthCoordinate - minWidthRS) / environmentWidthRS) * environmentWidth) + minWidth;
}

float CoordinateMappingManager::transformHeightCoordinate (float heightCoordinate) {
    float newHeightCoordinate = -heightCoordinate + maxHeightRS;
    if (newHeightCoordinate >= 2) {
        return 3;
    } else if (newHeightCoordinate <= 0) {
        return 0;
    }
    
    return newHeightCoordinate + 0.15;
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



std::vector <Point3D *> * CoordinateMappingManager::mapToMeters (std::vector <Point3D *> pointsToMap) {
    std::vector <Point3D *> * newPoints = new std::vector <Point3D *>;
    
    for (auto & singlePoint: pointsToMap) {
        newPoints->push_back(new Point3D(
            transformWidthCoordinate(singlePoint->getX()),
            transformHeightCoordinate(singlePoint->getY()),
            singlePoint->getZ())
        );
    }
    
    return newPoints;
}


std::vector <Point3D *> * CoordinateMappingManager::mapToMetersForUnity (std::vector <Point3D *> pointsToMap, float xOrigin, float zOrigin) {
    std::vector <Point3D *> * newPoints = new std::vector <Point3D *>;
    
    for (auto & singlePoint: pointsToMap) {
        newPoints->push_back(new Point3D(
            transformWidthCoordinate(singlePoint->getX()) - std::abs(xOrigin),
            transformHeightCoordinate(singlePoint->getY()),
            - (singlePoint->getZ() + std::abs(zOrigin)))
        );
    }
    
    return newPoints;
}
