//
//  Skeleton.hpp
//  AI Watch A1
//
//  Created by Denny Caruso on 17/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#ifndef Skeleton_h
#define Skeleton_h

#include "FacadeSingleton/FacadeSingleton.hpp"



/**
 * @brief Enumeration for body keypoints produced from OpenPose. 
 * @see https://github.com/CMU-Perceptual-Computing-Lab/openpose
 */
enum BodyKeypoint { Nose = 0, Neck = 1, RShoulder = 2, RElbow = 3, RWrist = 4,
                    LShoulder = 5, LElbow = 6, LWrist = 7, MidHip = 8, RHip = 9,
                    RKnee = 10, RAnkle = 11, LHip = 12, LKnee = 13, LAnkle = 14,
                    REye = 15, LEye = 16, REar = 17, LEar = 18, LBigToe = 19,
                    LSmallToe = 20, LHeel = 21, RBigToe = 22, RSmallToe = 23, RHeel = 24,
                    Background = 25
                };



/**
 * Skeleton class is a class that keeps track of the image different frames where a specific skeleton may appears, 
 * its body key points, correspondent 3D space points, and other useful information skeleton-related.
 * @brief Skeleton class is used for skeleton creations and manipulations.
 */
class Skeleton {
private:
    /**
     * @brief RGB frame related to the frame in which the skeleton may appears.
     */
    cv::Mat                     rgb_Image;
    /**
     * @brief Distance frame related to the frame in which the skeleton may appears.
     */
    cv::Mat                     distance_Image;
    /**
     * @brief A frame that contains only skeleton information such as green legs and red dots, representing connections between body joints.
     */
    cv::Mat                     skeleton_Image; // remove
    /**
     * @brief A vector that contains each body joint retrieved from OpenPose
     * @see BodyKeyPoint
     */
    std::vector <BodyKeyPoint>  bodyKeyPoints;
    /**
     * @brief A vector that contains for each body joint retrieved from OpenPose a corresponding boolean that means if that body joint is a valuable
     * and effective body joint or not. A body joint is a BodyKeyPoint with 3 conditions: "x" coordinate is different from zero, "y" coordinate is different 
     * from zero, and "confidence" is greater than 0.0.
     * @see BodyKeyPoint
     */
    std::vector <bool>          bodyKeyPointsMap;
     /**
     * @brief Represents a Skeleton JSON value. This class is a discriminated union wrapper that can represent a:
     *          - signed integer [range: Value::minInt - Value::maxInt]
     *          - unsigned integer (range: 0 - Value::maxUInt)
     *          - double
     *          - UTF-8 string
     *          - boolean
     *          - 'null'
     *          - an ordered list of Value
     *          - collection of name/value pairs (javascript object)
     * 
     * In this case this JSON Value contains all informations about body joints retrieved from OpenPose JSON output.
     * @see https://github.com/open-source-parsers/jsoncpp
     * @see BodyKeyPoint
     */
    Json::Value                 skeletonData;
    /**
     * @brief A vector that contains a set of pointers to Point3D. These points have coordinates whose domain is defined by RealSense Camera 
     * and project/deproject operations.
     * @see https://dev.intelrealsense.com/docs/projection-in-intel-realsense-sdk-20
     * @see Point3D
     */
    std::vector <Point3D *>     skeletonPoints3D_RS;
    /**
     * @brief A pointer to a vector that contains a set of pointers to Point3D. These points have coordinates in which the domain is defined from 
     * boundaries parameters specified in "constants.hpp"
     * @see https://dev.intelrealsense.com/docs/projection-in-intel-realsense-sdk-20
     * @see Point3D
     * @see constants.hpp
     */
    std::vector <Point3D *> *   skeletonPoints3D;
    /**
     * @brief Consistency is a value that represents how accurate is the OpenPose detection for this skeleton. As consequence, a really low consistency 
     * value indicates a skeleton that could not there be in the real scene (OpenPose misdetection). Otherwise, a low consistency value indicates a 
     * partial skeleton. This value is within the range [0; 1].
     */
    float consistency;
    


    /**
     * @brief Set the RGB Image object.
     * @param rgbImage 
     */
    void setRGB_Image               (cv::Mat & rgbImage);
    /**
     * @brief Set the Distance Image object.
     * @param distanceImage 
     */
    void setDistance_Image          (cv::Mat & distanceImage);
    /**
     * @brief Set the Skeleton-only Image object.
     * @param skeleton_Image 
     */
    void setSkeleton_Image          (cv::Mat & skeleton_Image);
    /**
     * @brief Set the Body Key Points vector.
     * @param bodyKeyPoints 
     */
    void setBodyKeyPoints           (std::vector <BodyKeyPoint> & bodyKeyPoints);
    /**
     * @brief Set the Body Key Points Map vector.
     * @param bodyKeyPointsMap 
     */
    void setBodyKeyPointsMap        (std::vector <bool> & bodyKeyPointsMap);
    /**
     * @brief Set the Skeleton Data JSON object.
     * @param skeletonData 
     */
    void setSkeletonData            (Json::Value skeletonData);
    /**
     * @brief Set the SkeletonPoints3D RS vector.
     * @param skeletonPoints3D_RS 
     */
    void setSkeletonPoints3D_RS     (std::vector <Point3D *> skeletonPoints3D_RS);
    /**
     * @brief Set the Skeleton Points3D pointer to vector.
     * @param skeletonPoints3D 
     */
    void setSkeletonPoints3D        (std::vector <Point3D *> * skeletonPoints3D);
    /**
     * @brief Set the Consistency float value.
     * @param consistency 
     */
    void setConsistency             (float consistency);
    


