//
//  Point3D.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 20/07/22.
//

#ifndef Point3D_hpp
#define Point3D_hpp

#include "Point.hpp"



class Point3D : public Point {
private:
    float z;
    
    void setZ   (float z);
public:
    Point3D     (float x, float y, float z, Point * decorated = nullptr);
    
    float getZ  (void);
};

#endif /* Point3D_hpp */
