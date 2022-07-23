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
#include <iostream>
#include <fstream>
#include "Point3D.hpp"
#include "FacadeSingleton.hpp"
// Nota: inviare prima quante persone (x) e quanti frame (y) e poi x file json per ogni frame y[i]



class JSON_Manager {
    static std::string stringOutputData;
    
    static void setStringOutputData        (std::string stringOutputData);
    static std::string getStringOutputData (void);
public:
    JSON_Manager (void) { }
    
    static void loadJSON                                (std::string filePathJSON, Json::Value & currentJSON);
    static void makeJSON                                (std::vector <Point3D *> skeletonPoints3D);
    static void saveJSON                                (std::string filePath);
    static Json::Value getValueAt                       (std::string key, Json::Value currentJSON);
    static Json::Value getValueAt                       (unsigned int i, Json::Value currentJSON);
    static Json::Value getValueAt                       (std::string key, unsigned int i, Json::Value currentJSON);
    
};

#endif /* JSON_Manager_hpp */
