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



std::vector <Point3D *> * CoordinateMappingManager::mapToMeters (std::vector <Point3D *> pointsToMap, std::vector <bool> bodyKeyPointsMap) {
    std::vector <Point3D *> * newPoints = new std::vector <Point3D *>;
    
    for (unsigned char i = 0; i < bodyKeyPointsMap.size(); i++) {
        if (!bodyKeyPointsMap.at(i)) {
            newPoints->push_back(new Point3D(0, 0, 0));
        } else {
            newPoints->push_back(new Point3D(
                transformWidthCoordinate(pointsToMap.at(i)->getX()),
                transformHeightCoordinate(pointsToMap.at(i)->getY()),
                pointsToMap.at(i)->getZ(),
                new BodyKeyPoint(0, 0, ((BodyKeyPoint *) pointsToMap.at(i)->getDecorated())->getConfidence()))
            );
        }
    }
    
    return newPoints;
}

std::vector <Point3D *> * CoordinateMappingManager::mapToMetersForUnity (std::vector <Point3D *> pointsToMap, std::vector <bool> bodyKeyPointsMap, float xOrigin, float zOrigin) {
    std::vector <Point3D *> * newPoints = new std::vector <Point3D *>;
    
    for (unsigned char i = 0; i < bodyKeyPointsMap.size(); i++) {
        if (!bodyKeyPointsMap.at(i)) {
            newPoints->push_back(new Point3D(0, 0, 0, new BodyKeyPoint(0, 0, 0)));
        } else {
            newPoints->push_back(new Point3D(
                transformWidthCoordinate(pointsToMap.at(i)->getX()) - std::abs(xOrigin),
                transformHeightCoordinate(pointsToMap.at(i)->getY()),
                - (pointsToMap.at(i)->getZ() + std::abs(zOrigin)),
                new BodyKeyPoint(0, 0, ((BodyKeyPoint *) pointsToMap.at(i)->getDecorated())->getConfidence()))
            );
        }
    }

    return newPoints;
}
