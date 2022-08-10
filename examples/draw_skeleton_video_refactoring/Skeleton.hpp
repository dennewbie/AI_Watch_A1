//
//  Skeleton.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 17/07/22.
//

#ifndef Skeleton_h
#define Skeleton_h

#include "SingleBodyKeypoint.hpp"
#include <vector>
#include <opencv2/opencv.hpp>
#include <json/value.h>
#include <json/json.h>



enum BodyKeypoint { Nose = 0, Neck = 1, RShoulder = 2, RElbow = 3, RWrist = 4,
                    LShoulder = 5, LElbow = 6, LWrist = 7, MidHip = 8, RHip = 9,
                    RKnee = 10, RAnkle = 11, LHip = 12, LKnee = 13, LAnkle = 14,
                    REye = 15, LEye = 16, REar = 17, LEar = 18, LBigToe = 19,
                    LSmallToe = 20, LHeel = 21, RBigToe = 22, RSmallToe = 23, RHeel = 24,
                    Background = 25
                };



class Skeleton {
private:
    cv::Mat rgbImage;
    cv::Mat dImage;
    std::vector <SingleBodyKeypoint> bodyKeyPoints;
    std::vector <bool> bodyKeyPointsMap;
    Json::Value skeletonData;
    
    void setRGB_Image (cv::Mat & rgbImage);
    void setD_Image (cv::Mat & dImage);
    void setBodyKeyPoints (std::vector <SingleBodyKeypoint> & bodyKeyPoints);
    void setBodyKeyPointsMap (std::vector <bool> & bodyKeyPointsMap);
    void setSkeletonData (Json::Value skeletonData);
    
    cv::Mat getRGB_Image (void);
    cv::Mat getD_Image (void);
    std::vector <SingleBodyKeypoint> getBodyKeyPoints (void);
    std::vector <bool> getBodyKeyPointsMap (void);
    Json::Value getSkeletonData (void);
    
    void drawBodyKeypoints (void);
    void drawBodyEdges (void);
    void drawLine (int start, int end);
    void writeCoordinates (void);
public:
    Skeleton (cv::Mat & rgbImage, cv::Mat & dImage, std::vector <SingleBodyKeypoint> & bodyKeyPoints, std::vector <bool> & bodyKeyPointsMap, Json::Value skeletonData);
    void drawSkeleton (void);
};

#endif /* Skeleton_h */
