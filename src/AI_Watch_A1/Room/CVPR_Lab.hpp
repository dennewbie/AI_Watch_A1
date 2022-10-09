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