    /**
     * @brief Get the RGB Image object.
     * @return cv::Mat 
     */
    cv::Mat getRGB_Image                                    (void);
    /**
     * @brief Get the Distance Image object.
     * @return cv::Mat 
     */
    cv::Mat getDistance_Image                               (void);
    /**
     * @brief Get the Skeleton-only Image object.
     * @return cv::Mat 
     */
    cv::Mat getSkeleton_Image                               (void);
    /**
     * @brief Get the Body Key Points vector.
     * @return std::vector <BodyKeyPoint> 
     */
    std::vector <BodyKeyPoint> getBodyKeyPoints             (void);
    /**
     * @brief Get the Skeleton Data JSON object.
     * @return Json::Value 
     */
    Json::Value getSkeletonData                             (void);
    


    /**
     * @brief Retrieve BodyKeyPoints vector and the BodyKeyPoints Map bool vector from OpenPose output, 
     * while calculating corresponding Skeleton consistency.
     * @see OutputManager
     * @see OutputManagerJSON
     * @see FacadeSingleton
     */
    void calcBodyKeypoints          (void);
    /**
     * @brief Calculate Skeleton and invoke methods to draw it on the image according to OpenPose skeleton
     * structure.
     * @see drawLine (unsigned char start, unsigned char end)
     * @see drawCircle (cv::Point center)
     */
    void calcBodyEdges              (void);
    /**
     * @brief Draw a line that starts from a point and ends at another point. The points are specified as unsigned char, 
     * since is possible to access the instance BodyKeyPoints vector and get the point.
     * @param start start point index in the BodyKeyPoints vector
     * @param end end point index in the BodyKeyPoints vector
     */
    void drawLine                   (unsigned char start, unsigned char end);
    /**
     * @brief Draw a circle at the specified point as a parameter.
     * @param center points where OpenCV will draw the circle.
     */
    void drawCircle                 (cv::Point center);
    /**
     * @brief Deprojection operation takes a 2D pixel location on a stream's images, as well as a depth, 
     * specified in meters, and maps it to a 3D point location within the stream's associated 3D coordinate space.
     * It is provided by the header-only function rs2_deproject_pixel_to_point(...). 
     * Intrinsic parameters can be retrieved from any rs2::video_stream_profile object via a call to get_intrinsics(). 
     * @see https://dev.intelrealsense.com/docs/projection-in-intel-realsense-sdk-20
     * @see FacadeSingleton
     * @see RealSenseManager
     * @see get_color_intrin()
     */
    void deprojectSkeletonPoints3D  (void);
    /**
     * @brief Write "nose" joint point's coordinates on the RGB image.
     * @see getSkeletonPoints3D()
     * @see getBodyKeyPoints()
     * @see Point
     */
    void writeCoordinates           (void);
public:
    /**
     * @brief Construct a new Skeleton object.
     * @param rgbImage RGB frame.
     * @param distanceImage Distance frame.
     * @param skeletonImage Skeleton frame.
     * @param skeletonData JSON object of a single person detected by OpenPose.
     */
    Skeleton                                        (cv::Mat & rgbImage, cv::Mat & distanceImage, cv::Mat & skeletonImage, Json::Value skeletonData);
    /**
     * @brief Destroy the Skeleton object.
     */
    ~Skeleton                                       (void);
    /**
     * @brief A high-level method that abstracts all the internal structure and operations of the Skeleton class. 
     * It first calls calcBodyKeypoints(), then calcBodyEdges(), deprojectSkeletonPoints3D(), convert the coordinates 
     * in a specific format and then write them on the RGB image with writeCoordinates().
     * @see mapToMeters (std::vector <Point3D *> pointsToMap, std::vector <bool> bodyKeyPointsMap, float xOrigin, float zOrigin)
     */
    void generateSkeleton                           (void);
    /**
     * @brief Get the BodyKeyPoints Map vector.
     * @return std::vector <bool> 
     */
    std::vector <bool> getBodyKeyPointsMap          (void);
    /**
     * @brief Get the SkeletonPoints3D RS vector.
     * @return std::vector <Point3D *> 
     */
    std::vector <Point3D *> getSkeletonPoints3D_RS  (void);
    /**
     * @brief Get the Skeleton Points3D vector's pointer.
     * @return std::vector <Point3D *>* 
     */
    std::vector <Point3D *> * getSkeletonPoints3D   (void);
    /**
     * @brief Get the Consistency float value.
     * @return float 
     */
    float getConsistency                            (void);
};

#endif /* Skeleton_h */
