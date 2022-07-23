//
//  RealSenseManager.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#include "RealSenseManager.hpp"



void RealSenseManager::setFrameID (long unsigned int frameID) {
    this->frameID = frameID;
}

void RealSenseManager::set_align (rs2::align align) {
    this->align = align;
}

void RealSenseManager::set_depth_intrin (struct rs2_intrinsics depth_intrin) {
    this->depth_intrin = depth_intrin;
}

void RealSenseManager::set_color_intrin (struct rs2_intrinsics & color_intrin) {
    this->color_intrin = color_intrin;
}

void RealSenseManager::set_depth_to_color (struct rs2_extrinsics depth_to_color) {
    this->depth_to_color = depth_to_color;
}

void RealSenseManager::set_color_to_depth (struct rs2_extrinsics color_to_depth) {
    this->color_to_depth = color_to_depth;
}

rs2::align RealSenseManager::get_align (void) {
    return this->align;
}

struct rs2_intrinsics RealSenseManager::get_depth_intrin (void) {
    return this->depth_intrin;
}

struct rs2_extrinsics RealSenseManager::get_depth_to_color (void) {
    return this->depth_to_color;
}

struct rs2_extrinsics RealSenseManager::get_color_to_depth (void) {
    return this->color_to_depth;
}



RealSenseManager::RealSenseManager (void) : align(RS2_STREAM_COLOR) {
    setFrameID(0);
}

long unsigned int RealSenseManager::getFrameID (void) {
    return this->frameID;
}

struct rs2_intrinsics & RealSenseManager::get_color_intrin (void) {
    return this->color_intrin;
}
