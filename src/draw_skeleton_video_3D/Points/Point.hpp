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
    const Point * decorated;
    
protected:
    void setX   (float x);
    void setY   (float y);
public:
    Point (float x, float y, Point * decorated = nullptr) : decorated(decorated) {
        setX(x);
        setY(y);
    }
    
    ~Point (void);
    
    float getX                  (void);
    float getY                  (void);
    const Point * getDecorated  (void);
};

#endif /* Point_hpp */
