//
//  CVPR_Lab.hpp
//  AI_Watch_A1
//
//  Created by Denny Caruso on 27/09/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#ifndef CVPR_Lab_h
#define CVPR_Lab_h

#include "Room.hpp"



// CVPR Lab's Measurements Renato Esposito 06/22
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

static const float distanceCameraFromBackWall = 0.45;
static const float heightOffset = 0.15;



// CVPR Lab's Measurements Denny Caruso 09/22
//static const float minWidth = 0; // |x<----      |
//static const float maxWidth = 6.03; //  |      ---->x|
//static const float minHeight = 0.0;
//static const float maxHeight = 2.89;
//
//static const float minWidthRS = -3.5; // |x<----      |
//static const float maxWidthRS = 3.5; //  |      ---->x|
////static const float minHeightRS = -1.20;
////static const float maxHeightRS = 1.20;
//static const float minHeightRS = -1.0;
//static const float maxHeightRS = 1.0;
//
//static const float xOriginUnity = -26.89;
//static const float zOriginUnity = -3.842;
//
//static const float distanceCameraFromBackWall = 0.45;
//static const float heightOffset = 0.15;



/**
 * @brief CVPR Lab class represents the CVPR Lab abstraction. The CVPR Lab is a Room with default values.
 * Those default values are the ones above. Meanwhile, a Room object lets the possibility to define a 
 * room with custom dimensions. The real CVPR Lab is located at University of Naples Parthenope, Italy.
 */
class CVPR_Lab : public Room {
public:
    /**
     * @brief Construct a new CVPR Lab object.
     */
    CVPR_Lab (void);
};

#endif /* CVPR_Lab_h */
