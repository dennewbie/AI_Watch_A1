//
//  BodyKeyPoint.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 17/07/22.
//

#ifndef BodyKeyPoint_hpp
#define BodyKeyPoint_hpp

#include "Point.hpp"



class BodyKeyPoint : public Point {
private:
    float confidence;
    
    void setConfidence  (float confidence);
public:
    BodyKeyPoint (int x, int y, float confidence, Point * decorated = nullptr);
    
    float getConfidence (void);
};

#endif /* BodyKeyPoint_hpp */
