//
//  Room.hpp
//  AI_Watch_A1
//
//  Created by Denny Caruso on 27/09/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#ifndef Room_hpp
#define Room_hpp


/**
 * @brief Room class represents the Room abstraction. A Room object has different specifications, such as width and height. 
 * Furthermore, since we are interested in the conversion from real-world coordinates to Unity coordinates, 
 * it's important to have some more informations, such as the axes' origins of the digital twin room and the camera's coordinates' interval value.
 */
class Room {
private:
    /**
     * @brief Room's minimum width.
     */
    float _minWidth;
    /**
     * @brief Room's maximum width.
     */
    float _maxWidth;
    /**
     * @brief Room's minimum height.
     */
    float _minHeight;
    /**
     * @brief Room's maximum height.
     */
    float _maxHeight;

    /**
     * @brief RealSense environment's minimum width.
     */
    float _minWidthRS;
    /**
     * @brief RealSense environment's maximum width.
     */
    float _maxWidthRS;
    /**
     * @brief RealSense environment's minimum height.
     */
    float _minHeightRS;
    /**
     * @brief RealSense environment's maximum height.
     */
    float _maxHeightRS;

    /**
     * @brief Digital twin's x axis' origin.
     */
    float _xOriginUnity;
    /**
     * @brief Digital twin's z axis' origin.
     */
    float _zOriginUnity;

    /**
     * @brief Distance between the camera lens and the wall back to the camera.
     */
    float _distanceCameraFromBackWall;
    /**
     * @brief Specific offset that is experimentally considered optimal in order to
     * get more accurate height's measurements.
     */
    float _heightOffset;
    
protected:
    /**
     * @brief Set the Room's minimum width.
     * @param minWidth Room's minimum width.
     */
    void setMinWidth        (float minWidth);
    /**
     * @brief Set the Room's maximum width.
     * @param maxWidth Room's maximum width.
     */
    void setMaxWidth        (float maxWidth);
    /**
     * @brief Set the Room's minimum height.
     * @param minHeight Room's minimum height.
     */
    void setMinHeight       (float minHeight);
    /**
     * @brief Set the Room's maximum height.
     * @param maxHeight Room's maximum height.
     */
    void setMaxHeight       (float maxHeight);
    
    /**
     * @brief Set the RealSense environment's minimum width.
     * @param minWidthRS RealSense environment's minimum width.
     */
    void setMinWidthRS      (float minWidthRS);
    /**
     * @brief Set the RealSense environment's maximum width.
     * @param maxWidthRS RealSense environment's maximum width.
     */
    void setMaxWidthRS      (float maxWidthRS);
    /**
     * @brief Set the RealSense environment's minimum height.
     * @param minHeightRS RealSense environment's minimum height.
     */
    void setMinHeightRS     (float minHeightRS);
    /**
     * @brief Set the RealSense environment's maximum height.
     * @param maxHeightRS RealSense environment's maximum height.
     */
    void setMaxHeightRS     (float maxHeightRS);
    
    /**
     * @brief Set the digital twin's x axis' origin.
     * @param xOriginUnity Digital twin's x axis' origin.
     */
    void setXOriginUnity    (float xOriginUnity);
    /**
     * @brief Set the digital twin's z axis' origin.
     * @param zOriginUnity Digital twin's z axis' origin.
     */
    void setZOriginUnity    (float zOriginUnity);
    
    /**
     * @brief Set the distance between the camera lens and the wall back to the camera.
     * @param distanceCameraFromBackWall Distance between the camera lens and the wall back to the camera.
     */
    void setDistanceCameraFromBackWall  (float distanceCameraFromBackWall);
    /**
     * @brief Set the height offset.
     * @param heightOffset Specific offset that is experimentally considered optimal in order to
     * get more accurate height's measurements.
     */
    void setHeightOffset                (float heightOffset);

public:
    /**
     * @brief Construct a new Room object.
     * @param minWidth Room's minimum width.
     * @param maxWidth Room's maximum width.
     * @param minHeight Room's minimum height.
     * @param maxHeight Room's maximum height.
     * @param minWidthRS RealSense environment's minimum width.
     * @param maxWidthRS RealSense environment's maximum width.
     * @param minHeightRS RealSense environment's minimum height.
     * @param maxHeightRS RealSense environment's maximum height.
     * @param xOriginUnity Digital twin's x axis' origin.
     * @param zOriginUnity Digital twin's z axis' origin.
     * @param distanceCameraFromBackWall Distance between the camera lens and the wall back to the camera.
     * @param heightOffset Specific offset that is experimentally considered optimal in order to
     * get more accurate height's measurements.
     */
    Room (float minWidth, float maxWidth, float minHeight, float maxHeight,
          float minWidthRS, float maxWidthRS, float minHeightRS, float maxHeightRS,
          float xOriginUnity, float zOriginUnity,
          float distanceCameraFromBackWall, float heightOffset);
    
    /**
     * @brief Get the Room's minimum width.
     * @return float 
     */
    float getMinWidth       (void);
    /**
     * @brief Get the Room's maximum width.
     * @return float 
     */
    float getMaxWidth       (void);
    /**
     * @brief Get the Room's minimum height.
     * @return float 
     */
    float getMinHeight      (void);
    /**
     * @brief Get the Room's maximum height.
     * @return float 
     */
    float getMaxHeight      (void);
    
    /**
     * @brief Get the RealSense environment's minimum width.
     * @return float 
     */
    float getMinWidthRS     (void);
    /**
     * @brief Get the RealSense environment's maximum width.
     * @return float 
     */
    float getMaxWidthRS     (void);
    /**
     * @brief Get the RealSense environment's minimum height.
     * @return float 
     */
    float getMinHeightRS    (void);
    /**
     * @brief Get the RealSense environment's maximum height.
     * @return float 
     */
    float getMaxHeightRS    (void);
    
    /**
     * @brief Get the Ddgital twin's x axis' origin.
     * @return float 
     */
    float getXOriginUnity   (void);
    /**
     * @brief Get the digital twin's z axis' origin.
     * @return float 
     */
    float getZOriginUnity   (void);
    
    /**
     * @brief Get the distance between the camera lens and the wall back to the camera.
     * @return float 
     */
    float getDistanceCameraFromBackWall (void);
    /**
     * @brief Get the height offset.
     * @return float 
     */
    float getHeightOffset               (void);
};

#endif /* Room_hpp */