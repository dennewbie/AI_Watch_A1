//
//  Point.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 20/07/22.
//

#ifndef Point_hpp
#define Point_hpp



class Point {
private:
    float x;
    float y;
    
protected:
    void setX   (float x);
    void setY   (float y);
public:
    Point       (float x, float y);
    
    float getX  (void);
    float getY  (void);
};

#endif /* Point_hpp */
