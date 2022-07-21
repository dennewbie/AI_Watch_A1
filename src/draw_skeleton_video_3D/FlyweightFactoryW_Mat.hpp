//
//  FlyweightFactoryW_Mat.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 21/07/22.
//

#ifndef FlyweightFactoryW_Mat_hpp
#define FlyweightFactoryW_Mat_hpp

#include "W_Mat.hpp"
#include <vector>
#include <string>



class FlyweightFactoryW_Mat {
private:
    static std::vector <W_Mat> images;
    
//    static void setImage                               (std::vector <W_Mat> & images);
//    static std::vector <W_Mat *> & getImages  (void);
    static std::vector <W_Mat> & getImages    (void);
public:
    static cv::Mat & getImage                   (std::string imageName, cv::Mat & image);
};

#endif /* FlyweightFactoryW_Mat_hpp */
