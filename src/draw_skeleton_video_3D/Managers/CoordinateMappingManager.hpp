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
#include "../Points/Point3D.hpp"
#include "../Points/BodyKeyPoint.hpp"



static const float minWidth = 0; // |x<----      |
static const float maxWidth = 5.271; //  |      ---->x|
static const float minHeight = 0.0;
static const float maxHeight = 3.0;

static const float minWidthRS = -3.5; // |x<----      |
static const float maxWidthRS = 3.5; //  |      ---->x|
static const float minHeightRS = -1.0;
static const float maxHeightRS = 1.0;

static const float xOriginUnity = -26.89;
static const float zOriginUnity = -3.842;



class CoordinateMappingManager {
private:
    float transformWidthCoordinate      (float widthCoordinate);
    float transformHeightCoordinate     (float heightCoordinate);
    float inverseTransform              (float inputNumber);
public:
    std::vector <Point3D *> * mapToMeters           (std::vector <Point3D *> pointsToMap);
    std::vector <Point3D *> * mapToMetersForUnity   (std::vector <Point3D *> pointsToMap, float xOrigin, float zOrigin);
};

#endif /* CoordinateMappingManager_hpp */
