//
//  SinglePoint3D.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 20/07/22.
//

#ifndef SinglePoint3D_hpp
#define SinglePoint3D_hpp

class SinglePoint3D {
private:
    float x;
    float y;
    float z;
    
    void setX (float x);
    void setY (float y);
    void setZ (float z);
public:
    SinglePoint3D (float x, float y, float z);
    
    float getX (void);
    float getY (void);
    float getZ (void);
};

#endif /* SinglePoint3D_hpp */
