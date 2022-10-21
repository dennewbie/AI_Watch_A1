//
//  Room.cpp
//  AI_Watch_A1
//
//  Created by Denny Caruso on 27/09/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#include "Room.hpp"

void Room::setMinWidth (float minWidth) {
    this->_minWidth = minWidth;
}

void Room::setMaxWidth (float maxWidth) {
    this->_maxWidth = maxWidth;
}

void Room::setMinHeight (float minHeight) {
    this->_minHeight = minHeight;
}

void Room::setMaxHeight (float maxHeight) {
    this->_maxHeight = maxHeight;
}

void Room::setMaxDepth(float maxDepth) {
    this->_maxDepth = maxDepth;
}

void Room::setMinWidthRS (float minWidthRS) {
    this->_minWidthRS = minWidthRS;
}

void Room::setMaxWidthRS (float maxWidthRS) {
    this->_maxWidthRS = maxWidthRS;
}

void Room::setMinHeightRS (float minHeightRS) {
    this->_minHeightRS = minHeightRS;
}

void Room::setMaxHeightRS (float maxHeightRS) {
    this->_maxHeightRS = maxHeightRS;
}

void Room::setXOriginUnity (float xOriginUnity) {
    this->_xOriginUnity = xOriginUnity;
}

void Room::setZOriginUnity    (float zOriginUnity) {
    this->_zOriginUnity = zOriginUnity;
}

void Room::setDistanceCameraFromBackWall (float distanceCameraFromBackWall) {
    this->_distanceCameraFromBackWall = distanceCameraFromBackWall;
}

void Room::setHeightOffset (float heightOffset) {
    this->_heightOffset = heightOffset;
}



Room::Room (float minWidth, float maxWidth, float minHeight, float maxHeight, float maxDepth,
      float minWidthRS, float maxWidthRS, float minHeightRS, float maxHeightRS,
      float xOriginUnity, float zOriginUnity, float distanceCameraFromBackWall, float heightOffset) {
    setMinWidth(minWidth);
    setMaxWidth(maxWidth);
    setMinHeight(minHeight);
    setMaxHeight(maxHeight);
    setMaxDepth(maxDepth);
    setMinWidthRS(minWidthRS);
    setMaxWidthRS(maxWidthRS);
    setMinHeightRS(minHeightRS);
    setMaxHeightRS(maxHeightRS);
    setXOriginUnity(xOriginUnity);
    setZOriginUnity(zOriginUnity);
    setDistanceCameraFromBackWall(distanceCameraFromBackWall);
    setHeightOffset(heightOffset);
}

float Room::getMinWidth (void) {
    return this->_minWidth;
}

float Room::getMaxWidth (void) {
    return this->_maxWidth;
}

float Room::getMinHeight (void) {
    return this->_minHeight;
}

float Room::getMaxHeight (void) {
    return this->_maxHeight;
}

float Room::getMaxDepth(void) {
    return this->_maxDepth;
}

float Room::getMinWidthRS (void) {
    return this->_minWidthRS;
}

float Room::getMaxWidthRS (void) {
    return this->_maxWidthRS;
}

float Room::getMinHeightRS (void) {
    return this->_minHeightRS;
}

float Room::getMaxHeightRS (void) {
    return this->_maxHeightRS;
}

float Room::getXOriginUnity (void) {
    return this->_xOriginUnity;
}

float Room::getZOriginUnity (void) {
    return this->_zOriginUnity;
}

float Room::getDistanceCameraFromBackWall (void) {
    return this->_distanceCameraFromBackWall;
}

float Room::getHeightOffset (void) {
    return this->_heightOffset;
}
