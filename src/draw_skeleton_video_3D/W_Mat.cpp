//
//  W_Mat.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 21/07/22.
//

#include "W_Mat.hpp"

void W_Mat::setImage (cv::Mat & image) {
    this->image = image;
}



cv::Mat & W_Mat::getImage (void) {
    return this->image;
}
