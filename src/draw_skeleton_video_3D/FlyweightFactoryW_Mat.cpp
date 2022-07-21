//
//  FlyweightFactoryW_Mat.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 21/07/22.
//

#include "FlyweightFactoryW_Mat.hpp"



std::vector <W_Mat> FlyweightFactoryW_Mat::images;



//void FlyweightFactoryW_Mat::setImage (std::string imageName, cv::Mat & image) {
//    for (auto & singleImage: FlyweightFactoryW_Mat::getImages()) {
//        if (singleImage->getImageName() == imageName) singleImage->setImage(image);
//    }
//}

std::vector <W_Mat> & FlyweightFactoryW_Mat::getImages (void) {
    return FlyweightFactoryW_Mat::images;
}



cv::Mat & FlyweightFactoryW_Mat::getImage (std::string imageName, cv::Mat & image) {
    for (auto & singleImage: FlyweightFactoryW_Mat::getImages()) {
        std::cout << singleImage.getImageName() << "\n";
    }
    
    for (auto & singleImage: FlyweightFactoryW_Mat::getImages()) {
        
        if (singleImage.getImageName() == imageName) {
            std::cout << "FOUND: " << imageName << " == " << singleImage.getImageName() << "\n";
            return singleImage.getImage();
        }
    }
    
    getImages().push_back(W_Mat(imageName, image));
    return getImages().at(getImages().size() - 1).getImage();
}
