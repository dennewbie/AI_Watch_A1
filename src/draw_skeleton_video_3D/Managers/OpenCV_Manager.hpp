//
//  OpenCV_Manager.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#ifndef OpenCV_Manager_hpp
#define OpenCV_Manager_hpp

#include "../Skeleton.hpp"



class OpenCV_Manager {
public:
    virtual ~OpenCV_Manager() = default;
    
    cv::Mat realsenseFrameToMat     (const rs2::frame & singleFrame);
    void getVideoFramesCV           (unsigned int user_nFrame, rs2::pipeline & pipelineStream, float scale);
    void showSkeletonsCV            (unsigned int user_nFrame);
};

#endif /* OpenCV_Manager_hpp */
