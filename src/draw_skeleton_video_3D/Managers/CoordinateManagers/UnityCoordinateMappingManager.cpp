//
//  UnityCoordinateMappingManager.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 30/07/22.
//

#include "CoordinateMappingManager.hpp"



std::vector <Point3D *> * UnityCoordinateMappingManager::mapToMeters (std::vector <Point3D *> pointsToMap, std::vector <bool> bodyKeyPointsMap, float xOrigin, float zOrigin) {
    std::vector <Point3D *> * newPoints = new std::vector <Point3D *>;
    
    for (unsigned char i = 0; i < bodyKeyPointsMap.size(); i++) {
        if (!bodyKeyPointsMap.at(i)) {
            newPoints->push_back(new Point3D(0, 0, 0, new BodyKeyPoint(0, 0, 0)));
        } else {
            newPoints->push_back(new Point3D(
                transformWidthCoordinate(pointsToMap.at(i)->getX()) - std::abs(xOrigin),
                transformHeightCoordinate(pointsToMap.at(i)->getY()),
                - (pointsToMap.at(i)->getZ() + std::abs(zOrigin) + distanceCameraFromBackWall),
                new BodyKeyPoint(0, 0, ((BodyKeyPoint *) pointsToMap.at(i)->getDecorated())->getConfidence()))
            );
        }
    }
    
    return newPoints;
}
