//
//  OpenCV_Manager.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#ifndef OpenCV_Manager_hpp
#define OpenCV_Manager_hpp

#include "../Skeleton.hpp"
#include "ImageManager.hpp"




class OpenCV_Manager {
public:
    virtual ~OpenCV_Manager() = default;
    
//    void loadImage                  (std::string imagePath, int loadType, cv::Mat & inputImage);
//    void saveImage                  (std::string imageSavePath, const cv::Mat & imageToSave);
    cv::Mat realsenseFrameToMat     (const rs2::frame & singleFrame);
    void getVideoFramesCV           (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale);
    void showSkeletonCV             (unsigned int user_nFrame, Json::Value & currentJSON);
//    void saveImages                 (const std::initializer_list <cv::Mat> & images,
//                                     const std::initializer_list <std::string> & imagePaths);
//    void releaseImages              (const std::initializer_list <cv::Mat> & images);
};

#endif /* OpenCV_Manager_hpp */
