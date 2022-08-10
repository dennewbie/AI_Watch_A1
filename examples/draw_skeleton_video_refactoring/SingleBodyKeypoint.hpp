//
//  SingleBodyKeypoint.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 17/07/22.
//

#ifndef SingleBodyKeypoint_hpp
#define SingleBodyKeypoint_hpp

class SingleBodyKeypoint {
private:
    int x;
    int y;
    float confidence;
    
    void setX (int x);
    void setY (int y);
    void setConfidence (float confidence);
public:
    SingleBodyKeypoint (void);
    SingleBodyKeypoint (int x, int y, float confidence);
    
    int getX (void);
    int getY (void);
    float getConfidence (void);
};

#endif /* SingleBodyKeypoint_hpp */
