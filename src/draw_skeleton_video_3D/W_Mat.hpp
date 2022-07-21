//
//  W_Mat.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 21/07/22.
//

#ifndef W_Mat_hpp
#define W_Mat_hpp

#include <opencv2/opencv.hpp>

class W_Mat {
private:
    const std::string imageName;
    cv::Mat image;
    
    void setImage                   (cv::Mat & image);
public:
    W_Mat (std::string imageName, cv::Mat & image) : imageName(imageName) {
        setImage(image);
    }
    
    std::string     getImageName    (void);
    cv::Mat &       getImage        (void);
};

#endif /* W_Mat_hpp */
