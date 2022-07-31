//
//  CoordinateMappingManager.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 26/07/22.
//

#ifndef CoordinateMappingManager_hpp
#define CoordinateMappingManager_hpp

#include <vector>
#include <cmath>
#include "../../Points/Point3D.hpp"
#include "../../Points/BodyKeyPoint.hpp"



static const float minWidth = 0; // |x<----      |
static const float maxWidth = 2.55; //  |      ---->x|
static const float minHeight = 0.0;
static const float maxHeight = 2.7;

static const float minWidthRS = -3.5; // |x<----      |
static const float maxWidthRS = 3.5; //  |      ---->x|
static const float minHeightRS = -1.0;
static const float maxHeightRS = 1.0;

static const float xOriginUnity = 0;
static const float zOriginUnity = 0;

static const float distanceCameraFromBackWall = 0.0;



class CoordinateMappingManager {
protected:
    float transformWidthCoordinate      (float widthCoordinate);
    float transformHeightCoordinate     (float heightCoordinate);
    float inverseTransform              (float inputNumber);
public:
    virtual std::vector <Point3D *> * mapToMeters   (std::vector <Point3D *> pointsToMap, std::vector <bool> bodyKeyPointsMap,
                                                     float xOrigin, float zOrigin);
};

class UnityCoordinateMappingManager : public CoordinateMappingManager {
    std::vector <Point3D *> * mapToMeters           (std::vector <Point3D *> pointsToMap, std::vector <bool> bodyKeyPointsMap,
                                                     float xOrigin, float zOrigin) override;
};

#endif /* CoordinateMappingManager_hpp */
