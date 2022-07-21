//
//  JSON_Manager.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 21/07/22.
//

#ifndef JSON_Manager_hpp
#define JSON_Manager_hpp

#include <sstream>
#include <vector>
#include <string>
#include <json/value.h>
#include <json/json.h>
#include <json/writer.h>
#include <iostream>
#include "Point3D.hpp"
// Nota: inviare prima quante persone (x) e quanti frame (y) e poi x file json per ogni frame y[i]



class JSON_Manager {
    std::string outputData;
public:
    JSON_Manager (void) {
    }
    
    void makeJSON                               (std::vector <Point3D *> skeletonPoints3D);
    std::string getStringOutputData             (void);
    std::stringstream getStringStreamOutputData (void);
};

#endif /* JSON_Manager_hpp */
