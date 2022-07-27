//
//  OpenCV_Manager.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#ifndef OpenCV_Manager_hpp
#define OpenCV_Manager_hpp

#include "../Skeleton.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>



class OpenCV_Manager {
public:
    virtual ~OpenCV_Manager() = default;
    
    void loadImage                  (std::string imagePath, int loadType, cv::Mat & inputImage);
    void saveImage                  (std::string imageSavePath, cv::Mat & imageToSave);
    cv::Mat realsenseFrameToMat     (const rs2::frame & singleFrame);
    void getVideoFramesCV           (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale);
    void showSkeleton               (unsigned int user_nFrame, Json::Value & currentJSON);
};

#endif /* OpenCV_Manager_hpp */
