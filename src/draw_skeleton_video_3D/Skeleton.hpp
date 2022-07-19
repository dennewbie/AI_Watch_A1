//
//  Skeleton.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 17/07/22.
//

#ifndef Skeleton_h
#define Skeleton_h

#include "SingleBodyKeypoint.hpp"
#include "SinglePoint3D.hpp"
#include <vector>
#include <opencv2/opencv.hpp>
#include <json/value.h>
#include <json/json.h>
#include <librealsense2/rs.hpp>



typedef union {
    float f;
    struct {
        unsigned int mantisa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } parts;
} float_cast;

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
    struct rs2_intrinsics color_intrin;
    std::vector <SinglePoint3D *> skeletonPoints3D;
    
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
    void setSkeletonPoints3D (std::vector <SinglePoint3D *> skeletonPoints3D);
    std::vector <SinglePoint3D *> getSkeletonPoints3D (void);
    
    void drawBodyKeypoints (void);
    void drawBodyEdges (void);
    void drawLine (int start, int end);
    void writeCoordinates (void);
    void deprojectSkeletonPoints3D (struct rs2_intrinsics & color_intrin);
public:
    Skeleton (cv::Mat & rgbImage, cv::Mat & dImage, std::vector <SingleBodyKeypoint> & bodyKeyPoints, std::vector <bool> & bodyKeyPointsMap, Json::Value skeletonData);
    void drawSkeleton (struct rs2_intrinsics & color_intrin);
};

#endif /* Skeleton_h */
