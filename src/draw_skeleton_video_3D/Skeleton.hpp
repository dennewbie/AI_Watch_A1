//
//  Skeleton.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 17/07/22.
//

#ifndef Skeleton_h
#define Skeleton_h

#include "BodyKeyPoint.hpp"
#include "Point3D.hpp"
#include "FacadeSingleton.hpp"
#include <vector>
#include <opencv2/opencv.hpp>
#include <json/value.h>
#include <json/json.h>
#include <librealsense2/rs.hpp>
#include "constants.hpp"



enum BodyKeypoint { Nose = 0, Neck = 1, RShoulder = 2, RElbow = 3, RWrist = 4,
                    LShoulder = 5, LElbow = 6, LWrist = 7, MidHip = 8, RHip = 9,
                    RKnee = 10, RAnkle = 11, LHip = 12, LKnee = 13, LAnkle = 14,
                    REye = 15, LEye = 16, REar = 17, LEar = 18, LBigToe = 19,
                    LSmallToe = 20, LHeel = 21, RBigToe = 22, RSmallToe = 23, RHeel = 24,
                    Background = 25
                };



class Skeleton {
private:
    cv::Mat                     rgb_Image;
    cv::Mat                     distance_Image;
    std::vector <BodyKeyPoint>  bodyKeyPoints;
    std::vector <bool>          bodyKeyPointsMap;
    Json::Value                 skeletonData;
    std::vector <Point3D *>     skeletonPoints3D;
    
    void setRGB_Image           (cv::Mat & rgbImage);
    void setDistance_Image      (cv::Mat & distanceImage);
    void setBodyKeyPoints       (std::vector <BodyKeyPoint> & bodyKeyPoints);
    void setBodyKeyPointsMap    (std::vector <bool> & bodyKeyPointsMap);
    void setSkeletonData        (Json::Value skeletonData);
    void setSkeletonPoints3D    (std::vector <Point3D *> skeletonPoints3D);
    
    cv::Mat getRGB_Image                        (void);
    cv::Mat getDistance_Image                   (void);
    std::vector <BodyKeyPoint> getBodyKeyPoints (void);
    std::vector <bool> getBodyKeyPointsMap      (void);
    Json::Value getSkeletonData                 (void);
    std::vector <Point3D *> getSkeletonPoints3D (void);
    
    void calcBodyKeypoints          (void);
    void calcBodyEdges              (void);
    void drawLine                   (int start, int end);
    void writeCoordinates           (void);
    void deprojectSkeletonPoints3D  (void);
public:
    Skeleton            (cv::Mat & rgbImage, cv::Mat & distanceImage, Json::Value skeletonData);
    ~Skeleton           (void);
    void drawSkeleton   (void);
};

#endif /* Skeleton_h */
